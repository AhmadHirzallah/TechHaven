/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_into_bfr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:40:20 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:23 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_itoa_base_bfr(t_data_s *data_s, t_nbr_union values_uni)
{
	t_nbr_union	tmp_nbr;

	if ((NEG_NBR == data_s->flags_s.nbr_track)
		&& (CONVERTED_FRM_NEG != data_s->flags_s.nbr_track))
	{
		values_uni.int64 = -(values_uni.int64);
		data_s->flags_s.nbr_track = CONVERTED_FRM_NEG;
		ft_itoa_base_bfr(data_s, values_uni);
	}
	else if (values_uni.uint64 < data_s->flags_s.base_e)
	{
		if (data_s->flags_s.nbr_upper_case)
			data_s->nbr_s.nbr_bfr[data_s->nbr_s.nbr_bfr_len++] = \
			HEXADE_UPPER[values_uni.uint64];
		else
			data_s->nbr_s.nbr_bfr[data_s->nbr_s.nbr_bfr_len++] = \
			HEXADE_LOWER[values_uni.uint64];
	}
	else
	{
		tmp_nbr.uint64 = (values_uni.uint64 / data_s->flags_s.base_e);
		ft_itoa_base_bfr(data_s, tmp_nbr);
		tmp_nbr.uint64 = (values_uni.uint64 % data_s->flags_s.base_e);
		ft_itoa_base_bfr(data_s, tmp_nbr);
	}
}
