/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 00:38:16 by dderny            #+#    #+#             */
/*   Updated: 2025/04/08 04:10:18 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "stack.h"
#include <errno.h>
#include <libft.h>
#include <stdlib.h>

int	init_stack(t_stack *stack, size_t size)
{
	stack->data = ft_calloc(size, sizeof(int));
	if (!stack->data)
		return (1);
	stack->size = 0;
	stack->total_size = size;
	return (0);
}

static void	get_indexes(size_t size, int *numbers, u_int *res)
{
	u_int	i;
	u_int	j;

	i = 0;
	while (i < size)
	{
		res[i] = 0;
		j = 0;
		while (j < size)
		{
			res[i] += numbers[j] < numbers[i];
			j++;
		}
		i++;
	}
}

static int	is_duplicate(int *numbers, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (numbers[i] == numbers[j])
			{
				errno = ERRINITINVALDIDNBR;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_sorted(int *numbers, size_t size)
{
	size_t	i;

	if (size < 2)
		return (0);
	i = 0;
	while (i < size - 1)
	{
		if (numbers[i] > numbers[i + 1])
			break ;
		i++;
	}
	if (i == size - 1)
		return (1);
	return (0);
}

int	fill_stack(t_sdata *data, size_t argc, char **argv)
{
	char	*endptr;
	int		*numbers;
	size_t	i;

	i = 0;
	numbers = ft_calloc(argc - 1, sizeof(int));
	if (!numbers)
		return (1);
	while (++i < argc)
	{
		numbers[i - 1] = ps_strtoi(argv[i], &endptr, 0);
		if (*endptr)
			errno = ERRINITINVALDIDNBR;
		if (errno)
			return (1);
	}
	data->a.size = argc - 1;
	if (is_sorted(numbers, argc - 1) || is_duplicate(numbers, argc - 1))
	{
		free(numbers);
		return (1);
	}
	get_indexes(data->a.size, numbers, data->a.data);
	free(numbers);
	return (0);
}
