#include "pipex.h"
#include "libft.h"

/*
	- args nbr:			   1	  2		      3	        4        5
	- randomly:			./pipex infile   "grep  a1"   "wc -w"   outfile
	- args nbr:			   1	  2		    3	    4        5		    6
	- here_doc:			./pipex here_doc   END    "cat"    "wc -l"    output.txt
*/
void	process_characteristics(t_pipex *pipex)
{
	if(str_cmpr(pipex->main_pars.argv[1], "here_doc") == 0)
	{
		pipex->heredoc_delim = pipex->main_pars.argv[2];
		pipex->pipex_mode = PIPEX_MODE_HEREDOC;
		// pipex->num_commands = pipex->main_pars.argc - 4;
		return ;
	}
	pipex->pipex_mode = PIPEX_MODE_INFILE;
	// pipex->num_commands = pipex->main_pars.argc - 3;
	return ;
}

static char	*get_shell_path_var(t_pipex *pipex, char **raw_envp)
{
	int i;
	char	*path_var = NULL;

	i = 0;
	while (raw_envp[i] != NULL)
	{
		if (ft_strncmp(raw_envp[i], "PATH=", 5) == 0)
		{
			path_var = raw_envp[i];
			return (path_var);
		}
		i++;
	}
	if (path_var == NULL)
		error_msg_termination(pipex, "No Path Variable is found.\n", FD2, (int)ERR_CMD_NOT_EXIST);
	return (NULL);
}

 char	**extract_all_paths(t_pipex *pipex)
 {
	char	*path_var = NULL;
	
	path_var = get_shell_path_var(pipex, pipex->main_pars.raw_envp);
	if (path_var == NULL)
		error_msg_termination(pipex, "No Path Variable is found.\n", FD2, (int)ERR_CMD_NOT_EXIST);
	pipex->system_paths = ft_split((path_var + 5), ':');
	if (pipex->system_paths == NULL)
		error_msg_termination(pipex, "No Path Variable is found.\n", FD2, (int)ERR_FAIL_CALLOC_SYS_PATHS);
	return (pipex->system_paths);
 }
