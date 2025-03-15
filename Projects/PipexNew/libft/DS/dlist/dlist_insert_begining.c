/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_insert_begining.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:38:18 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:38:19 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

short	dlist_insert_begining(t_dlist *list, void *data)
{
	t_dlist_node	*new_node;

	if (!list)
		return (-1);
	new_node = malloc(sizeof(t_dlist_node));
	if (!new_node)
		return (-1);
	new_node->data = data;
	new_node->prev = NULL;
	new_node->next = list->head;
	if (list->head)
		list->head->prev = new_node;
	else
		list->tail = new_node;
	list->head = new_node;
	list->size++;
	return (0);
}
