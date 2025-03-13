/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_list_insert_beginning.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:58:40 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 22:06:20 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_list.h"
#include <stdlib.h>

int	circ_list_insert_beginning(t_circular_lst *list, void *data)
{
	t_list_node	*new_node;

	new_node = malloc(sizeof(t_list_node));
	if (!new_node)
		return (-1);
	new_node->data_s.data.as_ptr = data;
	if (list->size == 0)
	{
		new_node->next = new_node;
		new_node->prev = new_node;
		list->tail = new_node;
	}
	else
	{
		new_node->next = list->head;
		new_node->prev = list->tail;
		list->head->prev = new_node;
		list->tail->next = new_node;
	}
	list->head = new_node;
	list->size++;
	return (0);
}
