/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:56 by dderny            #+#    #+#             */
/*   Updated: 2025/04/03 23:46:24 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "push_swap.h"
#include "stack.h"

#include <libft.h>
#include <ft_bool.h>
#include <errno.h>
#include <ft_printf.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int	init_stack(t_stack *stack, size_t size)
{
	stack->data = ft_calloc(size, sizeof(int));
	if (!stack->data)
		return (1);
	stack->size = 0;
	stack->total_size = size;
	return (0);
}

static int	fill_stack(t_sdata *data, size_t argc, char **argv)
{
	char 		*endptr;
	size_t		i;

	i = 1;
	while (i < argc)
	{
		data->a.data[i - 1] = ft_strtoi(argv[i], &endptr, 0);
		data->a.size++;
		if (*endptr)
			errno = ERRINITINVALDIDNBR;
		if (errno)
			return (1);
		i++;
	}
	return (0);
}

static int	is_duplicate(t_stack stack)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < stack.size)
	{
		j = i + 1;
		while (j < stack.size)
		{
			if (stack.data[i] == stack.data[j])
			{
				errno = ERRINITDUP;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_sorted(t_stack stack)
{
	size_t	i;

	i = 0;
	while (i < stack.size - 1)
	{
		if (stack.data[i] > stack.data[i + 1])
			break ;
		i++;
	}
	if (i == stack.size - 1)
	{
		errno = ERRINITSORT;
		return (1);
	}
	return (0);
}

static t_slice	*init_slice(u_int pos, size_t size, int *from);

static int	init_subslices(t_slice *slice)
{
	const u_int	positions[4][3] = {
		{BOT_B, TOP_B, BOT_A},
		{BOT_B, TOP_B, TOP_A},
		{BOT_B, BOT_A, TOP_A},
		{TOP_B, BOT_A, TOP_A}};
	size_t i;

	i = -1;
	while (++i < 3)
		slice->subslices[i] = init_slice(positions[slice->pos][i],
					slice->size / 3 + (slice->size % 3 >= i + 1 && i < 2), NULL);
	if (errno)
	{
		i = -1;
		while (++i < 3)
		{
			if (!slice->subslices[i])
				continue ;
			free(slice->subslices[i]->data);
			free(slice->subslices[i]);
		}
		return (1);
	}
	return (0);
}

static t_slice	*init_slice(u_int pos, size_t size, int *from)
{
	t_slice	*slice;

	slice = ft_calloc(1, sizeof(t_slice));
	if (!slice)
		return (NULL);
	slice->pos = pos;
	slice->size = size;
	slice->data = ft_calloc(size, sizeof(int));
	if (!slice->data)
	{
		free(slice);
		return (NULL);
	}
	if (from)
		ft_memcpy(slice->data, from, size * sizeof(int));
	if (slice->size <= 3)
		return (slice);
	if (init_subslices(slice))
	{
		free(slice->data);
		free(slice);
		return (NULL);
	}
	return (slice);
}

int	main(int argc, char **argv)
{
	t_sdata		data;
	t_slice		*slice;

	data = (t_sdata){0};
	if (argc < 2)
		return (print_cerror("Usage", ERRINITUSAGE));
	if (init_stack(&data.a, argc - 1))
		return (print_error("Stack creation"));
	if (init_stack(&data.b, argc - 1) || fill_stack(&data, argc, argv)
		|| is_duplicate(data.a) || is_sorted(data.a))
	{
		free(data.a.data);
		if (data.b.data)
			free(data.b.data);
		return (print_error("Stack creation"));
	}
	if (data.a.size < 10)
		sort_ten(&data);
	else
	{
		slice = init_slice(TOP_A, data.a.size, data.a.data);
		if (errno)
		{
			free(data.a.data);
			free(data.b.data);
			return (print_error("Slice creation"));
		}
		quicksort(&data, slice);
	}
	free(data.a.data);
	free(data.b.data);
	return (EXIT_SUCCESS);
}
