/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_insert_after.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:37:58 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:37:59 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

short	dlist_insert_after(t_dlist *list, t_dlist_node *node, void *data)
{
	t_dlist_node	*new_node;

	if (!node)
		return (-1);
	new_node = malloc(sizeof(t_dlist_node));
	if (!new_node)
		return (-2);
	new_node->data = data;
	new_node->prev = node;
	new_node->next = node->next;
	if (node->next)
		node->next->prev = new_node;
	else
		list->tail = new_node;
	node->next = new_node;
	list->size++;
	return (0);
}
