/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ten.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:22:59 by dderny            #+#    #+#             */
/*   Updated: 2025/04/06 00:40:28 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <sys/types.h>

static void	min_to_b(t_sdata *data);
static void	sort_three(t_sdata *data);

void	sort_nine(t_sdata *data)
{
	if (data->a.size < 2)
		return ;
	if (data->a.size == 2)
	{
		if (data->a.data[0] > data->a.data[1])
			operate(SA, data);
		return ;
	}
	while (data->a.size > 3)
		min_to_b(data);
	sort_three(data);
	while (data->b.size > 0)
		operate(PA, data);
}

static void	min_to_b(t_sdata *data)
{
	u_int	i;
	u_int	min;
	u_int	op;

	min = 0;
	i = -1;
	while (++i < data->a.size)
		if (data->a.data[i] < data->a.data[min])
			min = i;
	op = RA;
	if (min > data->a.size / 2)
	{
		min = data->a.size - min;
		op = RRA;
	}
	i = 0;
	while (i++ < min)
		operate(op, data);
	operate(PB, data);
}

static void	sort_three(t_sdata *data)
{
	u_int	*stack;

	stack = data->a.data;
	if (stack[0] < stack[2] && stack[2] < stack[1])
	{
		operate(RRA, data);
		operate(SA, data);
	}
	else if (stack[1] < stack[0] && stack[0] < stack[2])
		operate(SA, data);
	else if (stack[2] < stack[0] && stack[0] < stack[1])
		operate(RRA, data);
	else if (stack[1] < stack[2] && stack[2] < stack[0])
		operate(RA, data);
	else if (stack[2] < stack[1] && stack[1] < stack[0])
	{
		operate(RA, data);
		operate(SA, data);
	}
}
