/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:56 by dderny            #+#    #+#             */
/*   Updated: 2025/03/28 01:59:27 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_vector.h"
#include "stack.h"

#include <libft.h>
#include <ft_bool.h>
#include <errno.h>
#include <ft_printf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void	sort_list(int *nums, size_t size)
{
	size_t	i;
	size_t	j;
	int		swap;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (nums[i] > nums[j])
			{
				swap = nums[i];
				nums[i] = nums[j];
				nums[j] = swap;
			}
			j++;
		}
		i++;
	}
}

void	partition(t_sdata *data, size_t size)
{
	if (size <= 3)
	{
		if (size == 2)
		{
			if (data->a.data[0] > data->a.data[1])
				operate(SA, data);
		}
		else if (size == 3)
		{
			if (data->a.data[0] > data->a.data[1] && data->a.data[0] > data->a.data[2])
			{
				operate(RA, data);
				if (data->a.data[0] > data->a.data[1])
					operate(SA, data);
			}
			else if (data->a.data[0] > data->a.data[1] && data->a.data[0] < data->a.data[2])
				operate(SA, data);
			else if (data->a.data[0] < data->a.data[1] && data->a.data[0] > data->a.data[2])
				operate(RRA, data);
			else if (data->a.data[0] < data->a.data[1] && data->a.data[0] < data->a.data[2])
			{
				operate(RA, data);
				operate(SA, data);
				operate(RRA, data);
			}
		}
		return ;
	}
	
	size_t	median;
	size_t	i;
	size_t	j;

	int	*nums = ft_calloc(size, sizeof(int));
	if (!nums && print_error("Memory allocation"))
		return ;
	ft_memcpy(nums, data->a.data, size * sizeof(int));
	
	median = size / 2;
	i = 0;
	j = 0;
	while (i < size)
	{
		if (nums[i] < nums[median])
		{
			operate(PB, data);
			j++;
		}
		else
			operate(RA, data);
		i++;
	}

	free(nums);
	
	i = 0;
	while (i < j)
	{
		operate(PA, data);
		i++;
	}
	
	partition(data, j);
	partition(data, size - j);
}


int	main(int argc, char **argv)
{
	t_sdata		data;
	int		i;

	if (argc < 2)
	{
		print_cerror("Usage", ERRINITUSAGE);
		return (EXIT_FAILURE);
	}
	data.a.total_size = argc - 1;
	data.b.total_size = argc - 1;
	data.a.data = ft_calloc(data.a.total_size, sizeof(int));
	data.b.data = ft_calloc(data.b.total_size, sizeof(int));
	data.a.size = 0;
	data.b.size = 0;
	if ((!data.a.data || !data.b.data) && print_error("Stack creation"))
		return (EXIT_FAILURE);
	
	i = 1;
	while (i < argc)
	{
		char *endptr;
		data.a.data[i - 1] = ft_strtol(argv[i], &endptr, 0);
		if (*endptr && print_cerror("Invalid number", ERRINITENTRY))
			return (EXIT_FAILURE);
		i++;
	}
	data.a.size = data.a.total_size;
	
	data.ops = vec_new((argc - 1) * 7, sizeof(uint8_t));
	
	partition(&data, data.a.total_size);
	
	const char **op = (const char *[]){"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"};
	i = 0;
	while (i < data.ops.actual_size)
	{
		ft_printf("%s\n", op[data.ops.data[i]]);
		i++;
	}

	free(data.a.data);
	free(data.b.data);
	vec_destroy(&data.ops);
	
	/*i = 0;
	while (i < argc - 1)
	{
		ft_printf("%d\n", data->a.data[i]);
		i++;
	}*/
	return (EXIT_SUCCESS);
}
