/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:11:12 by dderny            #+#    #+#             */
/*   Updated: 2025/03/28 01:18:42 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

#include <libft.h>

void	push(t_stack *from, t_stack *to)
{
	if (!from->size)
		return ;
	if (to->size > 1)
		ft_memmove(to->data + 1, to->data, to->size * sizeof(int));
	to->data[0] = from->data[0];
	to->size++;
	ft_memmove(from->data, from->data + 1, (from->size - 1) * sizeof(int));
	from->size--;
	from->data[from->size] = 0;
}
