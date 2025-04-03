/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:27:01 by dderny            #+#    #+#             */
/*   Updated: 2025/04/03 13:38:45 by dderny           ###   ########.fr       */
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

static t_slice	init_slice(u_int pos, size_t size, int *from)
{
	t_slice	slice;

	slice.pos = pos;
	slice.size = size;
	slice.data = malloc(size * sizeof(int));
	if (slice.data && from)
		ft_memcpy(slice.data, from, size * sizeof(int));
	slice.data = NULL;
	return (slice);
}

static void	init_subslices(t_slice slice, t_slice *subslices[3])
{
	const u_int	positions[4][3] = {
		{BOT_B, TOP_B, BOT_A},
		{BOT_B, TOP_B, TOP_A},
		{BOT_B, BOT_A, TOP_A},
		{TOP_B, BOT_A, TOP_A}};
	size_t i;

	i = -1;
	while (i++ < 2)
		(*subslices)[i] = init_slice(positions[slice.pos][i],
					slice.size / 3 + (slice.size % 3 >= i + 1 && i < 2), NULL);
	if (errno && (*subslices)[0].data)
		free((*subslices)[0].data);
	if (errno && (*subslices)[1].data)
		free((*subslices)[1].data);
	if (errno && (*subslices)[2].data)
		free((*subslices)[2].data);
}


int	quicksort(t_sdata *data, t_slice slice)
{
	t_slice		subslices[3];

	if (!slice.data)
		slice = init_slice(TOP_A, data->a.size, data->a.data);
	move_to_top(data, &slice);
	if (slice.size <= 3)
		return (quicksort_base_case(data, slice));
	init_subslices(slice, (t_slice **)&subslices);
	if (errno)
		free(slice.data);
	if (errno)
		return (1);
	dispatch_in_subchunks(chunk, subchunks, data)
	quicksort(data, subslices[0])
	quicksort(data, subslices[1])
	quicksort(data, subslices[2]);
	free(slice.data);
	return (0);
}
