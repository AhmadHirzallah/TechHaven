/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_peek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:40:46 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:40:46 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	*stack_peek(const t_stack *s)
{
	const t_dlist_node	*top;

	top = dlist_front(s);
	if (top)
		return (top->data);
	return (NULL);
}

/*
void	*stack_peek(const t_stack *s)
{
	const t_dlist_node	*top = dlist_front(s);

	return (top ? top->data : NULL);
}
*/
