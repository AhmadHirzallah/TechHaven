/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_fmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:40:25 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:26 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_initiate_parsing(t_data_s *data_s)
{
	ft_bzero(&data_s->flags_s, sizeof(data_s->flags_s));
	ft_bzero(&data_s->nbr_s, sizeof(data_s->nbr_s));
	data_s->flags_s.precision_val = -1;
}

static void	ft_parse_flags(t_data_s *data_s)
{
	while (ft_strchr(FLAGS, *data_s->str))
	{
		if ('0' == *data_s->str)
			data_s->flags_s.zero_pad_fl = true;
		if ('+' == *data_s->str)
			data_s->flags_s.plus_fl = true;
		if (' ' == *data_s->str)
			data_s->flags_s.space_fl = true;
		if ('-' == *data_s->str)
			data_s->flags_s.left_justif_fl = true;
		if ('#' == *data_s->str)
			data_s->flags_s.hasht_fl = true;
		++data_s->str;
	}
}

static int	ft_extract_vals(t_data_s *data_s, int *value)
{
	if (('*' == *data_s->str) && *(data_s->str++))
	{
		*value = (int)va_arg(data_s->ap, int);
		return (*value);
	}
	*value = 0;
	while (ft_strchr(DIGITS, (int)*data_s->str))
		*value = (*value * 10) + (*data_s->str++ - '0');
	return (*value);
}

static void	ft_set_specifiers_flags(t_data_s *data_s)
{
	data_s->flags_s.specifier = (char)*data_s->str;
	if (ft_strchr("diu", (int)data_s->flags_s.specifier))
		data_s->flags_s.base_e = BASE_10;
	else if (ft_strchr("xXp", (int)data_s->flags_s.specifier))
		data_s->flags_s.base_e = BASE_16;
	if ('X' == data_s->flags_s.specifier)
		data_s->flags_s.nbr_upper_case = true;
}

int	ft_parse_fmt(t_data_s *data_s)
{
	ft_initiate_parsing(data_s);
	ft_parse_flags(data_s);
	ft_extract_vals(data_s, &data_s->flags_s.width_val);
	if (('.' == *data_s->str) && *(++data_s->str))
	{
		data_s->flags_s.precision_fl = true;
		ft_extract_vals(data_s, &data_s->flags_s.precision_val);
	}
	if (ft_strchr(SPECIFIERS, (int)*data_s->str))
	{
		ft_set_specifiers_flags(data_s);
		return (OK_PRINTF);
	}
	else
		return (PARSE_ERR);
}
