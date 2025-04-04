/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:27:01 by dderny            #+#    #+#             */
/*   Updated: 2025/04/04 20:21:20 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "push_swap.h"
#include "stack.h"
#include <limits.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

u_int	get_min(t_slice *slice)
{
	u_int	i;
	u_int		min;

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

static void	reverse_slice(t_slice *slice)
{
	u_int	i;
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

void	move_to_top(t_sdata *data, t_slice *slice)
{
	if (slice->pos == BOT_A && slice->size == data->a.size)
	{
		slice->pos = TOP_A;
		reverse_slice(slice);
	}
	if (slice->pos == BOT_B && slice->size == data->b.size)
	{
		slice->pos = TOP_B;
		reverse_slice(slice);
	}
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

void	split_slice(t_sdata *data, t_slice *slice)
{
	size_t	i;
	u_int	base;
	t_slice	subslices[3];
	t_slice	*subslice;

	base = get_min(slice);
	i = -1;
	while (++i < 3)
	{
		subslices[i] = *(slice->subslices[i]);
		subslices[i].data += subslices[i].size - 1;
	}
	i = 0;
	while (i < slice->size)
	{
		slice->data[i] = slice->data[i] - base;
		subslice = &subslices[2];
		if ((u_int)slice->data[i] < (u_int)subslices[0].size)
			subslice = &subslices[0];
		else if ((u_int)slice->data[i] < (u_int)(subslices[0].size + subslices[1].size))
			subslice = &subslices[1];
		move_from_to(data, slice->pos, subslice->pos);
		*subslice->data-- = slice->data[i];
		i++;
	}
}

static void	sort_three_top_a(t_sdata *data)
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

int	quicksort_base_case(t_sdata *data, t_slice *slice)
{
	size_t	i;

	i = 0;
	while (i < slice->size)
	{
		move_from_to(data, slice->pos, TOP_A);
		i++;
	}
	if (slice->size == 2)
		if (data->a.data[0] > data->a.data[1])
			operate(SA, data);
	if (slice->size == 3)
		sort_three_top_a(data);
	free(slice->data);
	free(slice);
	return (1);
}

int	quicksort(t_sdata *data, t_slice *slice)
{
	//static u_int	count = 0;

	//print_array(slice->data, slice->size);
	move_to_top(data, slice);
	if (slice->size <= 3 && quicksort_base_case(data, slice))
		return (0);
	split_slice(data, slice);
	//__builtin_printf("quicksort %d, %p, %d\n", count++, slice->subslices[0], slice->subslices[0]->data[0]);
	quicksort(data, slice->subslices[2]);
	quicksort(data, slice->subslices[1]);
	quicksort(data, slice->subslices[0]);
	free(slice->data);
	free(slice);
	return (0);
}
