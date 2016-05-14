/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 15:46:50 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/18 14:30:24 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_str(char *str, t_value *v, int fd)
{
	ft_putstr_fd(str, fd);
	if (v->char_null)
		ft_putchar_fd(*str, fd);
}

void	wprint_str(US *str, t_value *v, int fd, int size)
{
	ft_putwstr_size_fd(str, fd, size);
	if (v->char_null)
		ft_putwchar_fd(*str, fd);
}
