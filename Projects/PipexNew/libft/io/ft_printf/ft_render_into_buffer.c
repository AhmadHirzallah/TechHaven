/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_into_buffer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:40:35 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:37 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_render_any_nbr(t_data_s *data_s)
{
	if (ft_strchr("di", (int)data_s->flags_s.specifier))
	{
		data_s->dynmc_nbr.int64 = va_arg(data_s->ap, int);
		data_s->flags_s.is_signed_nbr = true;
		if (data_s->dynmc_nbr.int64 < 0)
			data_s->flags_s.nbr_track = NEG_NBR;
		ft_render_nbrs_to_buf(data_s);
	}
	else if (ft_strchr("uxX", (int)data_s->flags_s.specifier))
	{
		data_s->dynmc_nbr.uint64 = (unsigned long)va_arg(data_s->ap,
				unsigned int);
		ft_render_nbrs_to_buf(data_s);
	}
	else if ('p' == data_s->flags_s.specifier)
	{
		data_s->dynmc_nbr.uint64 = (unsigned long)va_arg(data_s->ap,
				unsigned long);
		ft_render_nbrs_to_buf(data_s);
	}
}

void	ft_render_into_buffer(t_data_s *data_s)
{
	if ('%' == data_s->flags_s.specifier)
		ft_render_char_to_buf(data_s, '%');
	else if ('c' == data_s->flags_s.specifier)
		ft_render_char_to_buf(data_s, va_arg(data_s->ap, int));
	else if ('s' == data_s->flags_s.specifier)
		ft_render_str_to_buf(data_s, va_arg(data_s->ap, char *));
	else if (ft_strchr("diuxXp", (int)data_s->flags_s.specifier))
		ft_render_any_nbr(data_s);
}
