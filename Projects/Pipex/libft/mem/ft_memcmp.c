/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:20:22 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/02 12:20:23 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr_str1;
	unsigned char	*ptr_str2;
	size_t			i;

	ptr_str1 = (unsigned char *)s1;
	ptr_str2 = (unsigned char *)s2;
	i = 0;
	while ((i < n) && (ptr_str1[i] == ptr_str2[i]))
		i++;
	if (i < n)
		return ((unsigned char)ptr_str1[i] - (unsigned char)ptr_str2[i]);
	else
		return (0);
}
