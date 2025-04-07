/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:22:25 by dderny            #+#    #+#             */
/*   Updated: 2025/04/07 19:53:11 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stack.h"
# include <stddef.h>
# include <sys/types.h>

typedef enum e_slice_pos
{
	TOP_A,
	BOT_A,
	TOP_B,
	BOT_B,
}					t_slice_pos;

typedef struct s_slice
{
	u_int			*data;
	size_t			size;
	u_int			pos;
	struct s_slice	*subslices[3];
}					t_slice;

int					init_stack(t_stack *stack, size_t size);
int					fill_stack(t_sdata *data, size_t argc, char **argv);

t_slice				*init_slice(size_t size, u_int *from);
void				free_slice(t_slice *slice);

u_int				get_min(t_slice *slice);
void				move_from_to(t_sdata *data, u_int from, u_int to);
void				move_to_top(t_sdata *data, t_slice *slice);
void				reverse_slice(t_slice *slice);
void				sort_three_top_a(t_sdata *data);

void				sort_nine(t_sdata *data);
int					quicksort(t_sdata *data, t_slice *slice);

#endif
