#include "libft.h"
#include "pipex.h"

void input_here_doc(t_pipex *pipex)
{
	char	*user_input = NULL;

	while (true)
	{
		ft_putstr_fd("heredoc> ", STDIN_FILENO);
		user_input = get_next_line(STDIN_FILENO);
		if (user_input == NULL)	// this termination should be freeing everything :)
			error_msg_termination(pipex,"Error in get_next_line input", FD2, ERR_IN_GNL_MALLOC);
		if (ft_strncmp(user_input, pipex->heredoc_delim, ft_strlen(pipex->heredoc_delim)) == 0 && 
						(ft_strlen(user_input) - 1) == (ft_strlen(pipex->heredoc_delim)))
			break;
		ft_putstr_fd(user_input, pipex->pipes_fds[0][1]);
		free(user_input);
	}
	free(user_input);
}

int is_valid_cmd_checker(t_pipex *pipex, char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		pipex->errno_rtrn = errno;
		return (ERR_CMD_NOT_EXIST);
	}	
	if (access(cmd, R_OK | X_OK) == -1)
	{
		pipex->errno_rtrn = errno;
		return (ERR_CMD_NOT_XR);
	}
	return (OK);
}

static int process_pathed_entered_cmd(t_pipex *pipex, char **cmd_args, char **complete_cmd, int i)
{
	if (cmd_args == NULL || cmd_args[i] == NULL)
		return ((int)PER_NOT_EXIST_F_NOK);
	else if (ft_strchr(cmd_args[i], '/') != NULL)
	{
		if (is_valid_cmd_checker(pipex, cmd_args[i]) != OK)
			error_msg_termination(pipex, "ERROR not valid command.\t", PERROR, pipex->errno_rtrn);
			// exit (pipex->errno_rtrn);
		else
		{
			*complete_cmd = cmd_args[i];
			return (OK);
		}
	}
	return (1);
}

static int process_general_cmd(t_pipex *pipex, char **cmd_args, char **complete_cmd, int i)
{
	char	*temp_cmd = NULL;
	int		validation_return;

	validation_return = 0;
	temp_cmd = join_cmds_handler(pipex, "/", cmd_args[i], false);
	i = 0;
	while (pipex->system_paths[i])
	{
		(*complete_cmd) = join_cmds_handler(pipex, pipex->system_paths[i], temp_cmd, true);
		// (*complete_cmd) = ft_strjoin(pipex->system_paths[i], temp_cmd);
		// if ((*complete_cmd) == NULL || (*complete_cmd)[i] == '\0')
		// {
		// 	free(temp_cmd);
		// 	error_msg_termination(pipex,"Failed in mallocing strjoin of child process.\n", FD2, ERR_FAIL_STRJOIN_MALLOC);
		// }
		validation_return = is_valid_cmd_checker(pipex, (*complete_cmd));
		if (validation_return == OK)
		{
			free(temp_cmd);
			return (OK);
		}
		i++;
	}
	free(temp_cmd);
	return ((int)validation_return);
}

int	processing_cmd_args(t_pipex *pipex, char *cmd_args, char **complete_cmd, int i)
{
	if (process_pathed_entered_cmd(pipex, &cmd_args, complete_cmd, i) == OK)
		return (OK);
	return (process_general_cmd(pipex, &cmd_args, complete_cmd, i));
}
