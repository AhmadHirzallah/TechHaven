/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_list_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:58:29 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 22:08:17 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_list.h"
#include <stdlib.h>

void	circ_list_clear(t_circular_lst *list, void (*del)(void *))
{
	t_list_node	*current;
	t_list_node	*next;
	size_t		i;

	if (list->size == 0)
		return ;
	current = list->head;
	i = 0;
	while (i++ < list->size)
	{
		next = current->next;
		if (del)
			del(current->data_s.data.as_ptr);
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}
