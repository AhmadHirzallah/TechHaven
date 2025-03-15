/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:40:56 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:40:57 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

size_t	stack_size(const t_stack *s)
{
	return (dlist_size(s));
}

/*
size_t	stack_size(const t_stack *s)
{
	return (s ? dlist_size(s) : 0);
}
*/
