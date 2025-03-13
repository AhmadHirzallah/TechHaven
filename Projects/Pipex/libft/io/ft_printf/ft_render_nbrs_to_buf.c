/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_nbrs_to_buf.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:40:41 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:41 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_add_0x_cases(t_data_s *data_s)
{
	if ((ft_strchr("xX", data_s->flags_s.specifier))
		&& (data_s->flags_s.hasht_fl) && (data_s->nbr_s.nbr_bfr[0] != '0'))
	{
		if (data_s->flags_s.nbr_upper_case)
			ft_add_n_of_str_into_bfr(data_s, 2, "0X");
		else
			ft_add_n_of_str_into_bfr(data_s, 2, "0x");
		data_s->flags_s.padding_spaces_nbr -= 2;
	}
	if ('p' == data_s->flags_s.specifier)
		ft_add_n_of_str_into_bfr(data_s, 2, "0x");
}

static void	ft_cofig_preceding_signs_and_flags(t_data_s *data_s)
{
	if (CONVERTED_FRM_NEG == data_s->flags_s.nbr_track)
	{
		data_s->flags_s.padding_spaces_nbr--;
		return ;
	}
	else if ((NOT_MODIFIED == data_s->flags_s.nbr_track)
		&& ((data_s->flags_s.plus_fl) || (data_s->flags_s.space_fl)))
	{
		data_s->flags_s.padding_zeros_nbr--;
		return ;
	}
}

static void	ft_add_preceding_signs_and_flags(t_data_s *data_s)
{
	ft_cofig_preceding_signs_and_flags(data_s);
	if (data_s->flags_s.is_signed_nbr)
	{
		if (CONVERTED_FRM_NEG == data_s->flags_s.nbr_track)
			ft_add_n_chrs_into_bfr(data_s, 1, '-');
		else if ((NOT_MODIFIED == data_s->flags_s.nbr_track)
			&& (data_s->flags_s.plus_fl))
			ft_add_n_chrs_into_bfr(data_s, 1, '+');
		else if ((NOT_MODIFIED == data_s->flags_s.nbr_track)
			&& (data_s->flags_s.space_fl))
			ft_add_n_chrs_into_bfr(data_s, 1, ' ');
	}
}

static void	ft_handle_display(t_data_s *data_s)
{
	if (data_s->flags_s.left_justif_fl)
	{
		if ('p' == data_s->flags_s.specifier)
			data_s->flags_s.padding_spaces_nbr -= 2;
		if (BASE_16 == data_s->flags_s.base_e)
			ft_add_0x_cases(data_s);
		ft_add_preceding_signs_and_flags(data_s);
		ft_add_n_chrs_into_bfr(data_s, data_s->flags_s.padding_zeros_nbr, '0');
		ft_add_n_of_str_into_bfr(data_s, data_s->nbr_s.nbr_bfr_len,
			data_s->nbr_s.nbr_bfr);
		ft_add_n_chrs_into_bfr(data_s, data_s->flags_s.padding_spaces_nbr, ' ');
	}
	else
	{
		if ('p' == data_s->flags_s.specifier)
			data_s->flags_s.padding_spaces_nbr -= 2;
		ft_add_n_chrs_into_bfr(data_s, data_s->flags_s.padding_spaces_nbr, ' ');
		if (BASE_16 == data_s->flags_s.base_e)
			ft_add_0x_cases(data_s);
		ft_add_preceding_signs_and_flags(data_s);
		ft_add_n_chrs_into_bfr(data_s, data_s->flags_s.padding_zeros_nbr, '0');
		ft_add_n_of_str_into_bfr(data_s, data_s->nbr_s.nbr_bfr_len,
			data_s->nbr_s.nbr_bfr);
	}
}

void	ft_render_nbrs_to_buf(t_data_s *data_s)
{
	if ((data_s->flags_s.precision_fl) && data_s->dynmc_nbr.int64 == 0
		&& (data_s->flags_s.precision_val == -1
			|| data_s->flags_s.precision_val == 0))
		return ;
	if ((0 == data_s->dynmc_nbr.uint64) && ('p' == data_s->flags_s.specifier))
	{
		ft_add_n_of_str_into_bfr(data_s, 5, "(nil)");
		return ;
	}
	ft_itoa_base_bfr(data_s, data_s->dynmc_nbr);
	ft_set_pad_zeros_nbr_cases(data_s);
	ft_set_pad_spaces_nbr_cases(data_s);
	ft_handle_display(data_s);
}
