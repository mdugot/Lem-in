/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 18:13:23 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/18 14:32:54 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		read_joker(t_printer *p, char *flag)
{
	int r;

	r = va_arg(*(p->ap), int);
	p->format += 1;
	if (flag)
		*flag = 1;
	return (r);
}

void	print_color(char c, int fd)
{
	if (c == 'R' || c == 'r')
		ft_putstr_fd(C_RED, fd);
	else if (c == 'G' || c == 'g')
		ft_putstr_fd(C_GREEN, fd);
	else if (c == 'Y' || c == 'y')
		ft_putstr_fd(C_YELLOW, fd);
	else if (c == 'B' || c == 'b')
		ft_putstr_fd(C_BLUE, fd);
	else if (c == 'M' || c == 'm')
		ft_putstr_fd(C_MAGENTA, fd);
	else if (c == 'C' || c == 'c')
		ft_putstr_fd(C_CYAN, fd);
	else if (c == 'W' || c == 'w')
		ft_putstr_fd(C_WHITE, fd);
	else if (c == 'N' || c == 'n')
		ft_putstr_fd(C_NORMAL, fd);
	else
		ft_putstr_fd(RESET, fd);
}

void	read_color(t_printer *p)
{
	print_color(p->format[0], p->fd);
	if (p->format[0])
		p->format += 1;
}

char	*one_char_str(char c)
{
	char *str;

	str = ft_strnew(2);
	str[0] = c;
	return (str);
}
