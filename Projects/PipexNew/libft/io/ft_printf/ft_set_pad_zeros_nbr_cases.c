/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pad_zeros_nbr_cases.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:40:50 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:51 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static bool	ft_set_zeros_wth_prec(t_data_s *data_s)
{
	if ((data_s->flags_s.precision_val >= 0)
		&& (data_s->flags_s.precision_val > data_s->nbr_s.nbr_bfr_len))
	{
		(data_s->flags_s.padding_zeros_nbr) = (data_s->flags_s.precision_val)
			- (data_s->nbr_s.nbr_bfr_len);
		if (data_s->flags_s.plus_fl)
			data_s->flags_s.padding_zeros_nbr++;
		return (true);
	}
	return (false);
}

static void	ft_set_width_wth_nbr_len(t_data_s *data_s)
{
	if ((data_s->flags_s.width_val) > (data_s->nbr_s.nbr_bfr_len)
		&& data_s->flags_s.nbr_track != CONVERTED_FRM_NEG)
		(data_s->flags_s.padding_zeros_nbr) = (data_s->flags_s.width_val)
			- (data_s->nbr_s.nbr_bfr_len);
	else if ((data_s->flags_s.width_val) > (data_s->nbr_s.nbr_bfr_len)
		&& data_s->flags_s.nbr_track == CONVERTED_FRM_NEG)
	{
		(data_s->flags_s.padding_zeros_nbr) = (data_s->flags_s.width_val)
			- (data_s->nbr_s.nbr_bfr_len) - 1;
		data_s->flags_s.width_val--;
	}
}

static void	ft_set_flags_effects(t_data_s *data_s)
{
	if ((ft_strchr("xX", (int)data_s->flags_s.specifier))
		&& (data_s->flags_s.hasht_fl) && (data_s->nbr_s.nbr_bfr[0] != '0'))
		(data_s->flags_s.padding_zeros_nbr) -= 2;
	if ((data_s->flags_s.plus_fl) || (data_s->flags_s.space_fl))
		(data_s->flags_s.padding_zeros_nbr)--;
}

void	ft_set_pad_zeros_nbr_cases(t_data_s *data_s)
{
	if (ft_set_zeros_wth_prec(data_s))
		return ;
	else if (data_s->flags_s.zero_pad_fl)
	{
		ft_set_width_wth_nbr_len(data_s);
		ft_set_flags_effects(data_s);
		if ((data_s->flags_s.padding_zeros_nbr) < 0)
			data_s->flags_s.padding_spaces_nbr = 0;
	}
}
