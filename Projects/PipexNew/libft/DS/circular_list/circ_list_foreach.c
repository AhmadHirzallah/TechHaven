/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_list_foreach.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:58:25 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 16:02:24 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_list.h"
#include <stdlib.h>

void	circ_list_foreach(t_circular_lst *list, void (*f)(void *))
{
	size_t		i;
	t_list_node	*current;

	if (list->size == 0)
		return ;
	current = list->head;
	i = 0;
	while (i++ < list->size)
	{
		f(current->data_s.data.as_ptr);
		current = current->next;
	}
}
