/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:27:01 by dderny            #+#    #+#             */
/*   Updated: 2025/04/06 01:13:11 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"
#include <libft.h>
#include <stdlib.h>

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

void	dispatch_pos(t_slice *slice)
{
	const u_int	positions[4][3] = {
	{BOT_B, TOP_B, BOT_A},
	{BOT_B, TOP_B, TOP_A},
	{BOT_B, BOT_A, TOP_A},
	{TOP_B, BOT_A, TOP_A}};
	size_t		i;

	i = 3;
	while (i--)
		slice->subslices[i]->pos = positions[slice->pos][i];
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
		if (slice->data[i] < subslices[0].size)
			subslice = &subslices[0];
		else if (slice->data[i] < subslices[0].size + subslices[1].size)
			subslice = &subslices[1];
		move_from_to(data, slice->pos, subslice->pos);
		*subslice->data-- = slice->data[i];
		i++;
	}
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
	move_to_top(data, slice);
	if (slice->size <= 3 && quicksort_base_case(data, slice))
		return (0);
	dispatch_pos(slice);
	split_slice(data, slice);
	quicksort(data, slice->subslices[2]);
	quicksort(data, slice->subslices[1]);
	quicksort(data, slice->subslices[0]);
	free(slice->data);
	free(slice);
	return (0);
}
