/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_del_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:37:25 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:37:27 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_del_end(t_dlist *list)
{
	t_dlist_node	*temp;

	if (!list->tail)
		return ;
	temp = list->tail;
	list->tail = list->tail->prev;
	if (list->tail)
		list->tail->next = NULL;
	else
		list->head = NULL;
	dlist_del_node(list, temp);
}
