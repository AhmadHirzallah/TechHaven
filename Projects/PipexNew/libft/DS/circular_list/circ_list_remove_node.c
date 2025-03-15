/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_list_remove_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:58:48 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 22:07:17 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_list.h"
#include <stdlib.h>

void	circ_list_remove_node(t_circular_lst *list, t_list_node *node,
		void (*del)(void *))
{
	if (list->size == 0 || !node)
		return ;
	if ((list->size == 1) && (list->head == node))
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		if (node == list->head)
			list->head = node->next;
		if (node == list->tail)
			list->tail = node->prev;
	}
	if (del)
		del(node->data_s.data.as_ptr);
	free(node);
	list->size--;
}
