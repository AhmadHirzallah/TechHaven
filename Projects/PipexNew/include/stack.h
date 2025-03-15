/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:57:31 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/11 19:57:32 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "dlist.h"

typedef t_dlist	t_stack;

// Creation/Destruction
t_stack			*stack_create(void (*del)(void *));
void			stack_destroy(t_stack *s);
short			stack_push(t_stack *s, void *data);
void			*stack_pop(t_stack *s);
void			*stack_peek(const t_stack *s);
size_t			stack_size(const t_stack *s);
short			is_stack_empty(const t_stack *s);
void			stack_clear(t_stack *s);
short			stack_iter_on_data(t_stack *s, int (*f)(void *));
t_stack			*stack_clone(t_stack *s, void *(*copy)(void *),
					void (*del)(void *));

#endif
