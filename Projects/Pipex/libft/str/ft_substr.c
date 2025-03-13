/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:31:42 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/07 14:31:44 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str_sub;
	size_t	true_size;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	true_size = ft_strlen(s + start);
	if (true_size < len)
		len = true_size;
	str_sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_sub)
		return (NULL);
	ft_strlcpy(str_sub, (s + start), (len + 1));
	return (str_sub);
}
