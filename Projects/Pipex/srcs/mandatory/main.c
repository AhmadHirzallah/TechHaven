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
	pipex_info->argc = argc;
	pipex_info->argv = argv;
	pipex_info->env.raw_env = envp;
	pipex_info->env.system_paths = NULL;
	pipex_info->files.infile_fd = STDIN_FILENO;
	if(str_cmpr(pipex_info->argv[1], "here_doc") == 0)
	{
		pipex_info->mode = PIPEX_MODE_HEREDOC;
		pipex_info->heredoc_delim = pipex_info->argv[2];
	}
	if (pipex_info->mode == PIPEX_MODE_HEREDOC)
		pipex_info->num_commands = argc - 4;
	else
		pipex_info->num_commands = argc - 3;
	pipex_info->exit_code = get_path_var(pipex_info);
	get_cmdline_args(pipex_info);
	pipe_on_pipes_fds(pipex_info);
	get_io_files_ready(pipex_info);
	pipex_info->pipes.childs_prcs_ids = ft_calloc(pipex_info->num_commands, sizeof(int));
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

		// perform_all_cmds(&pipex_info);




		terminate_pipex(&pipex_info, pipex_info.exit_code);
		// Tests:
		
		// get_path_var(&pipex_info);
		// pipex(argc, argv, envp);
	}
	else
	{
		display_error_msg("ERROR: Wrong number of arguments !!\n", FD2);
		return (1);
	}
	return (0);
}
