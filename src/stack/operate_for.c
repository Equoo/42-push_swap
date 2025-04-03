/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_for.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:15:54 by dderny            #+#    #+#             */
/*   Updated: 2025/03/28 00:20:58 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

#include <stdint.h>

void	operate_for(uint8_t op, ssize_t count, t_sdata *data)
{
	ssize_t	i;

	i = 0;
	while (i < count)
	{
		operate(op, data);
		i++;
	}
}
