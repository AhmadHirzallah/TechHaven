#include "pipex.h"
#include "libft.h"

static int get_infile_ready(t_pipex *pipex_info)
{
	if (pipex_info->mode != PIPEX_MODE_HEREDOC)
	{
		if (access(pipex_info->argv[1], F_OK | R_OK) == -1)
		{
			display_error_msg("ERROR of input file:\t", PERROR);
			pipex_info->files.infile_fd = -1;
			return (-1);
		}
		else
			pipex_info->files.infile_fd = open(pipex_info->argv[1], O_RDONLY);
	}
	return (OK_PRINTF);
}
static int	get_outfile_ready(t_pipex *pipex_info)
{
	if (access(pipex_info->argv[pipex_info->argc - 1], F_OK) == 0)	// IF FAIL return 1 to terminal
	{
		if (access(pipex_info->argv[pipex_info->argc - 1], W_OK) == -1)
		{
			display_error_msg("ERROR of output file:\t", PERROR);
			pipex_info->files.outfile_fd = -1;
			return (-1);
		}
	}
	if (pipex_info->mode == PIPEX_MODE_HEREDOC)
		pipex_info->files.outfile_fd = open(pipex_info->argv[pipex_info->argc - 1],
											O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		pipex_info->files.outfile_fd = open(pipex_info->argv[pipex_info->argc - 1],
											O_CREAT | O_WRONLY | O_TRUNC, 0644);
		return (OK_PRINTF);
}
int	get_io_files_ready(t_pipex *pipex_info)
{
	get_infile_ready(pipex_info);
	get_outfile_ready(pipex_info);
	return (OK_PRINTF);
}
