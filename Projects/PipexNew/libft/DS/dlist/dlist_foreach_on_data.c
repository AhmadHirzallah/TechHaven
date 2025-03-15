/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_foreach_on_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:37:44 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:37:45 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_foreach_on_data(t_dlist *list, void (*f)(void *))
{
	t_dlist_node	*current;

	current = list->head;
	while (current)
	{
		f(current->data);
		current = current->next;
	}
}
