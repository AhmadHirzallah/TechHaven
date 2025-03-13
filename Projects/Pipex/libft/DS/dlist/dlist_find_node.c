/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_find_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:37:41 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:37:41 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

t_dlist_node	*dlist_find_node(const t_dlist *list, const void *data,
		int (*cmp)(const void *, const void *))
{
	t_dlist_node	*current;

	current = list->head;
	while (current)
	{
		if (cmp(current->data, data) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
