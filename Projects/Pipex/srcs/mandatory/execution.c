#include "pipex.h"
#include "libft.h"

static int	handle_input_piping(t_pipex *pipex_info, int i, int j)
{
	if (pipex_info->mode == PIPEX_MODE_HEREDOC)
		handle_here_doc(pipex_info, i);
	else
		handle_input_file(pipex_info, i, j);

	return 0;
}


static int	perform_mid_pipes_cmds(t_pipex *pipex_info, int i, int j)
{
	while (i < (pipex_info->num_commands - 1))
	{
		pipex_info->pipes.childs_prcs_ids[i] = fork();	// try to fail it
		if (pipex_info->pipes.childs_prcs_ids[i] == -1)
		{
			display_error_msg("Error: Failed in forking mid pipes child.\n", PERROR);
			return (errno);
		}
		if (pipex_info->pipes.childs_prcs_ids[i] == 0)
		{
			if (peform_io_dble_dup2(pipex_info->pipes.pipes_fds[i - 1][0], pipex_info->pipes.pipes_fds[i][1]) != OK)
				termination_with_all_closing(pipex_info, errno, i);
			close_all_pipes(&(pipex_info->pipes), i);
			close_io_files(&(pipex_info->files));
			execute_cmd(pipex_info, i);
			i++;
		}
	}
	return OK;
}

static int	perform_last_cmd(t_pipex *pipex_info, int i, int j)
{
	i = pipex_info->pipes.num_pipes - 1;
	pipex_info->pipes.childs_prcs_ids[i] = fork();	// try to fail it
	if (pipex_info->pipes.childs_prcs_ids[i] == -1)
	{
		display_error_msg("Error: Failed in forking last pipe child.\n", PERROR);
		return (errno);
	}
	if (pipex_info->pipes.childs_prcs_ids[i] == 0)
	{
		if (pipex_info->files.outfile_fd == -1)
			termination_with_all_closing(pipex_info, ERR_INPUT_FILE_HANDLER, i);
		j = 0;
		if (peform_io_dble_dup2(pipex_info->pipes.pipes_fds[i - 1][0], pipex_info->files.outfile_fd) != OK)
			termination_with_all_closing(pipex_info, errno, i);
		close_all_pipes(&(pipex_info->pipes), i);
		close_io_files(&(pipex_info->files));
		execute_cmd(pipex_info, i);
	}
	return OK;
}


int	perform_all_cmds(t_pipex *pipex_info)
{
	int i;
	int j;

	i = 0;
	j = 0;
	handle_input_piping(pipex_info, i, j);
	i++;
	perform_mid_pipes_cmds(pipex_info, i, j);
	perform_last_cmd(pipex_info, i, j);
	return 0;
}
