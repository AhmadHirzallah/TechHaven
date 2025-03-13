/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_lst_push_front_into_other.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:58:58 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 15:58:59 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_list.h"
#include <stdlib.h>

static t_list_node	*pop_src_node(t_circular_lst *src)
{
	t_list_node	*node;

	if (!src || src->size == 0)
		return (NULL);
	node = src->head;
	if (src->size == 1)
	{
		src->head = NULL;
		src->tail = NULL;
	}
	else
	{
		src->head = node->next;
		src->head->prev = src->tail;
		src->tail->next = src->head;
	}
	src->size--;
	return (node);
}

static void	push_node_to_dest(t_circular_lst *dest, t_list_node *node)
{
	if (!dest)
		return ;
	if (dest->size == 0)
	{
		node->next = node;
		node->prev = node;
		dest->head = node;
		dest->tail = node;
	}
	else
	{
		node->next = dest->head;
		node->prev = dest->tail;
		dest->tail->next = node;
		dest->head->prev = node;
		dest->head = node;
	}
	dest->size++;
}

void	circ_lst_push_front_into_other(t_circular_lst *dest,
		t_circular_lst *src)
{
	t_list_node	*node;

	node = pop_src_node(src);
	if (!node)
		return ;
	push_node_to_dest(dest, node);
}
