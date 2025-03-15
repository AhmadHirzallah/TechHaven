/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:40:28 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:29 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	ft_init_data(t_data_s *data_s, const char *fmt)
{
	data_s->dynmc_nbr.int64 = 0;
	data_s->str = fmt;
	data_s->printf_buffer = ft_calloc(BUFFER_SIZE_PRINTF, sizeof(char));
	if (NULL == data_s->printf_buffer)
		return (MALLOC_ERR);
	data_s->printf_buf_len = 0;
	data_s->rtrn_printf_value = 0;
	return (OK_PRINTF);
}

int	ft_printf(const char *fmt, ...)
{
	t_data_s	data_s;

	va_start(data_s.ap, fmt);
	if (MALLOC_ERR == ft_init_data(&data_s, fmt))
		return (PRINTF_ERR);
	while (*data_s.str)
	{
		if (*data_s.str == '%' && *(data_s.str++))
		{
			if (ft_parse_fmt(&data_s) == OK_PRINTF)
				ft_render_into_buffer(&data_s);
			else
			{
				ft_flush_buffer(&data_s);
				return (data_s.rtrn_printf_value);
			}
		}
		else
			ft_add_n_chrs_into_bfr(&data_s, 1, *data_s.str);
		++data_s.str;
	}
	ft_flush_buffer(&data_s);
	va_end(data_s.ap);
	free(data_s.printf_buffer);
	return (data_s.rtrn_printf_value);
}
	// if (data_s.rtrn_printf_value > BUFFER_SIZE_PRINTF)
		// return (data_s.rtrn_printf_value + 1);
