/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_insert_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:38:23 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:38:23 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"
#include "libft.h"
#include <stdlib.h>

short	dlist_insert_end(t_dlist *list, t_value_data *data)
{
	t_dlist_node	*new_node;

	new_node = malloc(sizeof(t_dlist_node));
	if (!new_node)
		return (-1);
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = list->tail;
	if (list->tail)
		list->tail->next = new_node;
	else
		list->head = new_node;
	list->tail = new_node;
	list->size++;
	return (0);
}
