#include "libft.h"
#include "pipex.h"

int execute_a_cmd(t_pipex *pipex, char **cmd_args, int i)
{
	char	*complete_cmd = NULL;

	if (processing_cmd_args(pipex, cmd_args[i], &complete_cmd, 0) == OK)
	{
		if (access(complete_cmd, X_OK) == 0)
			execve(complete_cmd, cmd_args, pipex->main_pars.raw_envp);
	}
	error_msg_termination("Invalid Command.\n", FD2, is_valid_cmd_checker(pipex, complete_cmd));
	return (is_valid_cmd_checker(pipex, complete_cmd));
}

int	handle_input_cmd(t_pipex *pipex, int i)
{
	if (pipex->files.infile_fd == -1)
		return (ERR_OUTFILE);
	pipex->childs_pids[i] = fork();
	if (pipex->childs_pids[i] == -1)
	{
		pipex->errno_rtrn = errno;
		error_msg_termination("ERROR: forking for infile cmd failed :(.\n", PERROR, errno);
	}
	if (pipex->childs_pids[i] == 0)
	{
		pipex->errno_rtrn = perform_both_io_dup2(pipex, pipex->files.infile_fd, pipex->pipes_fds[0][1]);
		close_all_files(pipex);
		close_all_pipes(pipex);
		execute_a_cmd(pipex, pipex->cmds_args[0], 0);
	}
	return (is_valid_cmd_checker(pipex, pipex->cmds_args[0][0]));
}

int	handle_here_doc(t_pipex *pipex, int i)
{
	pipex->childs_pids[i] = fork();	// try to fail it
	if (pipex->childs_pids[i] == -1)
	{
		error_msg("Failed in forking here_doc child.\n", PERROR);
		return (errno);
	}
	if (pipex->childs_pids[i] == 0)
	{
		input_here_doc(pipex);
		close_io_pipes(pipex->pipes_fds[0]);	// close all pipes also for this child
		close(pipex->files.outfile_fd);
		error_msg_termination("", STDOUT_FILENO, OK);
	}
	return (OK);
}

int perform_middle_pipes_cmds(t_pipex *pipex, int i)
{
	int j;

	while (i < pipex->num_cmds_args - 1)
	{
		pipex->childs_pids[i] = fork();
		if (pipex->childs_pids[i] == -1)
			error_msg_termination("Failed in forking middle child.\n", PERROR, errno);
		if (pipex->childs_pids[i] == 0)
		{
			pipex->errno_rtrn = perform_both_io_dup2(pipex->pipes_fds[i - 1][0], pipex->pipes_fds[i][1]);
			if (pipex->errno_rtrn != OK)
				return (i);
			j = 0;
			while (j < pipex->num_cmds_args - 1)
			{
				close_io_pipes(pipex->pipes_fds[j]);
				j++;
			}
			execute_a_cmd(pipex, pipex->cmds_args[i], 0);
		}
		i++;
	}
	return (OK);
}

int perform_last_cmd(t_pipex *pipex, int i)
{
	int j;

	i = pipex->num_cmds_args - 1;
	pipex->childs_pids[i] = fork();
	if (pipex->childs_pids[i] == -1)
		error_msg_termination("Failed in forking last child.\n", PERROR, errno);
	if (pipex->childs_pids[i] == 0)
	{
		if (pipex->files.outfile_fd == -1)
		{
			close_io_pipes(pipex->pipes_fds[i]);
			error_msg_termination("Failed in last cmd.\n", PERROR, get_outfile_ready(pipex));
		}
		pipex->errno_rtrn = perform_both_io_dup2(pipex->pipes_fds[i - 1][0], pipex->files.outfile_fd);
		if (pipex->errno_rtrn != OK)
			error_msg_termination("Failed in dup2 in last child.\n", PERROR, errno);
		j = 0;
		while (j < pipex->num_cmds_args - 1)
		{
			close_io_pipes(pipex->pipes_fds[j]);	// also close files !
			j++;
		}
		execute_a_cmd(pipex, pipex->cmds_args[i], 0);
	}
	return (OK);
}


