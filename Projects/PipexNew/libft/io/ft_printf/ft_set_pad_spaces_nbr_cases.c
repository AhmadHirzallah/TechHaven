/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pad_spaces_nbr_cases.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:40:47 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:48 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static bool	ft_set_flags_effects(t_data_s *data_s)
{
	if (CONVERTED_FRM_NEG == (data_s->flags_s.nbr_track))
	{
		if (data_s->flags_s.space_fl)
			data_s->flags_s.padding_spaces_nbr--;
		return (true);
	}
	else if ((NOT_MODIFIED == data_s->flags_s.nbr_track)
		&& (data_s->flags_s.plus_fl))
	{
		data_s->flags_s.padding_spaces_nbr--;
		return (true);
	}
	else if ((NOT_MODIFIED == data_s->flags_s.nbr_track)
		&& (data_s->flags_s.space_fl))
	{
		data_s->flags_s.padding_spaces_nbr--;
		return (true);
	}
	return (false);
}

static bool	ft_set_hash_effects(t_data_s *data_s)
{
	if (ft_strchr("xXp", (int)(data_s->flags_s.specifier))
		&& (data_s->flags_s.hasht_fl) && (data_s->nbr_s.nbr_bfr[0] != '0'))
	{
		data_s->flags_s.padding_spaces_nbr -= 2;
		return (true);
	}
	if ('u' == (data_s->flags_s.specifier))
		return (true);
	return (false);
}

void	ft_set_pad_spaces_nbr_cases(t_data_s *data_s)
{
	(data_s->flags_s.padding_spaces_nbr) = (data_s->flags_s.width_val)
		- ((data_s->nbr_s.nbr_bfr_len) + data_s->flags_s.padding_zeros_nbr);
	if (ft_set_hash_effects(data_s))
		return ;
	if (ft_set_flags_effects(data_s))
		return ;
}
