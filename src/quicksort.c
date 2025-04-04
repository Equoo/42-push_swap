/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:27:01 by dderny            #+#    #+#             */
/*   Updated: 2025/04/05 00:34:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "push_swap.h"
#include "stack.h"
#include <libgen.h>
#include <stdint.h>
#include <limits.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

u_int	get_min(t_slice *slice)
{
	u_int	i;
	u_int		min;

	min = INT_MAX;
	i = 0;
	while (i < slice->size)
	{
		if (min > slice->data[i])
			min = slice->data[i];
		i++;
	}
	return (min);
}

static void	reverse_slice(t_slice *slice)
{
	size_t	i;
	u_int	temp;

	i = 0;
	while (i < slice->size / 2)
	{
		temp = slice->data[i];
		slice->data[i] = slice->data[slice->size - 1 - i];
		slice->data[slice->size - 1 - i] = temp;
		i++;
	}
}

void	move_to_top(t_sdata *data, t_slice *slice)
{
	if (slice->pos == BOT_A && slice->size == data->a.size)
	{
		slice->pos = TOP_A;
		reverse_slice(slice);
	}
	if (slice->pos == BOT_B && slice->size == data->b.size)
	{
		slice->pos = TOP_B;
		reverse_slice(slice);
	}
}

void	move_from_to(t_sdata *data, u_int from, u_int to)
{
	if (from == to)
		return ;
	if (from == BOT_A)
		operate(RRA, data);
	if ((from == TOP_A || from == BOT_A) && (to == TOP_B || to == BOT_B))
		operate(PB, data);
	if ((from == TOP_A || from == BOT_A || from == TOP_B) && to == BOT_B)
		operate(RB, data);
	if (from == BOT_B)
		operate(RRB, data);
	if ((from == TOP_B || from == BOT_B) && (to == TOP_A || to == BOT_A))
		operate(PA, data);
	if ((from == TOP_B || from == BOT_B || from == TOP_A) && to == BOT_A)
		operate(RA, data);
}

void	split_slice(t_sdata *data, t_slice *slice)
{
	size_t	i;
	u_int	base;
	t_slice	subslices[3];
	t_slice	*subslice;

	base = get_min(slice);
	i = -1;
	while (++i < 3)
	{
		subslices[i] = *(slice->subslices[i]);
		subslices[i].data += subslices[i].size - 1;
	}
	i = 0;
	while (i < slice->size)
	{
		slice->data[i] = slice->data[i] - base;
		subslice = &subslices[2];
		if (slice->data[i] < subslices[0].size)
			subslice = &subslices[0];
		else if (slice->data[i] < subslices[0].size + subslices[1].size)
			subslice = &subslices[1];
		move_from_to(data, slice->pos, subslice->pos);
		*subslice->data-- = slice->data[i];
		i++;
	}
}

static void	sort_three_top_a(t_sdata *data)
{
	u_int	*stack;

	stack = data->a.data;
	if (stack[2] < stack[1] && stack[1] < stack[0])
		operate(SA, data);
	if (stack[2] < stack[0] && stack[0] < stack[1])
	{
		operate(RA, data);
		operate(SA, data);
		operate(RRA, data);
	}
	if (stack[1] < stack[2] && stack[2] < stack[0])
		operate(SA, data);
	if (stack[0] < stack[2] && stack[2] < stack[1])
	{
		operate(RA, data);
		operate(SA, data);
		operate(RRA, data);
	}
	if (stack[1] < stack[0] && stack[0] < stack[2])
		operate(SA, data);
}

int	quicksort_base_case(t_sdata *data, t_slice *slice)
{
	size_t	i;

	i = 0;
	while (i < slice->size)
	{
		move_from_to(data, slice->pos, TOP_A);
		i++;
	}
	if (slice->size == 2)
		if (data->a.data[0] > data->a.data[1])
			operate(SA, data);
	if (slice->size == 3)
		sort_three_top_a(data);
	free(slice->data);
	free(slice);
	return (1);
}



#include "backtrace.h"

void error_callback(void *data, const char *msg, int errnum) {
	(void)data; // Unused parameter
	if (errnum == 0)
		fprintf(stderr, "Error: %s\n", msg);
	else
		fprintf(stderr, "Error: %s: %s\n", msg, strerror(errnum));
}

int full_callback(void *data, uintptr_t pc, const char *filename, int lineno, const char *function) {
    static char exe_path[PATH_MAX] = {0};
	(void)data; // Unused parameter
    if (!filename || !function)
        return 0;

    // Get the executable's path once
    if (exe_path[0] == '\0') {
        ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
        if (len != -1) {
            exe_path[len] = '\0';
            // Get directory part only
            dirname(exe_path);
        }
    }

    // Remove common prefix (executable path)
    const char *short_filename = filename;
    if (strncmp(filename, exe_path, strlen(exe_path)) == 0) {
        short_filename = filename + strlen(exe_path);
        if (*short_filename == '/')
            short_filename++; // Remove leading slash
    }

    printf("%#lx: %s (%s:%d)\n", pc,
           function ? function : "??",
           short_filename ? short_filename : "??",
           lineno);

    return 0;
}

void print_backtrace(const char *funcname) {
	(void)funcname; // Unused parameter
    struct backtrace_state *state = backtrace_create_state(NULL, 1, error_callback, NULL);
    backtrace_full(state, 1, full_callback, error_callback, NULL);
}

void	print_array(u_int *array, size_t size)
{
	size_t	i;

	ft_printf("-------------------------\n");
	i = 0;
	while (i < size)
	{
		ft_printf("%d ", array[i]);
		i++;
	}
	ft_printf("\n-------------------------\n");
}


int	quicksort(t_sdata *data, t_slice *slice)
{
	//static u_int	count = 0;

	//print_array(slice->data, slice->size);
	//print_backtrace("quicksort");
	if (slice->size > 3)
		print_array(slice->data, slice->size);
	
	move_to_top(data, slice);
	if (slice->size <= 3 && quicksort_base_case(data, slice))
		return (0);
	split_slice(data, slice);
	
	print_array(slice->data, slice->size);
	//print_array(slice->subslices[0]->data, slice->subslices[0]->size);
	//print_array(slice->subslices[1]->data, slice->subslices[1]->size);
	//print_array(slice->subslices[2]->data, slice->subslices[2]->size);

	quicksort(data, slice->subslices[2]);
	quicksort(data, slice->subslices[1]);
	quicksort(data, slice->subslices[0]);
	free(slice->data);
	free(slice);
	return (0);
}
