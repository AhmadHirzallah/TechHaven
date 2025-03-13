/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:39:35 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:39:36 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_merge(t_dlist *list1, t_dlist *list2)
{
	if (!list1 || !list2 || list1 == list2)
		return ;
	if (is_dlist_empty(list2))
		return ;
	if (is_dlist_empty(list1))
	{
		list1->head = list2->head;
		list1->tail = list2->tail;
	}
	else
	{
		list1->tail->next = list2->head;
		list2->head->prev = list1->tail;
		list1->tail = list2->tail;
	}
	list1->size += list2->size;
	list2->head = NULL;
	list2->tail = NULL;
	list2->size = 0;
}
