/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:08:17 by dderny            #+#    #+#             */
/*   Updated: 2025/04/06 01:10:58 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"
#include <limits.h>

u_int	get_min(t_slice *slice)
{
	u_int	i;
	u_int	min;

	min = INT_MAX;
	i = 0;
	while (i < slice->size)
	{
		if (min > slice->data[i])
			min = slice->data[i];
		i++;
	}
	return (min);
}

void	move_from_to(t_sdata *data, u_int from, u_int to)
{
	if (from == to)
		return ;
	if (from == BOT_A)
		operate(RRA, data);
	if ((from == TOP_A || from == BOT_A) && (to == TOP_B || to == BOT_B))
		operate(PB, data);
	if ((from == TOP_A || from == BOT_A || from == TOP_B) && to == BOT_B)
		operate(RB, data);
	if (from == BOT_B)
		operate(RRB, data);
	if ((from == TOP_B || from == BOT_B) && (to == TOP_A || to == BOT_A))
		operate(PA, data);
	if ((from == TOP_B || from == BOT_B || from == TOP_A) && to == BOT_A)
		operate(RA, data);
}

void	reverse_slice(t_slice *slice)
{
	size_t	i;
	u_int	temp;

	i = 0;
	while (i < slice->size / 2)
	{
		temp = slice->data[i];
		slice->data[i] = slice->data[slice->size - 1 - i];
		slice->data[slice->size - 1 - i] = temp;
		i++;
	}
}

void	sort_three_top_a(t_sdata *data)
{
	u_int	*stack;

	stack = data->a.data;
	if (stack[2] < stack[1] && stack[1] < stack[0])
		operate(SA, data);
	if (stack[2] < stack[0] && stack[0] < stack[1])
	{
		operate(RA, data);
		operate(SA, data);
		operate(RRA, data);
	}
	if (stack[1] < stack[2] && stack[2] < stack[0])
		operate(SA, data);
	if (stack[0] < stack[2] && stack[2] < stack[1])
	{
		operate(RA, data);
		operate(SA, data);
		operate(RRA, data);
	}
	if (stack[1] < stack[0] && stack[0] < stack[2])
		operate(SA, data);
}
