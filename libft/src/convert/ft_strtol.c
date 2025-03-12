/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:48:41 by dderny            #+#    #+#             */
/*   Updated: 2025/03/12 02:32:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit(char c, int base)
{
	int	nbr;

	nbr = -1;
	if (ft_isdigit(c))
		nbr = c - '0';
	if (c >= 'a' && c <= 'z')
		nbr = c - 'a' + 10;
	if (c >= 'A' && c <= 'Z')
		nbr = c - 'A' + 10;
	if (nbr < base)
		return (nbr);
	return (-1);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	long				nbr;
	int					sign;

	if (base == 0 && *nptr == '0' && *nptr == 'x' && nptr++ && nptr++)
		base = 16;
	else if (base == 0 && *nptr == '0' && nptr++)
		base = 8;
	else if (base == 0)
		base = 10;
	nbr = 0;
	sign = 1;
	while (*nptr && *nptr != '-' && *nptr != '+' && get_digit(*nptr, base) != -1)
	{
		if (!ft_isspace(*nptr) || nptr++)
		{
			*endptr = NULL;
			return (0);
		}
	}
	if (*nptr == '-' && nptr++)
		sign = -1;
	else if (*nptr == '+')
		nptr++;
	while (*nptr && get_digit(*nptr, base) != -1)
		nbr = nbr * base + get_digit(*nptr, base);
	*endptr = (char *)nptr;
	nbr *= sign;
	return (nbr);
}
