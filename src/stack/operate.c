/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:12:44 by dderny            #+#    #+#             */
/*   Updated: 2025/04/06 01:14:22 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include <ft_bool.h>
#include <libft.h>
#include <stdint.h>
#include <unistd.h>

void	operate(uint8_t op, t_sdata *data)
{
	const char	**ops = (const char *[]){"sa", "sb", "ss", "pa", "pb", "ra",
		"rb", "rr", "rra", "rrb", "rrr"};

	write(STDOUT_FILENO, ops[op], ft_strlen(ops[op]));
	write(STDOUT_FILENO, "\n", 1);
	if (op == SA || op == SS)
		swap(&data->a);
	if (op == SB || op == SS)
		swap(&data->b);
	if (op == PA)
		push(&data->b, &data->a);
	if (op == PB)
		push(&data->a, &data->b);
	if (op == RA || op == RR)
		rotate(&data->a, FALSE);
	if (op == RB || op == RR)
		rotate(&data->b, FALSE);
	if (op == RRA || op == RRR)
		rotate(&data->a, TRUE);
	if (op == RRB || op == RRR)
		rotate(&data->b, TRUE);
}
