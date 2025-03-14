#include "pipex.h"
#include "libft.h"

static int	process_pathed_entered_cmd(t_pipex *pipex_info, int *i)
{
	t_command *cmd_ptr;

	if (ft_strchr(pipex_info->argv[*i], '/') != NULL)
	{
		pipex_info->commands[*i - 2].cmd_args = ft_split(pipex_info->argv[*i], ' ');
		if (pipex_info->commands[*i - 2].cmd_args == NULL)
			terminate_pipex_with_msg(pipex_info, "No Command is found!\n",
									ERR_NO_PATH_VAR_FOUND, FD2);
		// print_2d_arr(pipex_info->commands[*i - 2].cmd_args);
		pipex_info->commands[*i - 2].full_path = pipex_info->commands[*i - 2].cmd_args[0];
		// pipex_info->commands[*i - 2].full_path = ft_strdup(pipex_info->argv[*i]);
		cmd_ptr = &(pipex_info->commands[*i - 2]);
		// is_valid_cmd_check(pipex_info, pipex_info->commands[*i - 2].full_path, &(pipex_info->commands[*i - 2]));
		is_valid_cmd_check(pipex_info, cmd_ptr->full_path, &cmd_ptr);
		(*i)++;
		return 1;
	}
	return 0;
}

// static int	full_path_genaration(t_pipex *pipex_info, char *exe_cmd, int i)
// {


// }

static int	process_general_cmd(t_pipex *pipex_info, int *i)
{
	pipex_info->commands[*i - 2].cmd_args = split_multi(pipex_info->argv[*i], " \t\n");
	// print_2d_arr(pipex_info->commands[*i - 2].cmd_args);
	if (pipex_info->commands[*i - 2].cmd_args == NULL || pipex_info->commands[*i - 2].cmd_args[0] == NULL)
	{
		pipex_info->commands->cmd_pers_validation = false;
		return (ERR_CMD_NOT_EXIST);
	}

	// full_path_genaration(pipex_info, pipex_info->commands[*i - 2].cmd_args[0], *i);
	// pipex_info->commands->cmd_pers_validation = true;
	(*i)++;
	pipex_info->commands->cmd_pers_validation = PERMISSIONS_OK;
	return (OK);
}


int	process_any_cmd(t_pipex *pipex_info, int *i)
{
	pipex_info->commands[*i - 2].full_path = NULL;
	if (process_pathed_entered_cmd(pipex_info, i) == 1)
		return (1);
	return (process_general_cmd(pipex_info, i));
}
