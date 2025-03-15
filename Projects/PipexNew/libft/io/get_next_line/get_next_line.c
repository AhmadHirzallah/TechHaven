/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:43:35 by ahirzall          #+#    #+#             */
/*   Updated: 2024/10/25 11:14:29 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_copy_from_leftover(t_gnl *gnl)
{
	long	i;
	long	j;
	long	k;

	i = 0;
	while (gnl->leftover[gnl->fd][i] != '\n')
		i++;
	gnl->line = malloc(i + 2);
	if (!gnl->line)
	{
		gnl->count_newlns[gnl->fd] = 0;
		gnl->size_lft_ovr[gnl->fd] = 0;
		return ;
	}
	gnl->count_newlns[gnl->fd]--;
	j = -1;
	while (++j <= i)
		gnl->line[j] = gnl->leftover[gnl->fd][j];
	gnl->line[j] = '\0';
	k = -1;
	while ((j + (++k)) < (gnl->size_lft_ovr[gnl->fd]))
		gnl->leftover[gnl->fd][k] = gnl->leftover[gnl->fd][j + k];
	gnl->size_lft_ovr[gnl->fd] = k;
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;

	gnl.line = NULL;
	gnl.fd = fd;
	if (fd > 1023 || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl.count_newlns[fd])
	{
		gnl.what_rtrn = gnl_read_file(&gnl, -1, 0, 0);
		if (gnl.what_rtrn != OKK)
			return (NULL);
	}
	else
		gnl_copy_from_leftover(&gnl);
	return (gnl.line);
}
