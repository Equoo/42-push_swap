/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:56 by dderny            #+#    #+#             */
/*   Updated: 2025/03/11 22:28:35 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "stack.h"

#include <libft.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	int		i;

	if (argc < 2)
	{
		print_cerror("Usage", ERRINITUSAGE);
		return (EXIT_FAILURE);
	}
	stack_a.size = argc - 1;
	stack_b.size = argc - 1;
	stack_a.stack = ft_calloc(stack_a.size, sizeof(int));
	stack_b.stack = ft_calloc(stack_b.size, sizeof(int));
	if ((!stack_a.stack || !stack_b.stack) && print_error("Stack creation"))
		return (EXIT_FAILURE);
	i = 1;
	while (i < argc)
	{
		stack_a.stack[i - 1] = argv[i];
	}
	return (EXIT_SUCCESS);
}
