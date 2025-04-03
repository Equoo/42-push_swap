/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:11:12 by dderny            #+#    #+#             */
/*   Updated: 2025/03/28 01:17:12 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

#include <libft.h>
#include <ft_bool.h>

void	rotate(t_stack *stack, t_bool reverse)
{
	int	swap;

	if (reverse)
	{
		swap = stack->data[stack->size - 1];
		ft_memmove(stack->data + 1, stack->data, (stack->size - 1) * sizeof(int));
		stack->data[0] = swap;
	}
	else
	{
		swap = stack->data[0];	
		ft_memmove(stack->data, stack->data + 1, (stack->size - 1) * sizeof(int));
		stack->data[stack->size - 1] = swap;
	}
}
