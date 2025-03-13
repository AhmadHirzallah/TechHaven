/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:55:39 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 15:56:10 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_value	ft_value_new_ptr(void *ptr)
{
	t_value	value;

	value.type = VAL_PTR;
	value.data.as_ptr = ptr;
	return (value);
}

t_value	ft_value_new_long(long num)
{
	t_value	value;

	value.type = VAL_LONG;
	value.data.as_long = num;
	return (value);
}

t_value	ft_value_new_int(int num)
{
	t_value	value;

	value.type = VAL_INT;
	value.data.as_int = num;
	return (value);
}

short	ft_value_get_long(const t_value *val, long *out)
{
	if (val->type != VAL_LONG)
		return (0);
	*out = val->data.as_long;
	return (1);
}

short	ft_value_get_int(const t_value *val, int *out)
{
	if (val->type != VAL_INT)
		return (0);
	*out = val->data.as_int;
	return (1);
}
