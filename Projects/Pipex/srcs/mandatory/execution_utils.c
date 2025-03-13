#include "pipex.h"
#include "libft.h"
#include "get_next_line.h"

  
int	handle_here_doc(t_pipex *pipex_info, int i)
{
	char	*user_input = NULL;

	pipex_info->pipes.childs_prcs_ids[i] = fork();	// try to fail it
	if (pipex_info->pipes.childs_prcs_ids[i] == -1)
		terminate_pipex_with_msg(pipex_info, "Failed in forking here_doc child.\n", 
								ERR_FAIL_IN_FORKING_HEREDOC, PERROR);
	if (pipex_info->pipes.childs_prcs_ids[i] == 0)
	{
		while (true)
		{
			ft_putstr_fd("> ", STDIN_FILENO);
			user_input = get_next_line(STDIN_FILENO);
			if (user_input == NULL)
				terminate_pipex_with_msg(pipex_info, "Error in get_next_line input",
										ERR_IN_GNL, FD2);
			if (str_cmpr(user_input, pipex_info->heredoc_delim) == 0)
			{
				free(user_input);
				break;
			}
			ft_putstr_fd(pipex_info->pipes.pipes_fds[i][1], user_input);
			free(user_input);
			
			// close pipes[0][1,0] & fd_outfile
			terminate_pipex(pipex_info, i);
		}
		
	}
	
}
		()
int	handle_input_file(t_pipex *pipex_info, int i)
