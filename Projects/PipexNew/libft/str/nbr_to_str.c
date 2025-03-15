/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:56:36 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 19:56:48 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_negative(__int128_t nbr, short *is_negative,
		unsigned __int128 *unbr)
{
	if (nbr < 0)
	{
		*unbr = (unsigned __int128)(-nbr);
		*is_negative = 1;
	}
	else
	{
		*is_negative = 0;
		*unbr = (unsigned __int128)nbr;
	}
}

static size_t	extract_digits(unsigned __int128 num, char *buffer)
{
	size_t	total;

	total = 0;
	while (num > 0)
	{
		buffer[total] = '0' + (num % 10);
		total++;
		num /= 10;
	}
	return (total);
}

static void	reverse_digits(char *bfr, size_t len)
{
	size_t	i;
	size_t	j;
	char	temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = bfr[i];
		bfr[i] = bfr[j];
		bfr[j] = temp;
		i++;
		j--;
	}
}

static void	fill_result_nbr(char *result, int is_negative, char *bfr,
		size_t digit_count)
{
	char	*cur;
	size_t	i;

	cur = result;
	if (is_negative)
	{
		*cur = '-';
		cur++;
	}
	i = 0;
	while (i < digit_count)
	{
		cur[i] = bfr[i];
		i++;
	}
	cur[i] = '\0';
}

char	*nbr_to_str(__int128_t nbr)
{
	char				bfr[40];
	size_t				len;
	short				is_negative;
	unsigned __int128	unbr;
	char				*result;

	if (nbr == 0)
		return (ft_strdup("0"));
	handle_negative(nbr, &is_negative, &unbr);
	len = extract_digits(unbr, bfr);
	reverse_digits(bfr, len);
	if (is_negative)
		result = malloc(len + 2);
	else
		result = malloc(len + 1);
	if (!result)
		return (NULL);
	fill_result_nbr(result, is_negative, bfr, len);
	return (result);
}
