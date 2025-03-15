/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:30:33 by ahirzall          #+#    #+#             */
/*   Updated: 2025/03/16 00:30:34 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	open_pipes(t_pipex *pipex, int i)
{
	pipex->pipes_fds = ft_calloc(pipex->num_cmds_args - 1, sizeof(int *));
	if (pipex->pipes_fds == NULL)
		error_msg_termination(pipex, "ERROR; Malloc Failes.\n", FD2,
			(int)ERR_FAIL_CALLOC_PIPES);
	i = 0;
	while (i < (pipex->num_cmds_args - 1))
	{
		pipex->pipes_fds[i] = ft_calloc(2, sizeof(int));
		if (!pipex->pipes_fds[i])
			error_msg_termination(pipex, "ERROR; Malloc Failes.\n", FD2,
				(int)ERR_FAIL_CALLOC_PIPES);
		i++;
	}
	i = 0;
	while (i < pipex->num_cmds_args - 1)
	{
		if (pipe(pipex->pipes_fds[i]) == -1)
			error_msg_termination(pipex, "ERROR! pipe() failed.\n", PERROR,
				errno);
		i++;
	}
	return (OK);
}
