/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_lst_rev_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:01 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/19 22:06:34 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_list.h"

void	circ_lst_rev_rotate(t_circular_lst *list)
{
	if (!list || list->size < 2)
		return ;
	list->head = list->head->prev;
	list->tail = list->tail->prev;
}
