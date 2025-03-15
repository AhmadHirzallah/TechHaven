/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:31:17 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/15 13:35:39 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "ft_printf.h"

void print_2d_arr(char **arr)
{
    size_t i = 0;

    while (arr[i] != NULL)
    {
        ft_printf("{%s}\n", arr[i]);
        i++;
    }
}
