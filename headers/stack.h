/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:18:46 by dderny            #+#    #+#             */
/*   Updated: 2025/04/06 01:43:24 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <ft_bool.h>
# include <ft_vector.h>
# include <stddef.h>
# include <sys/types.h>

typedef struct s_stack
{
	u_int	*data;
	size_t	size;
	size_t	total_size;
}			t_stack;

typedef struct s_sdata
{
	t_stack	a;
	t_stack	b;
}			t_sdata;

typedef enum e_op
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
}			t_op;

int			ps_strtoi(const char *nptr, char **endptr, int base);

void		push(t_stack *from, t_stack *to);
void		swap(t_stack *stack);
void		rotate(t_stack *stack, t_bool reverse);

void		operate(uint8_t op, t_sdata *data);
void		operate_for(uint8_t op, ssize_t count, t_sdata *data);

#endif
