/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:08:31 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/07 14:42:57 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	exit_error(char *str)
{
	if (str != NULL)
		ft_printf_fd(1, "ERROR : %s\n", str);
	else
		ft_printf_fd(1, "ERROR\n");
	exit(1);
}

void	*secure_alloc(size_t size)
{
	void *result;

	result = ft_memalloc(size);
	if (result == NULL)
		exit_error(strerror(errno));
	return (result);
}
