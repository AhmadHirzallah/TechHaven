/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_remove_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:39:43 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:39:44 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_remove_node(t_dlist *list, t_dlist_node *node)
{
	if (!node || list->size == 0)
		return ;
	if (node == list->head)
		list->head = node->next;
	if (node == list->tail)
		list->tail = node->prev;
	dlist_del_node(list, node);
}
