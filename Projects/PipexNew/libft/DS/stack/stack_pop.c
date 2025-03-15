/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:40:49 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:40:49 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	*stack_pop(t_stack *s)
{
	void	*data;

	if (!s || is_stack_empty(s))
		return (NULL);
	data = stack_peek(s);
	if (data)
		dlist_del_front(s);
	return (data);
}
