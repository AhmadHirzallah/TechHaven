#include "pipex.h"
#include "libft.h"

int get_path_var(t_pipex *pipex_info)
{
	int i;

	i = 0;
	pipex_info->env.shell_path_var  = NULL;
	while (pipex_info->env.raw_env[i])
	{
		if (ft_strncmp(pipex_info->env.raw_env[i], "PATH=", 5) == 0)
		{
			pipex_info->env.shell_path_var = pipex_info->env.raw_env[i];
			break;
		}
		i++;
	}
	if (pipex_info->env.shell_path_var == NULL)
	{
		// display_error_msg("No Path Variable is found !\n", FD2);
		// return ((int) ERR_NO_PATH_VAR_FOUND);
		terminate_pipex_with_msg(pipex_info, "No Path Variable is found !\n",
									ERR_NO_PATH_VAR_FOUND, FD2);
	}
	return ((int) OK);
}


int	get_cmdline_args(t_pipex *pipex_info)
{
	int	i;

	pipex_info->commands = ft_calloc(pipex_info->num_commands, sizeof(t_command));
	if (pipex_info->commands == NULL)
		terminate_pipex_with_msg(pipex_info, "ERROR: Fail in Command's CALLOC !",
									 ERR_FAIL_CALLOC_CMDS, FD2);

	i = 2;
	while (i < (pipex_info->argc - 1))
	{
		pipex_info->commands[i - 2].cmd_args = split_multi(pipex_info->argv[i], " \t\n");
		i++;
	}
	// print_2d_arr(pipex_info->commands->cmd_args);
	return ((int) OK);
}



int	get_io_files_ready(t_pipex *pipex_info)
{
	if (pipex_info->mode != PIPEX_MODE_HEREDOC)
	{
		if (access(pipex_info->argv[1], F_OK & R_OK) == -1)
		{
			display_error_msg("ERROR of input file:\t", PERROR);
			pipex_info->files.infile_fd = -1;
		}
		else
			pipex_info->files.infile_fd = open(pipex_info->argv[1], O_RDONLY);
	}
	if (access(pipex_info->argv[pipex_info->argc - 1], F_OK) != -1)
	{
		if (access(pipex_info->argv[pipex_info->argc - 1], W_OK) == -1)
		{
			display_error_msg("ERROR of output file:\t", PERROR);
			pipex_info->files.outfile_fd = -1;
		}
	}
	else if (pipex_info->mode == PIPEX_MODE_HEREDOC)
		pipex_info->files.outfile_fd = open(pipex_info->argv[pipex_info->argc - 1], 
											O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		pipex_info->files.outfile_fd = open(pipex_info->argv[pipex_info->argc - 1], 
											O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (OK);
}




/*
	- Pipes are less than executable cmds by 1 
		(2 cmds need 1 pipe) (3 cmds needs 2 pipes).
*/
int	 pipe_on_pipes_fds(t_pipex *pipex_info)
{
	size_t i;

	pipex_info->pipes.num_pipes = pipex_info->num_commands;
	pipex_info->pipes.pipes_fds = ft_calloc(pipex_info->pipes.num_pipes,
											sizeof(int *));
	if (pipex_info->pipes.pipes_fds == NULL)
		terminate_pipex_with_msg(pipex_info, "ERROR: Fail in CALLOC pipes_fds !",
									 ERR_FAIL_CREATING_PIPE, FD2);
	i = 0;
	while (i < pipex_info->pipes.num_pipes)
		pipex_info->pipes.pipes_fds[i++] = ft_calloc(2, sizeof(int));
	i = 0;
	while (i < pipex_info->pipes.num_pipes)
	{
		if (pipe(pipex_info->pipes.pipes_fds[i]) == -1)
			terminate_pipex_with_msg(pipex_info, "ERROR Specification: Fail in creating pipe() !\n",
									 ERR_FAIL_CREATING_PIPE, BOTH_FD2_PERROR);
		i++;
	}
	return ((int) OK);
}


