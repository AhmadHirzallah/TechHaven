#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"

/*
** Closes a single pipe represented by an array of two file descriptors.
** It checks if the descriptor is valid (> 2) before calling close.
*/
void	close_io_pipes(int *pipes_fds)
{
	if (pipes_fds[0] > 2)
		close(pipes_fds[0]);
	if (pipes_fds[1] > 2)
		close(pipes_fds[1]);
}

/*
** Iterates over all pipes and closes them using ft_close_io_pipes.
** The total number of pipes is (pipex->num_cmds_args - 1).
*/
void	close_all_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->num_cmds_args - 1)
	{
		if (pipex->pipes_fds && pipex->pipes_fds[i])
			close_io_pipes(pipex->pipes_fds[i]);
		i++;
	}
}

/*
** Closes the file descriptors for both the infile and outfile,
** if they are valid (>= 0).
*/
void	close_all_files(t_pipex *pipex)
{
	if (pipex->files.infile_fd >= 0)
		close(pipex->files.infile_fd);

	if (pipex->files.outfile_fd >= 0)
		close(pipex->files.outfile_fd);
}

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
	ft_close_all_files(pipex);
	ft_close_all_pipes(pipex);
	ft_free_system_paths(pipex);
	ft_free_cmds_args(pipex);
	ft_free_pipes_fds(pipex);
	ft_free_childs_pids(pipex);
}
