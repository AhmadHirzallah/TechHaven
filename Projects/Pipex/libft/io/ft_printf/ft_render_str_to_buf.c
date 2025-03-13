/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_str_to_buf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:40:44 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:45 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_calculate_pad_spaces_str(t_data_s *data_s, char *str_arg)
{
	int	str_len;

	str_len = ft_strlen(str_arg);
	if (data_s->flags_s.width_val > 0)
	{
		if (data_s->flags_s.precision_val >= 0)
		{
			if (data_s->flags_s.precision_val >= str_len)
				(data_s->flags_s.padding_spaces_nbr) = \
				(data_s->flags_s.width_val) - (str_len);
			else if (data_s->flags_s.precision_val < str_len)
				(data_s->flags_s.padding_spaces_nbr) = \
				(data_s->flags_s.width_val)
					- (data_s->flags_s.precision_val);
		}
		else
			(data_s->flags_s.padding_spaces_nbr) = (data_s->flags_s.width_val)
				- (str_len);
	}
}

void	ft_add_n_of_str_into_bfr(t_data_s *data_s, int len, char *str_arg)
{
	if (len <= 0)
		return ;
	while (len-- && *str_arg)
		ft_add_n_chrs_into_bfr(data_s, 1, (int)*str_arg++);
}

void	ft_render_str_to_buf(t_data_s *data_s, char *str_arg)
{
	if (NULL == str_arg)
		str_arg = "(null)";
	ft_calculate_pad_spaces_str(data_s, str_arg);
	if (data_s->flags_s.left_justif_fl)
	{
		if (data_s->flags_s.precision_val >= 0)
			ft_add_n_of_str_into_bfr(data_s, data_s->flags_s.precision_val,
				str_arg);
		else
			ft_add_n_of_str_into_bfr(data_s, ft_strlen(str_arg), str_arg);
		ft_add_n_chrs_into_bfr(data_s, (data_s->flags_s.padding_spaces_nbr),
			' ');
	}
	else
	{
		ft_add_n_chrs_into_bfr(data_s, (data_s->flags_s.padding_spaces_nbr),
			' ');
		if (data_s->flags_s.precision_val >= 0)
			ft_add_n_of_str_into_bfr(data_s, data_s->flags_s.precision_val,
				str_arg);
		else
			ft_add_n_of_str_into_bfr(data_s, ft_strlen(str_arg), str_arg);
	}
}
