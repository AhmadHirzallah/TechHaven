#include "libft.h"
#include "pipex.h"

int	perform_both_io_dup2(t_pipex *pipex, int in_stream, int out_stream)
{
	if(dup2(in_stream, STDIN_FILENO) < 0)
	{
		error_msg_termination(pipex, "Error in dup2 on instream\n", PERROR, errno);
	}
	if(dup2(out_stream, STDOUT_FILENO) < 0)
	{
		error_msg_termination(pipex, "Error in dup2 on outstream\n", PERROR, errno);
	}
	return (OK);
}

char	*join_cmds_handler(t_pipex *pipex, char *s1, char *s2, bool free_s2)
{
	char	*temp_cmd = NULL;

	temp_cmd = ft_strjoin(s1, s2);
	if (free_s2 == true)
		free(s2);
	if (temp_cmd == NULL || *temp_cmd == '\0')
		error_msg_termination(pipex, "Failed in mallocing strjoin of cmds.\n", FD2, ERR_FAIL_STRJOIN_MALLOC);
	return (temp_cmd);
}

int	process_here_doc_line(t_pipex *pipex)
{
	char	*user_input = NULL;

	ft_putstr_fd("heredoc> ", STDIN_FILENO);
	user_input = get_next_line(STDIN_FILENO);
	if (user_input == NULL)
		error_msg_termination(pipex,"Error in get_next_line input", FD2, ERR_IN_GNL_MALLOC);
	if (ft_strncmp(user_input, pipex->heredoc_delim, ft_strlen(pipex->heredoc_delim)) == 0 && 
					(ft_strlen(user_input) - 1) == (ft_strlen(pipex->heredoc_delim)))
	{
		free(user_input);
		return (HERE_DOC_STOP);
	}
	ft_putstr_fd(user_input, pipex->pipes_fds[0][1]);
	free(user_input);
	return (OK);
}
