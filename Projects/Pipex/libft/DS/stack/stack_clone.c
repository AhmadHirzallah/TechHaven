/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_clone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:40:21 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:40:22 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack	*stack_clone(t_stack *s, void *(*copy)(void *), void (*del)(void *))
{
	t_stack			*clone;
	t_dlist_node	*current;
	void			*data_copy;

	if (!s || !copy)
		return (NULL);
	clone = stack_create(del);
	if (!clone)
		return (NULL);
	current = s->tail;
	while (current)
	{
		data_copy = copy(current->data);
		if (!data_copy || stack_push(clone, data_copy) != 0)
		{
			stack_destroy(clone);
			return (NULL);
		}
		current = current->prev;
	}
	return (clone);
}
