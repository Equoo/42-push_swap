/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:56 by dderny            #+#    #+#             */
/*   Updated: 2025/03/16 00:41:19 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_vector.h"
#include "stack.h"

#include <libft.h>
#include <ft_bool.h>
#include <errno.h>
#include <ft_printf.h>
#include <stdlib.h>




void	swap(t_stack *stack)
{
	int	swap;

	if(stack->actual_size <= 1)
		return ;
	swap = stack->data[0];
	stack->data[0] = stack->data[1];
	stack->data[1] = swap;	
}

void	push(t_stack *from, t_stack *to)
{
	if (!from->actual_size)
		return ;
	if (to->actual_size > 1)
		ft_memmove(to->data + 1, to->data, to->actual_size - 1);
	to->data[0] = from->data[0];
	to->actual_size++;
	ft_memmove(from->data, from->data + 1, from->actual_size - 1);
	from->actual_size--;
	from->data[from->actual_size] = 0;
}

void	rotate(t_stack *stack, t_bool reverse)
{
	int	swap;

	if (reverse)
	{
		swap = stack->data[stack->actual_size];
		ft_memmove(stack->data + 1, stack->data, stack->actual_size - 1);
		stack->data[0] = swap;
	}
	else
	{
		swap = stack->data[0];	
		ft_memmove(stack->data, stack->data + 1, stack->actual_size - 1);
		stack->data[stack->actual_size - 1] = swap;
	}
}

//void	sa(t_vector *operations, t_stack *stack_a)
//{
//	const t_op	op = OP_SA;

//	vec_append(operations, (void *)&op);
//	swap(stack_a);
//}

//void	sb(t_vector *operations, t_stack *stack_b)
//{
//	const t_op	op = OP_SB;

//	vec_append(operations, (void *)&op);
//	swap(stack_b);
//}

//void	ss(t_vector *operations, t_stack *stack_a, t_stack *stack_b)
//{
//	const t_op	op = OP_SS;

//	vec_append(operations, (void *)&op);
//	swap(stack_a);
//	swap(stack_b);
//}

//void	pa(t_vector *operations, t_stack *stack_a, t_stack *stack_b)
//{
//	const t_op	op = OP_PA;

//	vec_append(operations, (void *)&op);
//	push(stack_b, stack_a);
//}

//void	pb(t_vector *operations, t_stack *stack_a, t_stack *stack_b)
//{
//	const t_op	op = OP_PB;

//	vec_append(operations, (void *)&op);
//	push(stack_b, stack_a);
//}

//void	ra(t_vector *operations, t_stack *stack_a)
//{
//	const t_op	op = OP_RA;

//	vec_append(operations, (void *)&op);
//	rotate(stack_a, FALSE);
//}

//void	rb(t_vector *operations, t_stack *stack_b)
//{
//	const t_op	op = OP_RA;

//	vec_append(operations, (void *)&op);
//	rotate(stack_b, FALSE);
//}

//void	rr(t_vector *operations, t_stack *stack_a, t_stack *stack_b)
//{
//	const t_op	op = OP_RR;

//	vec_append(operations, (void *)&op);
//	rotate(stack_a, FALSE);
//	rotate(stack_b, FALSE);
//}

//void	rra(t_vector *operations, t_stack *stack_a)
//{
//	const t_op	op = OP_RA;

//	vec_append(operations, (void *)&op);
//	rotate(stack_a, TRUE);
//}

//void	rrb(t_vector *operations, t_stack *stack_b)
//{
//	const t_op	op = OP_RA;

//	vec_append(operations, (void *)&op);
//	rotate(stack_b, TRUE);
//}

//void	rrr(t_vector *operations, t_stack *stack_a, t_stack *stack_b)
//{
//	const t_op	op = OP_RR;

//	vec_append(operations, (void *)&op);
//	rotate(stack_a, TRUE);
//	rotate(stack_b, TRUE);
//}

void	operate(t_op op, t_vector *operations, t_stack *stack_a, t_stack *stack_b)
{
	vec_append(operations, (void *)&op);
	if (op == OP_SA || op == OP_SS)
		swap(stack_a);
	if (op == OP_SB || op == OP_SS)
		swap(stack_b);
	if (op == OP_PA)
		push(stack_b, stack_a);
	if (op == OP_PB)
		push(stack_a, stack_b);
	if (op == OP_RA || op == OP_RR)
		rotate(stack_a, FALSE);
	if (op == OP_RB || op == OP_RR)
		rotate(stack_b, FALSE);
	if (op == OP_RRA || op == OP_RRR)
		rotate(stack_a, TRUE);
	if (op == OP_RRB || op == OP_RRR)
		rotate(stack_b, TRUE);
}




int	main(int argc, char **argv)
{
	t_stack		stack_a;
	t_stack		stack_b;
	t_vector	operations;
	int		i;

	if (argc < 2)
	{
		print_cerror("Usage", ERRINITUSAGE);
		return (EXIT_FAILURE);
	}
	stack_a.size = argc - 1;
	stack_b.size = argc - 1;
	stack_a.data = ft_calloc(stack_a.size, sizeof(int));
	stack_b.data = ft_calloc(stack_b.size, sizeof(int));
	if ((!stack_a.data || !stack_b.data) && print_error("Stack creation"))
		return (EXIT_FAILURE);
	
	i = 1;
	while (i < argc)
	{
		char *endptr;
		stack_a.data[i - 1] = ft_strtol(argv[i], &endptr, 0);
		if (*endptr && print_cerror("Invalid number", ERRINITENTRY))
			return (EXIT_FAILURE);
		i++;
	}
	stack_a.actual_size = stack_a.size;

	operations = vec_new((argc - 1) * 4, sizeof(t_op));
	

	

	
	i = 0;
	while (i < argc - 1)
	{
		ft_printf("%d\n", stack_a.data[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
