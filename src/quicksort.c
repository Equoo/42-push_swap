/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:27:01 by dderny            #+#    #+#             */
/*   Updated: 2025/04/03 16:01:48 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"
#include <limits.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

int	get_min(t_slice slice)
{
	u_int	i;
	int		min;

	min = INT_MAX;
	i = 0;
	while (i < slice.size)
	{
		if (min > slice.data[i])
			min = slice.data[i];
		i++;
	}
	return (min);
}

static void	reverse_slice(t_slice slice)
{
	u_int	i;
	u_int	temp;

	i = 0;
	while (i < slice.size / 2)
	{
		temp = slice.data[i];
		slice.data[i] = slice.data[slice.size - 1 - i];
		slice.data[slice.size - 1 - i] = temp;
		i++;
	}
}

void	move_to_top(t_sdata *data, t_slice *slice)
{
	if (slice->pos == BOT_A && slice->size == data->a.size)
	{
		slice->pos = TOP_A;
		reverse_slice(*slice);
	}
	if (slice->pos == BOT_B && slice->size == data->b.size)
	{
		slice->pos = TOP_B;
		reverse_slice(*slice);
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

void	split_slice(t_sdata *data, t_slice slice, t_slice subslices[3])
{
	size_t	i;
	t_slice	*subslice;
	int		base;

	i = 0;
	base = get_min(slice);
	subslices[0].data += subslices[0].size - 1;
	subslices[1].data += subslices[1].size - 1;
	subslices[2].data += subslices[2].size - 1;
	while (i < slice.size)
	{
		slice.data[i] = slice.data[i] - base;
		subslice = &subslices[3];
		if ((size_t)slice.data[i] < subslices[0].size)
			subslice = &subslices[0];
		else if ((size_t)slice.data[i] < subslices[0].size + subslices[1].size)
			subslice = &subslices[1];
		move_from_to(data, slice.pos, subslice->pos);
		*subslice->data-- = slice.data[i];
		i++;
	}
}

int	quicksort_base_case(t_sdata *data, t_slice slice)
{
	size_t	i;

	i = 0;
	while (i < slice.size)
	{
		move_from_to(data, slice.pos, TOP_A);
		i++;
	}
	if (slice.size <= 1)
		return (1);
	if (slice.size == 2)
		if (data->a.data[0] > data->a.data[1])
			operate(SA, data);
	if (slice.size == 3)
		sort_three(data);
	return (1);
}

int	quicksort(t_sdata *data, t_slice slice)
{
	t_slice		subslices[3];

	if (!slice.data)
		slice = init_slice(TOP_A, data->a.size, data->a.data);
	move_to_top(data, &slice);
	if (slice.size <= 3 && quicksort_base_case(data, slice))
		return (0);
	if (init_subslices(slice, (t_slice **)&subslices))
		return (1);
	split_slice(data, slice, subslices);
	quicksort(data, subslices[0]);
	quicksort(data, subslices[1]);
	quicksort(data, subslices[2]);
	free(slice.data);
	return (0);
}
