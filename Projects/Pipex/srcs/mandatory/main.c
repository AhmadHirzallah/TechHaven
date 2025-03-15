#include "libft.h"
#include "pipex.h"

/*
	- assign argc & argv and envp
	- calloc the p_ids[] ; memory for child_pids for cmds execution
	- get_path_var() function => (PATH: ....)
		- get_path_var should be first function	before callocing
			!! bec. no free inside needed
	- get_cmdline_args() function => "ls -l -a" [ls] [-l] [-a] :
		(as we have 3rd char*** array for storing array of strings)
		 but out before output redirected to outfile
	- get_io_files_ready() => check access() then open(infile & outfile);;
		if outfile fails; execute first command; and perform everything;
	- pipe_on_pipes_fds() ; calloc pipes (cmdsNbr-1 * int*) &
		 loop calloc(int, 2); => (2nd array) then pipe(fd[2])
*/
int	init_pipex_managing(t_pipex *pipex_info ,int argc, char **argv, char **envp)
{
	ft_bzero(pipex_info, sizeof(t_pipex));
	pipex_info->argc = argc;
	pipex_info->argv = argv;
	pipex_info->env.raw_env = envp;
	pipex_info->files.infile_fd = STDIN_FILENO;
	if(str_cmpr(pipex_info->argv[1], "here_doc") == 0)
	{
		pipex_info->heredoc_delim = pipex_info->argv[2];
		pipex_info->argv++;
		pipex_info->mode = PIPEX_MODE_HEREDOC;
	}
	if (pipex_info->mode == PIPEX_MODE_HEREDOC)
		pipex_info->num_commands = argc - 4;
	else
		pipex_info->num_commands = argc - 3;
	pipex_info->exit_code = get_path_var_and_paths(pipex_info);
	// pipex_info->exit_code = get_cmd();
	get_cmdline_args(pipex_info);
	pipe_on_pipes_fds(pipex_info);
	get_io_files_ready(pipex_info);
	pipex_info->pipes.childs_prcs_ids = ft_calloc(pipex_info->num_commands, sizeof(pid_t));
	if (pipex_info->pipes.childs_prcs_ids == NULL)
		terminate_pipex_with_msg(pipex_info, "ERROR: Fail in CALLOC childs_prcs_ids !",
									 ERR_FAIL_CREATING_PIPE, FD2);
	return ((int)OK);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex_info;

	if (argc >= 4)
	{
		if (init_pipex_managing(&pipex_info , argc, argv, envp) != (int)OK)
			return (pipex_info.exit_code);


		perform_all_cmds(&pipex_info);



		terminate_pipex(&pipex_info, pipex_info.exit_code);


		// Tests:

		// get_path_var(&pipex_info);
		// pipex(argc, argv, envp);


		// char	*executable_cmd = NULL;
		// int	k = 0;
		// executable_cmd = get_executable_cmd(&pipex_info, pipex_info.env.system_paths , pipex_info.commands->cmd_args[k]);
		// // if (access(executable_cmd, F_OK & X_OK & R_OK) == 0)
		// if (execve(executable_cmd, pipex_info., pipex_info->env.raw_env) == -1)
		// 	write (2, "khu", 3);
		// free(executable_cmd);





		// int j, i;
		// i = 0;
		// if (pipex_info.files.infile_fd == -1)
		// 	termination_with_all_closing(&pipex_info, ERR_INPUT_FILE_HANDLER, i);
		// j = 0;
		// // if (peform_io_dble_dup2(pipex_info.files.infile_fd, pipex_info.pipes.pipes_fds[i][1]) != OK)
		// 	// termination_with_all_closing(&pipex_info, errno, i);
		// close_all_pipes(&(pipex_info.pipes), i);
		// close_io_files(&(pipex_info.files));
		// execute_cmd(&pipex_info, i);








		// int i = 0;
		// // handle_here_doc()
		// input_here_doc(&pipex_info, i);
		// if (peform_io_dble_dup2(pipex_info.pipes.pipes_fds[0][0], pipex_info.pipes.pipes_fds[1][1]) != OK)
		// 	termination_with_all_closing(&pipex_info, errno, i);
		// close_all_pipes(&((&pipex_info)->pipes), i);
		// close_io_files(&((&pipex_info)->files));
		// execute_cmd((&pipex_info), i);
		// terminate_pipex((&pipex_info), pipex_info.exit_code);



	}
	else
	{
		display_error_msg("ERROR: Wrong number of arguments !!\n", FD2);
		return (1);
	}
	return (0);
}
