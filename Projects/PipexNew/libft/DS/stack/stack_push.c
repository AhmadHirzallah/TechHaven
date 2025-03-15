/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:40:51 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:40:53 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

short	stack_push(t_stack *s, void *data)
{
	return (dlist_insert_begining(s, data));
}

/*
int	stack_push(t_stack *s, void *data)
{
	return (dlist_push_front(s, data) == 0 ? 0 : -1);
}
*/
