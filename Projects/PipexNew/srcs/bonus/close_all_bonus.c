/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:30:08 by ahirzall          #+#    #+#             */
/*   Updated: 2025/03/16 03:06:48 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Closes a single pipe represented by an array of two file descriptors.
** It checks if the descriptor is valid (> 2) before calling close.
*/
void	close_io_pipes(t_pipex *pipex, int *pipes_fds)
{
	(void)pipex;
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
			close_io_pipes(pipex, pipex->pipes_fds[i]);
		i++;
	}
}

/*
** Closes the file descriptors for both the infile and outfile,
** if they are valid (>= 0).
*/
void	close_all_files(t_pipex *pipex)
{
	if (pipex->files.infile_fd > 2)
		close(pipex->files.infile_fd);
	if (pipex->files.outfile_fd > 2)
		close(pipex->files.outfile_fd);
}
