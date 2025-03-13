/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_nullify_delimiters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:53:39 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/15 16:54:28 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	str_nullify_delimiters(char *input, const char *delimiters)
/*
 * ft_nullify_delimiters
 *
 * Scans through the entire input string and replaces every character found in
 * the 'delimiters' set with a '\0'. This modifies the original string in-place,
 * effectively splitting it into separate, null-terminated segments.
 *
 * Parameters:
 *   input      - The string to be processed. It is modified in place.
 *   delimiters - A string containing all delimiter characters.
 */
{
	if (input == NULL || delimiters == NULL)
		return ;
	while (*input != '\0')
	{
		if (ft_strchr(delimiters, *input))
			*input = '\0';
		input++;
	}
}
