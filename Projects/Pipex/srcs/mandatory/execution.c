#include "pipex.h"
#include "libft.h"

static int	handle_input_piping(t_pipex *pipex_info, int i, int j)
{
	if (pipex_info->mode == PIPEX_MODE_HEREDOC)
		handle_here_doc();
	else
		handle_input_file()
	

	return 0;
}


static int	perform_mid_pipes_cmds(t_pipex *pipex_info, int i, int j)
{

	return 0;
}

static int	perform_last_cmd(t_pipex *pipex_info, int i, int j)
{

	return 0;
}


int	perform_all_cmds(t_pipex *pipex_info)
{
	int i;
	int j;

	i = 0;
	j = 0;
	handle_input_piping(pipex_info, i, j);
	perform_mid_pipes_cmds(pipex_info, i, j);
	perform_last_cmd(pipex_info, i, j);
	return 0;
}