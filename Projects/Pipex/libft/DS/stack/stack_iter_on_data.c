/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_iter_on_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:40:42 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:40:43 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

short	stack_iter_on_data(t_stack *s, int (*f)(void *))
{
	t_dlist_node	*current;

	if (!s || !f)
		return (-1);
	current = s->head;
	while (current)
	{
		if (f(current->data) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}
