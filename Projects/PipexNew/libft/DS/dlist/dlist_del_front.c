/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_del_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:37:31 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:37:32 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_del_front(t_dlist *list)
{
	t_dlist_node	*temp;

	if (!list->head)
		return ;
	temp = list->head;
	list->head = list->head->next;
	if (list->head)
		list->head->prev = NULL;
	else
		list->tail = NULL;
	dlist_del_node(list, temp);
}
