/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_lst_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:04 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 22:06:42 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_list.h"

void	circ_lst_rotate(t_circular_lst *list)
{
	if (!list || list->size < 2)
		return ;
	list->head = list->head->next;
	list->tail = list->tail->next;
}
