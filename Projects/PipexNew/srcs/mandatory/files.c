#include "libft.h"
#include "pipex.h"

static int get_infile_ready(t_pipex *pipex)
{
	if (pipex->pipex_mode != PIPEX_MODE_HEREDOC)
	{
		if (access(pipex->main_pars.argv[1], F_OK | R_OK) == -1)
		{
			pipex->files.infile_fd = -1;
			pipex->errno_rtrn = errno;
			error_msg("ERROR of input file:\t", PERROR);
			return (pipex->errno_rtrn);
		}
		else
			pipex->files.infile_fd = open(pipex->main_pars.argv[1], O_RDONLY);
	}
	return (OK);
}
int	get_outfile_ready(t_pipex *pipex)
{
	if (access(pipex->main_pars.argv[pipex->main_pars.argc - 1], F_OK) == 0)	// IF FAIL return 1 to terminal
	{
		if (access(pipex->main_pars.argv[pipex->main_pars.argc - 1], W_OK) == -1)
		{
			pipex->errno_rtrn = errno;
			error_msg("ERROR in outfile:\t", PERROR);
			pipex->files.outfile_fd = -1;
			return (pipex->errno_rtrn);
		}
	}
	if (pipex->pipex_mode == PIPEX_MODE_HEREDOC)
		pipex->files.outfile_fd = open(pipex->main_pars.argv[pipex->main_pars.argc - 1],
											O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		pipex->files.outfile_fd = open(pipex->main_pars.argv[pipex->main_pars.argc - 1],
											O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if ((access(pipex->main_pars.argv[pipex->main_pars.argc - 1], F_OK | W_OK) == -1) 
		|| pipex->files.outfile_fd == -1)
	{
		pipex->files.outfile_fd = -1;
		pipex->errno_rtrn = errno;
		error_msg("ERROR in outfile:\t", PERROR);
		return (pipex->errno_rtrn);
	}
	return (OK);
}

int	get_io_files_ready(t_pipex *pipex)
{
	get_infile_ready(pipex);
	return (get_outfile_ready(pipex));
}