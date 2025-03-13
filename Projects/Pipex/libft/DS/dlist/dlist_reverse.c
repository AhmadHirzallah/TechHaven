/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_reverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:39:45 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:39:46 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_reverse(t_dlist *list)
{
	t_dlist_node	*current;
	t_dlist_node	*temp;

	current = list->head;
	while (current)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	temp = list->head;
	list->head = list->tail;
	list->tail = temp;
}
