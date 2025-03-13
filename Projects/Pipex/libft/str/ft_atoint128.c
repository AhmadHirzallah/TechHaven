/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoint128.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:53:28 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 20:02:51 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Type           | Bits  | Signed Range
----------------------------------------------
int            | 32    | -2³¹ to 2³¹-1 (-2147483648 to 2147483647)
long           | 64    | -2⁶³ to 2⁶³-1
long long      | 64    | Same as long
__int128_t     | 128   | -2¹²⁷ to 2¹²⁷-1 (≈ ±1.7e³⁸)
*/
__int128	ft_atoint128(const char *nptr)
{
	int			i;
	short		sign;
	__int128	result;

	i = 0;
	sign = 1;
	result = 0;
	while (is_str_space(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}
