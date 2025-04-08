/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:28:02 by dderny            #+#    #+#             */
/*   Updated: 2025/04/08 04:12:13 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "push_swap.h"
#include "stack.h"
#include <errno.h>
#include <get_next_line.h>
#include <libft.h>
#include <sys/types.h>
#include <unistd.h>

static int	check(t_sdata *data)
{
	const char	**ops = (const char *[]){"sa", "sb", "ss", "pa", "pb", "ra",
		"rb", "rr", "rra", "rrb", "rrr"};
	char		*line;
	int			i;

	while (!errno)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		i = 0;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		while (i < 11 && ft_strcmp(line, ops[i]))
			i++;
		if (i > 10)
			free(line);
		if (i > 10)
			return (1);
		operate(i, data);
		free(line);
	}
	if (errno)
		return (print_error("Get_next_line"));
	return (0);
}

u_int	is_sorted(u_int *numbers, size_t size)
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
	{
		errno = ERRINITSORT;
		return (1);
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
	if (!check(&data) && !errno && (data.a.size < 2 || is_sorted(data.a.data,
				data.a.size)) && data.b.size == 0)
		write(STDOUT_FILENO, "OK\n", 3);
	else if (!errno)
		write(STDOUT_FILENO, "KO\n", 3);
	free(data.a.data);
	free(data.b.data);
	return (EXIT_SUCCESS);
}
