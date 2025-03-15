/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:20:40 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/02 12:20:42 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_2d_arr(char ***arr)
{
	int		i;
	char	**tmp;

	if (arr == NULL || *arr == NULL)
		return ;
	tmp = *arr;
	i = 0;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	*arr = NULL;
}
