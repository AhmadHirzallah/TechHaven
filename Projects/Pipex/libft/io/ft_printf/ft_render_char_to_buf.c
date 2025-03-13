/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_char_to_buf.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:40:31 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:32 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_add_n_chrs_into_bfr(t_data_s *data_s, int len, int c)
{
	if (0 >= len)
		return ;
	while (len--)
	{
		if (BUFFER_SIZE_PRINTF > data_s->printf_buf_len)
			data_s->printf_buffer[data_s->printf_buf_len++] = (char)c;
		else
		{
			ft_flush_buffer(data_s);
			data_s->printf_buffer[data_s->printf_buf_len++] = (char)c;
		}
	}
}

void	ft_render_char_to_buf(t_data_s *data_s, int c)
{
	if (data_s->flags_s.width_val > 0)
	{
		if (data_s->flags_s.left_justif_fl == true)
		{
			ft_add_n_chrs_into_bfr(data_s, 1, c);
			ft_add_n_chrs_into_bfr(data_s, (data_s->flags_s.width_val - 1),
				' ');
		}
		else
		{
			ft_add_n_chrs_into_bfr(data_s, (data_s->flags_s.width_val - 1),
				' ');
			ft_add_n_chrs_into_bfr(data_s, 1, c);
		}
	}
	else
		ft_add_n_chrs_into_bfr(data_s, 1, c);
}
