/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:45:21 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/02 19:45:26 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr_dup;
	size_t	the_size;

	the_size = ft_strlen(s) + 1;
	ptr_dup = malloc(the_size);
	if (ptr_dup == NULL)
		return (NULL);
	ft_memcpy(ptr_dup, s, the_size);
	return (ptr_dup);
}
