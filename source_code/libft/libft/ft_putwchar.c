/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 17:46:01 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/16 16:11:32 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

unsigned int	do_mask(US c, US mask, US apply_mask)
{
	unsigned int	result;
	unsigned int	cursor_mask;
	unsigned int	cursor_c;

	cursor_mask = 1;
	cursor_c = 1;
	result = 0;
	while (cursor_mask != 0x80000000)
	{
		if (cursor_mask & apply_mask)
			result = result | (cursor_mask & mask);
		else
		{
			if (cursor_c & c)
				result = result | cursor_mask;
			cursor_c = cursor_c << 1;
		}
		cursor_mask = cursor_mask << 1;
	}
	return (result);
}

void			ft_putoctet_fd(unsigned char *c, int n, int fd)
{
	if (n == 1)
		write(1, &(c[0]), fd);
	else if (n == 2)
	{
		write(1, &(c[1]), fd);
		write(1, &(c[0]), fd);
	}
	else if (n == 3)
	{
		write(1, &(c[2]), fd);
		write(1, &(c[1]), fd);
		write(1, &(c[0]), fd);
	}
	else
	{
		write(1, &(c[3]), fd);
		write(1, &(c[2]), fd);
		write(1, &(c[1]), fd);
		write(1, &(c[0]), fd);
	}
}

void			ft_putwchar_fd(unsigned int c, int fd)
{
	int				sb;

	sb = significant_bit(&c, 4);
	if (sb <= 7)
		ft_putchar_fd(c, fd);
	else if (sb <= 11)
	{
		c = do_mask(c, 0xC080, 0xE0C0);
		ft_putoctet_fd((unsigned char*)&c, 2, fd);
	}
	else if (sb <= 16)
	{
		c = do_mask(c, 0xE08080, 0xF0C0C0);
		ft_putoctet_fd((unsigned char*)&c, 3, fd);
	}
	else
	{
		c = do_mask(c, 0xF0808080, 0xF8C0C0C0);
		ft_putoctet_fd((unsigned char*)&c, 4, fd);
	}
}

void			ft_putwstr_fd(unsigned int *str, int fd)
{
	while (*str)
	{
		ft_putwchar_fd(*str, fd);
		str++;
	}
}

void			ft_putwstr_size_fd(unsigned int *str, int fd, int size)
{
	int i;

	i = 0;
	while (*str && (i < size || size < 0))
	{
		ft_putwchar_fd(*str, fd);
		str++;
		i++;
	}
}
