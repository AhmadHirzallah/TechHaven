#include "pipex.h"
#include "libft.h"

int get_path_var_and_paths(t_pipex *pipex_info)
{
	int i;

	i = 0;
	while (pipex_info->env.raw_env[i])
	{
		if (ft_strncmp(pipex_info->env.raw_env[i], "PATH=", 5) == 0)
		{
			pipex_info->env.shell_path_var = pipex_info->env.raw_env[i];
			if (pipex_info->env.shell_path_var == NULL)
				terminate_pipex_with_msg(pipex_info, "No Path Variable is found !\n",
											ERR_NO_PATH_VAR_FOUND, FD2);
			pipex_info->env.system_paths = ft_split((pipex_info->env.shell_path_var + 5), ':');
			if (pipex_info->env.system_paths == NULL)
				terminate_pipex_with_msg(pipex_info, "No System PATHS= is found !\n",
										ERR_NO_PATH_VAR_FOUND, FD2);
			break;
		}
		i++;
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

	i = 0;
	while (i < (pipex_info->num_commands))
	{
		process_any_cmd(pipex_info, i);
		i++;
	}
	// print_2d_arr(pipex_info->commands->cmd_args);
	return ((int) OK);
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
	while (i < pipex_info->pipes.num_pipes)	/// ADD PROTECTION
	{
		pipex_info->pipes.pipes_fds[i] = ft_calloc(2, sizeof(int));
		if (pipex_info->pipes.pipes_fds[i++] == NULL)
		terminate_pipex_with_msg(pipex_info, "ERROR Specification: Fail in creating pipe() !\n",
								 ERR_FAIL_CREATING_PIPE, BOTH_FD2_PERROR);
	}
	i = 0;
	while (i < pipex_info->pipes.num_pipes)
	{
		if (pipe(pipex_info->pipes.pipes_fds[i]) == -1)
		{
			pipex_info->last_pipe_index = i;
			terminate_pipex_with_msg(pipex_info, "ERROR Specification: Fail in creating pipe() !\n",
									 ERR_FAIL_CREATING_PIPE, BOTH_FD2_PERROR);
		}
		i++;
	}
	return ((int) OK);
}
