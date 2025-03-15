/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:43:50 by ahirzall          #+#    #+#             */
/*   Updated: 2024/10/25 11:14:47 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_rtrnss	gnl_double_temp(t_gnl *gnl, long *iter)
{
	long	i;

	(*iter)++;
	if (((*iter + 2) * BUFFER_SIZE) > gnl->size_temp)
	{
		gnl->temp2 = malloc((gnl->size_temp) * 2);
		if (!gnl->temp2)
		{
			free(gnl->temp);
			return (DOUBLE_TMP_FAIL);
		}
		gnl->size_temp *= 2;
		i = -1;
		while (gnl->temp && (++i < gnl->length_temp))
			gnl->temp2[i] = gnl->temp[i];
		free(gnl->temp);
		gnl->temp = gnl->temp2;
	}
	return (OKK);
}

static t_rtrnss	gnl_line_setting_up(t_gnl *gnl, long r)
{
	if (gnl->temp && gnl->length_temp)
	{
		gnl->line = malloc(gnl->length_temp + 1);
		if (!gnl->line)
		{
			free(gnl->temp);
			return (SETTING_UP_FAIL);
		}
		r = -1;
		while (gnl->temp && (++r < gnl->length_temp))
			gnl->line[r] = gnl->temp[r];
		gnl->line[r] = '\0';
	}
	free(gnl->temp);
	return (OKK);
}

static t_rtrnss	gnl_initialization(t_gnl *gnl, long *r)
{
	gnl->size_temp = BUFFER_SIZE * 2;
	gnl->temp = malloc(gnl->size_temp);
	if (!gnl->temp)
		return (INITIALIZATION_FAIL);
	*r = -1;
	while (++(*r) < gnl->size_lft_ovr[gnl->fd])
		gnl->temp[*r] = gnl->leftover[gnl->fd][*r];
	gnl->length_temp = gnl->size_lft_ovr[gnl->fd];
	gnl->size_lft_ovr[gnl->fd] = 0;
	gnl->count_newlns[gnl->fd] = 0;
	*r = 1;
	gnl->buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!gnl->buffer)
	{
		free(gnl->temp);
		return (INITIALIZATION_FAIL);
	}
	gnl->buffer[BUFFER_SIZE] = '\0';
	return (OKK);
}

static t_rtrnss	gnl_data_directing(t_gnl *gnl, long r, long i)
{
	i = 0;
	while (i < r && (!i || gnl->buffer[i - 1] != '\n'))
		gnl->temp[gnl->length_temp++] = gnl->buffer[i++];
	while (i < r)
	{
		if (gnl->buffer[i] == '\n')
			gnl->count_newlns[gnl->fd]++;
		gnl->leftover[gnl->fd][gnl->size_lft_ovr[gnl->fd]++] = gnl->buffer[i++];
	}
	if (gnl->length_temp && gnl->temp[gnl->length_temp - 1] == '\n')
		return (FULL_LINE_UP);
	return (CONTIN_TILL_FULL_LINE_UP);
}

t_rtrnss	gnl_read_file(t_gnl *gnl, long r, long i, long iter)
{
	if (gnl_initialization(gnl, &r) != OKK)
		return (INITIALIZATION_FAIL);
	while (r > 0 && gnl->temp && !gnl->count_newlns[gnl->fd])
	{
		r = read(gnl->fd, gnl->buffer, BUFFER_SIZE);
		if (r < 0)
		{
			free(gnl->buffer);
			free(gnl->temp);
			return (READ_FAIL);
		}
		if (gnl_data_directing(gnl, r, i) == FULL_LINE_UP)
			break ;
		if (gnl_double_temp(gnl, &iter) != OKK)
		{
			free(gnl->buffer);
			return (DOUBLE_TMP_FAIL);
		}
	}
	free(gnl->buffer);
	return (gnl_line_setting_up(gnl, r));
}
