/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tok_sttc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:53:17 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/22 21:24:36 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/*
This Function will create tokens but in many rounds;
every round it will return one tocken!!

if (!*next_ptr_pos)
{
	*next_ptr_pos = '\0';
	next_ptr_pos++;
}
*/
char	*str_tok_sttc(char *str, const char *delimiters)
{
	static char	*next_ptr_pos = NULL;
	char		*tocken_start;

	if (str)
		next_ptr_pos = str;
	if (!next_ptr_pos)
		return (NULL);
	while (*next_ptr_pos && ft_strchr(delimiters, *next_ptr_pos))
		next_ptr_pos++;
	if (!*next_ptr_pos)
	{
		next_ptr_pos = NULL;
		return (NULL);
	}
	tocken_start = next_ptr_pos;
	while (*next_ptr_pos && !ft_strchr(delimiters, *next_ptr_pos))
		next_ptr_pos++;
	if (*next_ptr_pos)
	{
		*next_ptr_pos = '\0';
		next_ptr_pos++;
	}
	return (tocken_start);
}
