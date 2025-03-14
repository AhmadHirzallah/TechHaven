#include "pipex.h"
#include "libft.h"
#include "stdio.h"

void	termination_with_all_closing(t_pipex *pipex_info, t_returns_exits exit_code, int i)
{
	close_all_pipes(&(pipex_info->pipes), i);
	close_io_files(&(pipex_info->files));
	terminate_pipex(pipex_info, exit_code);
}

void display_error_msg(char *msg, t_error_print type)
{
	if (type == PERROR)
		perror("\nERROR:\t");
	if (type == FD2)
		ft_putstr_fd(msg, 2);
	if (type == BOTH_FD2_PERROR)
	{
		perror("\nERROR Type:\t");
		ft_putstr_fd(msg, 2);
	}

}

int terminate_pipex(t_pipex *pipex_info, t_returns_exits exit_code)
{
	size_t i;

	if (pipex_info->pipes.childs_prcs_ids)
		free(pipex_info->pipes.childs_prcs_ids);
	if (pipex_info->env.system_paths && pipex_info->env.system_paths[0])
		free_2d_arr(pipex_info->env.system_paths);
	i = 0;
	while (i < pipex_info->num_commands)
	{
		// if (pipex_info->commands[i].cmd_args && pipex_info->commands[i].cmd_args[0])
		free_2d_arr(pipex_info->commands[i].cmd_args);
		if (pipex_info->commands[i].full_path != NULL)
			free(pipex_info->commands[i].full_path);
		i++;
	}
	free(pipex_info->commands);
	i = 0;
	while (i < (pipex_info->num_commands - 1))
		free(pipex_info->pipes.pipes_fds[i++]);
	if (pipex_info->pipes.pipes_fds)
		free(pipex_info->pipes.pipes_fds);
	return ((int)exit_code);
}

void terminate_pipex_with_msg(t_pipex *pipex_info, char *msg, t_returns_exits exit_code, t_error_print type)
{
	close_io_files(&(pipex_info->files));
	close_all_pipes(&(pipex_info->pipes), 0);
	display_error_msg(msg, type);
	exit(terminate_pipex(pipex_info, exit_code));
}

void term_pipex_pipes_handling(t_pipex *pipex_info, char *msg, t_returns_exits exit_code, t_error_print type)
{
	close_io_files(&(pipex_info->files));
	close_all_pipes_till_index(&(pipex_info->pipes), 0, pipex_info->last_pipe_index);
	display_error_msg(msg, type);
	exit(terminate_pipex(pipex_info, exit_code));
}
