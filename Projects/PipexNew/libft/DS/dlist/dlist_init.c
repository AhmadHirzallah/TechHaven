/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:37:51 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:37:51 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_init(t_dlist *list, void (*del)(void *))
{
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->del = del;
}
