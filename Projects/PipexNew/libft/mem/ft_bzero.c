/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:00:09 by ahirzall          #+#    #+#             */
/*   Updated: 2024/08/26 17:10:13 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*void	ft_bzero(void *s, size_t n)
{
	char	*ptr_str;
	size_t	i;

	ptr_str = (char *) s;
	i = 0;
	while (i < n)
		ptr_str[i++] = '\0';
	return (s);
}*/
