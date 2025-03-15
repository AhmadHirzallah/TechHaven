#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"

/*
** Frees the memory allocated for system_paths.
** system_paths is expected to be a NULL-terminated array of strings.
*/
void	free_system_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->system_paths)
	{
		while (pipex->system_paths[i])
		{
			free(pipex->system_paths[i]);
			i++;
		}
		free(pipex->system_paths);
		pipex->system_paths = NULL;
	}
}

/*
** Frees the memory allocated for cmds_args.
** cmds_args is a 2D array (array of strings for each command)
** and pipex->num_cmds_args tells how many command arrays there are.
*/
void	free_cmds_args(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	if (pipex->cmds_args)
	{
		while (i < pipex->num_cmds_args)
		{
			if (pipex->cmds_args[i])
			{
				j = 0;
				while (pipex->cmds_args[i][j])
				{
					free(pipex->cmds_args[i][j]);
					j++;
				}
				free(pipex->cmds_args[i]);
				pipex->cmds_args[i] = NULL;
			}
			i++;
		}
		free(pipex->cmds_args);
		pipex->cmds_args = NULL;
	}
}

/*
** Frees the memory allocated for pipes_fds.
** Each element in pipes_fds is a dynamically allocated array of two ints.
*/
void	free_pipes_fds(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->pipes_fds)
	{
		while (i < pipex->num_cmds_args - 1)
		{
			if (pipex->pipes_fds[i])
			{
				free(pipex->pipes_fds[i]);
				pipex->pipes_fds[i] = NULL;
			}
			i++;
		}
		free(pipex->pipes_fds);
		pipex->pipes_fds = NULL;
	}
}

/*
** Frees the memory allocated for childs_pids.
*/
void	free_childs_pids(t_pipex *pipex)
{
	if (pipex->childs_pids)
	{
		free(pipex->childs_pids);
		pipex->childs_pids = NULL;
	}
}

/*
** Main cleanup function that calls each of the above functions.
** This should be called before terminating the program or exiting from an error.
*/
void	cleanup_pipex(t_pipex *pipex)
{
	close_all_files(pipex);
	close_all_pipes(pipex);
	free_system_paths(pipex);
	free_cmds_args(pipex);
	free_pipes_fds(pipex);
	free_childs_pids(pipex);
}
