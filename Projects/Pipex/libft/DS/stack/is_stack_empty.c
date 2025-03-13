/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_stack_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:40:12 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:40:13 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

short	is_stack_empty(const t_stack *s)
{
	return (is_dlist_empty(s));
}
/*
int	is_stack_empty(const t_stack *s)
{
	return (s ? is_dlist_empty(s) : 1);
}
*/
