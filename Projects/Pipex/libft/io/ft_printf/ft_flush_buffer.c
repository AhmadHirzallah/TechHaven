/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flush_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:40:10 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:14 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_flush_buffer(t_data_s *data_s)
{
	data_s->rtrn_printf_value += write(1, data_s->printf_buffer,
			data_s->printf_buf_len);
	ft_bzero(data_s->printf_buffer, BUFFER_SIZE_PRINTF);
	data_s->printf_buf_len = 0;
}
