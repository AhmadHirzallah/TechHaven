#include "pipex.h"
#include "libft.h"

void error_msg(char *msg, t_error_print type)
{
	if (type == PERROR)
	{
		ft_putstr_fd(msg, 2);
		perror("\nERROR:\t");
	}
	else if (type == FD2)
		ft_putstr_fd(msg, 2);
	else if (type == BOTH_FD2_PERROR)
	{
		perror("\nERROR Type:\t");
		ft_putstr_fd(msg, 2);
	}
	else if (type == STDOUT_FILENO)
		ft_putstr_fd(msg, 1);
}

void error_msg_termination(t_pipex *pipex, char *msg, t_error_print type, int exit_code)
{
	error_msg(msg, type);
	cleanup_pipex(pipex);
	exit(exit_code);
}
