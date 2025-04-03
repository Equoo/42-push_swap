/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:22:25 by dderny            #+#    #+#             */
/*   Updated: 2025/04/03 13:07:00 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stddef.h>
#include <sys/types.h>

typedef enum e_slice_pos
{
	TOP_A,
	BOT_A,
	TOP_B,
	BOT_B,
}	t_slice_pos;

typedef struct s_slice
{
	int		*data;
	size_t	size;
	u_int	pos;
}	t_slice;

#endif
