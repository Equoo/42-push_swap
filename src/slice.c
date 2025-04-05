/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 00:28:15 by dderny            #+#    #+#             */
/*   Updated: 2025/04/06 01:13:30 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <errno.h>
#include <libft.h>
#include <stdlib.h>

void	free_slice(t_slice *slice)
{
	size_t	i;

	if (!slice)
		return ;
	i = 0;
	while (i < 3)
	{
		free_slice(slice->subslices[i]);
		i++;
	}
	free(slice->data);
	free(slice);
}

t_slice	*init_slice(size_t size, u_int *from)
{
	t_slice	*slice;
	size_t	i;

	if (errno)
		return (NULL);
	slice = ft_calloc(1, sizeof(t_slice));
	if (!slice)
		return (NULL);
	slice->pos = 0;
	slice->size = size;
	slice->data = ft_calloc(size, sizeof(int));
	if (!slice->data)
	{
		free(slice);
		return (NULL);
	}
	if (from)
		ft_memcpy(slice->data, from, size * sizeof(int));
	i = 3;
	if (slice->size > 3)
		while (i--)
			slice->subslices[i] = init_slice(slice->size / 3 + (slice->size
						% 3 >= i + 1 && i < 2), NULL);
	return (slice);
}
