/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:31:51 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/07 14:34:14 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start_index;
	int	end_index;

	start_index = 0;
	end_index = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (NULL);
	while (s1[start_index] && (ft_strchr(set, s1[start_index])))
		start_index++;
	while (s1[end_index] && ft_strchr(set, s1[end_index]))
		end_index--;
	return (ft_substr(s1, start_index, (end_index - start_index + 1)));
}
