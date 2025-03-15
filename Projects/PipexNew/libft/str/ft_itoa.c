/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:32:00 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/09 18:23:50 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short	ft_get_len_of_int_nbr(int n)
{
	short	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	len;
	char			*str_of_nbr;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_get_len_of_int_nbr(n);
	str_of_nbr = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_of_nbr)
		return (NULL);
	str_of_nbr[len] = '\0';
	if (n < 0)
	{
		str_of_nbr[0] = '-';
		n = -n;
	}
	while (n)
	{
		str_of_nbr[--len] = ('0' + (n % 10));
		n /= 10;
	}
	return (str_of_nbr);
}
