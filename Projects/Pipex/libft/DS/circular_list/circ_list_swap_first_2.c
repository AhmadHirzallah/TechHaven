/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_list_swap_first_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:58:54 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 22:07:47 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_list.h"

void	circ_list_swap_first_2(t_circular_lst *list)
{
	t_list_node	*first;
	t_list_node	*second;
	t_value		tmp;

	if (list->size < 2)
		return ;
	first = list->head;
	second = first->next;
	tmp = first->data_s;
	first->data_s = second->data_s;
	second->data_s = tmp;
}
