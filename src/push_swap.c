/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:56 by dderny            #+#    #+#             */
/*   Updated: 2025/04/08 04:09:34 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "push_swap.h"
#include "stack.h"
#include <errno.h>
#include <libft.h>
#include <stdlib.h>

static int	sort(t_sdata *data)
{
	t_slice	*slice;

	if (data->a.size < 10)
		sort_nine(data);
	else
	{
		slice = init_slice(data->a.size, data->a.data);
		if (errno)
		{
			free_slice(slice);
			free(data->a.data);
			free(data->b.data);
			return (print_error("Slices creation"));
		}
		quicksort(data, slice);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_sdata	data;

	data = (t_sdata){0};
	if (argc < 2)
		return (EXIT_SUCCESS);
	if (init_stack(&data.a, argc - 1))
		return (print_error("Stack creation"));
	if (init_stack(&data.b, argc - 1) || fill_stack(&data, argc, argv))
	{
		free(data.a.data);
		if (data.b.data)
			free(data.b.data);
		if (errno)
			return (print_error("Stack creation"));
		return (EXIT_SUCCESS);
	}
	if (sort(&data))
		return (EXIT_FAILURE);
	free(data.a.data);
	free(data.b.data);
	return (EXIT_SUCCESS);
}
