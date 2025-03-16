/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:30:14 by ahirzall          #+#    #+#             */
/*   Updated: 2025/03/16 03:06:55 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static int	get_infile_ready(t_pipex *pipex)
{
	if (pipex->pipex_mode != PIPEX_MODE_HEREDOC)
	{
		if (access(pipex->main_pars.argv[1], F_OK | R_OK) == -1)
		{
			pipex->files.infile_fd = -1;
			pipex->errno_rtrn = errno;
			return (pipex->errno_rtrn);
		}
		else
			pipex->files.infile_fd = open(pipex->main_pars.argv[1], O_RDONLY);
	}
	return (OK);
}

static int	handle_outfile_deny_access(t_pipex *pipex)
{
	int	i;

	i = pipex->main_pars.argc - 1;
	if (access(pipex->main_pars.argv[i], F_OK) == 0)
	{
		if (access(pipex->main_pars.argv[i], W_OK) == -1)
		{
			pipex->errno_rtrn = errno;
			pipex->files.outfile_fd = -1;
			exit (pipex->errno_rtrn);
		}
	}
	return (OK);
}

int	get_outfile_ready(t_pipex *pipex)
{
	int	i;

	i = handle_outfile_deny_access(pipex);
	if (i != OK)
		return (pipex->errno_rtrn);
	i = pipex->main_pars.argc - 1;
	if (pipex->pipex_mode == PIPEX_MODE_HEREDOC)
		pipex->files.outfile_fd = open(pipex->main_pars.argv[i],
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		pipex->files.outfile_fd = open(pipex->main_pars.argv[i],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if ((access(pipex->main_pars.argv[pipex->main_pars.argc - 1],
				F_OK | W_OK) == -1) || pipex->files.outfile_fd == -1)
	{
		pipex->files.outfile_fd = -1;
		pipex->errno_rtrn = errno;
		return (pipex->errno_rtrn);
	}
	return (OK);
}

int	get_io_files_ready(t_pipex *pipex)
{
	get_infile_ready(pipex);
	return (get_outfile_ready(pipex));
}
