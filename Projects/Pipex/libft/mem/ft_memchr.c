/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:20:10 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/02 12:20:11 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_str;
	size_t			i;

	i = 0;
	ptr_str = (unsigned char *)s;
	while (i < n)
	{
		if (ptr_str[i] == (unsigned char)c)
			return ((void *)(ptr_str + i));
		i++;
	}
	return (NULL);
}
