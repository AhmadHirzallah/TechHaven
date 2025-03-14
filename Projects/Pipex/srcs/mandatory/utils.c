#include "pipex.h"
#include "libft.h"

int	peform_io_dble_dup2(int in_stream, int out_stream)
{

	if(dup2(in_stream, STDIN_FILENO) == -1)
	{
		display_error_msg("Error in dup2 on instream:\t", PERROR);
		return (errno);
	}
	if(dup2(out_stream, STDOUT_FILENO) == -1)
	{
		display_error_msg("Error in dup2 on outstream:\t", PERROR);
		return (errno);
	}
	return (OK);
}

void	close_io_pipes(int *pipes_fds)
{
	if (pipes_fds[0] > 2)
		close(pipes_fds[0]);
	if (pipes_fds[1] > 2)
		close(pipes_fds[1]);
}
void	close_all_pipes_till_index(t_pipe_context *pipex_info, int i, int end)
{
	i = 0;
	while (i < end)
	{
		close_io_pipes(pipex_info->pipes_fds[i]);
		i++;
	}
}

void	close_all_pipes(t_pipe_context *pipex_info, int i)
{
	i = 0;
	while (i < pipex_info->num_pipes)
	{
		close_io_pipes(pipex_info->pipes_fds[i]);
		i++;
	}
}

void close_io_files(t_io_files *files)
{
    if (files->infile_fd > 2)
        close(files->infile_fd);
    if (files->outfile_fd > 2)
        close(files->outfile_fd);
}

// void close_specifying(t_pipex *pipex_info, )
int	is_valid_cmd_check(t_pipex *pipex_info, char *full_path_cmd, t_command **commands)
{
	if (access(full_path_cmd, F_OK) == -1) //& X_OK & R_OK) == -1)
	{
		(*commands)->cmd_pers_validation = PER_NOT_EXIST_F_NOK;
		pipex_info->exit_code = ERR_CMD_NOT_EXIST;
		return (ERR_CMD_NOT_EXIST);
	}

	if (access(full_path_cmd, R_OK & X_OK) == -1) //& X_OK & R_OK) == -1)
	{
		(*commands)->cmd_pers_validation = PER_NOT_X_R_NOK;
		pipex_info->exit_code = ERR_CMD_NOT_XR;
		return (ERR_CMD_NOT_XR);
	}
	(*commands)->cmd_pers_validation = PERMISSIONS_OK;
	pipex_info->exit_code = OK;
	return (OK);
}
