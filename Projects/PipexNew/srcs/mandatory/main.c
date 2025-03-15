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
int	initialize_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->main_pars.argc = argc;
	pipex->main_pars.argv = argv;
	pipex->main_pars.raw_envp = envp;
	process_characteristics(pipex);
	pipex->system_paths = extract_all_paths(pipex); 
	pipex->cmds_args = get_cmds_args(pipex, 0);
	get_io_files_ready(pipex);
	open_pipes(pipex, 0);
	pipex->childs_pids = ft_calloc(pipex->num_cmds_args, sizeof(int));
	if (pipex->childs_pids == NULL)
		error_msg_termination(pipex, "ERROR: Failed in child Processes IDS calloc.\n", FD2, (int)ERR_FAIL_CALLOC_CHILD_PIDS);
	return (OK);
}

int	perform_all_cmds(t_pipex *pipex)
{
	int i;

	i = 0;
	if (pipex->pipex_mode == PIPEX_MODE_INFILE)
		handle_input_cmd(pipex, i);
	else if (pipex->pipex_mode == PIPEX_MODE_HEREDOC)
		handle_here_doc(pipex, i);
	i++;
	perform_middle_pipes_cmds(pipex, i);
	perform_last_cmd(pipex, i);
	close_all_pipes(pipex);
	close_all_files(pipex);
	return (OK);
}

int	parent_wait_for_all(t_pipex *pipex)
{
	int			i;
	int			waitpid_status;

	i = 0;
	while (i < pipex->num_cmds_args - 1)
	{
		waitpid(pipex->childs_pids[i], NULL, 0);
		i++;
	}
	waitpid(pipex->childs_pids[i], &waitpid_status, 0);
	if (WIFEXITED(waitpid_status))
	{
		cleanup_pipex(pipex);
		exit (WEXITSTATUS(waitpid_status));
	}
	cleanup_pipex(pipex);
	exit (WTERMSIG(waitpid_status) + 128);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;

	ft_bzero(&pipex, sizeof(t_pipex));
	if (argc >= 4)
	{
		initialize_pipex(&pipex, argc, argv, envp);
		perform_all_cmds(&pipex);
		parent_wait_for_all(&pipex);
	}
	else
	{
		error_msg("ERROR: Wrong number of arguments !!\n", FD2);
		return (ERR_WRNG_ARGS_NBR);
	}
	return (OK);











		// if (initialize_pipex(&pipex_info , argc, argv, envp) != (int)OK)
		// 	return (pipex_info.exit_code);


		// perform_all_cmds(&pipex_info);



		// terminate_pipex(&pipex_info, pipex_info.exit_code);


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



	// }

}
