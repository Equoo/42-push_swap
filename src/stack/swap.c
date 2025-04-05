/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:11:12 by dderny            #+#    #+#             */
/*   Updated: 2025/04/06 01:13:44 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	swap(t_stack *stack)
{
	int	swap;

	if (stack->size <= 1)
		return ;
	swap = stack->data[0];
	stack->data[0] = stack->data[1];
	stack->data[1] = swap;
}
