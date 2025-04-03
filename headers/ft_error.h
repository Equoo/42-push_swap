/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:37 by dderny            #+#    #+#             */
/*   Updated: 2025/04/03 15:40:49 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# define ERRINIT ""
# define ERRINITUSAGE 1000
# define ERRINITENTRY 1003
# define ERRINITPID 1001
# define ERRINITLEN 1002
# define ERRINITDUP 1003
# define ERRINITINVALDIDNBR 1003

int	print_error(char *category);
int	print_cerror(char *category, int error);

#endif
