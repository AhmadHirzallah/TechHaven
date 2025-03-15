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

char	*join_cmds_handler(t_pipex *pipex, char const *s1, char const *s2, bool free_s2)
{
	char	*temp_cmd = NULL;

	temp_cmd = ft_strjoin(s1, s2);
	if (free_s2 == true)
		free(s2);
	if (temp_cmd == NULL || *temp_cmd == '\0')
		error_msg_termination(pipex, "Failed in mallocing strjoin of cmds.\n", FD2, ERR_FAIL_STRJOIN_MALLOC);
	return (temp_cmd);
}
