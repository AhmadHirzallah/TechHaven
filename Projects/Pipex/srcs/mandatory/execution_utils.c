#include "pipex.h"
#include "libft.h"

static void input_here_doc(t_pipex *pipex_info, int i)
{
	char	*user_input = NULL;

	while (true)
	{
		ft_putstr_fd("heredoc> ", STDIN_FILENO);
		user_input = get_next_line(STDIN_FILENO);
		if (user_input == NULL)
			terminate_pipex_with_msg(pipex_info, "Error in get_next_line input",
									ERR_IN_GNL, FD2);
		if (str_cmpr(user_input, pipex_info->heredoc_delim) == 0)
		{
			free(user_input);
			break;
		}
		ft_putstr_fd(user_input, pipex_info->pipes.pipes_fds[i][1]);
		free(user_input);
	}
}

int	handle_here_doc(t_pipex *pipex_info, int i)		//close fds and pipes
{
	pipex_info->pipes.childs_prcs_ids[i] = fork();	// try to fail it
	if (pipex_info->pipes.childs_prcs_ids[i] == -1)
	{
		display_error_msg("Failed in forking here_doc child.\n", PERROR);
		return (errno);
	}
	if (pipex_info->pipes.childs_prcs_ids[i] == 0)
		input_here_doc(pipex_info, i);
	// close pipes[0][1,0] & fd_outfile
	terminate_pipex(pipex_info, i);
	return (OK);
}

/*
	- argv[2] is first cmd in general form
	- argv[3] is first cmd in here_doc
*/
static char	*get_executable_cmd(t_pipex *pipex_info, char *system_path, char *cmd)
{
	char	*executable_cmd = NULL;
	char	*unusable_cmd;

	unusable_cmd = ft_strjoin("/", cmd);
	if (unusable_cmd == NULL || !unusable_cmd[0])
		terminate_pipex_with_msg(pipex_info, "Failed in mallocing strjoin of child process.\n",
								ERR_FAIL_STRJOIN_CMDS, FD2);
	executable_cmd = ft_strjoin(system_path, unusable_cmd);
	if (unusable_cmd == NULL || !unusable_cmd[0])
		terminate_pipex_with_msg(pipex_info, "Failed in mallocing strjoin of child process.\n",
								ERR_FAIL_STRJOIN_CMDS, FD2);
	free(unusable_cmd);
	return (executable_cmd);
}

void	execute_cmd(t_pipex *pipex_info, int i)
{
	char	*executable_cmd = NULL;
	int	k;


	if(pipex_info->commands->cmd_pers_validation == PER_NOT_EXIST_F_NOK)
		terminate_pipex_with_msg(pipex_info, "Failed :( unfortunately, the command isn't found/exist.\n",
								ERR_CMD_NOT_EXIST, FD2);

	if(pipex_info->commands->cmd_pers_validation == PER_NOT_X_R_NOK)
		terminate_pipex_with_msg(pipex_info, "Failed :( unfortunately, the command isn't executable/readable.\n",
								ERR_CMD_NOT_XR, FD2);

	if (pipex_info->commands[i].full_path != NULL)
	{
		// if (access(pipex_info->commands[i].full_path, F_OK & X_OK & R_OK) == 0)
			execve(executable_cmd, pipex_info->commands[k].cmd_args, pipex_info->env.raw_env);

	}
	k = 0;
	while (pipex_info->env.system_paths[k] != NULL)
	{
		// print_2d_arr(pipex_info->commands[k].cmd_args);
		executable_cmd = get_executable_cmd(pipex_info, pipex_info->env.system_paths[k], pipex_info->commands[k].cmd_args[0]);
		// if (access(executable_cmd, F_OK & X_OK & R_OK) == 0)
		if (execve(executable_cmd, pipex_info->commands[k].cmd_args, pipex_info->env.raw_env) == -1)
			write (2, "khu", 3);

		free(executable_cmd);
		k++;
	}
	terminate_pipex_with_msg(pipex_info, "Failed :( unfortunately, the command isn't found.\n",
							ERR_CMD_NOT_EXIST, FD2);
}



int	handle_input_file(t_pipex *pipex_info, int i, int j)
{
	pid_t	fork_id = fork();
	// pipex_info->pipes.childs_prcs_ids[i] = fork();	// try to fail it
	// if (pipex_info->pipes.childs_prcs_ids[i] == -1)

	if (fork_id == -1)
	{
		display_error_msg("Error: Failed in forking input child.\n", PERROR);
		return (errno);
	}

	// if (pipex_info->pipes.childs_prcs_ids[i] == 0)
	if (fork_id == 0)
	{
		if (pipex_info->files.infile_fd == -1)
			termination_with_all_closing(pipex_info, ERR_INPUT_FILE_HANDLER, i);
		j = 0;
		if (peform_io_dble_dup2(pipex_info->files.infile_fd, pipex_info->pipes.pipes_fds[i][1]) != OK)
			termination_with_all_closing(pipex_info, errno, i);
		close_all_pipes(&(pipex_info->pipes), i);
		close_io_files(&(pipex_info->files));
		execute_cmd(pipex_info, i);
	}
	return (OK);
}

// test


int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex_info;

	if (argc >= 4)
	{
		if (init_pipex_managing(&pipex_info , argc, argv, envp) != (int)OK)
			return (pipex_info.exit_code);

			char	*executable_cmd = NULL;
			int	k = 0;
			executable_cmd = get_executable_cmd(&pipex_info, pipex_info.env.system_paths , pipex_info.commands->cmd_args[k]);
			// if (access(executable_cmd, F_OK & X_OK & R_OK) == 0)
			if (execve(executable_cmd, pipex_info->commands[k].cmd_args, pipex_info->env.raw_env) == -1)
				write (2, "khu", 3);

			free(executable_cmd);
	}
}
