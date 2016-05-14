/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 14:53:22 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/07 19:56:52 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_special	is_special_com(char *str)
{
	if (ft_strcmp("##start", str) == 0)
		return (S_START);
	if (ft_strcmp("##end", str) == 0)
		return (S_END);
	if (ft_strcmp("##generator_error", str) == 0)
		exit_error("An error occured with the generator");
	return (NOT_SPECIAL);
}

int			read_number_ants(char *str, int *step)
{
	int is_int;
	int r;

	r = 0;
	is_int = ft_isint(str, &r);
	if (!is_int || r <= 0)
	{
		exit_error("Number of ants is not a positive integrer");
		return (0);
	}
	else
	{
		*step += 1;
		return (r);
	}
}

void		read_tube(char *str, t_anthill *anthill, int *step)
{
	char	**split;

	split = ft_strsplit(str, '-');
	if (ft_strsplit_size(split) != 2)
		*step = 0;
	else
		add_tube(anthill, split[0], split[1]);
	ft_deltab(split, ft_strsplit_size(split));
}

void		read_rooms(char *str, t_anthill *anthill, int *step)
{
	static t_type_room	type = R_NORMAL;
	int					special;
	t_coor				c;
	char				**split;

	if ((special = is_special_com(str)))
	{
		type = special_command(anthill, special);
		return ;
	}
	split = ft_strsplit(str, ' ');
	if (ft_strsplit_size(split) != 3)
	{
		*step += 1;
		ft_deltab(split, ft_strsplit_size(split));
		return ;
	}
	if (!ft_isint(split[1], &c.x) || !ft_isint(split[2], &c.y))
		exit_error("Coordonate is not an integrer");
	if (split[0][0] == 'L')
		exit_error("Name of a room can not begin with \'L\'");
	add_room(anthill, c, split[0], type);
	ft_deltab(split, ft_strsplit_size(split));
	type = R_NORMAL;
}

void		read_anthill(int fd, t_anthill *a)
{
	char		*s;
	int			step;
	int			r;

	s = NULL;
	step = 1;
	while (step && (r = get_next_line(fd, &s)) == 1)
	{
		if (!(s[0] == '#' && !is_special_com(s)))
		{
			if (step == 2)
				read_rooms(s, a, &step);
			if (step == 3)
				read_tube(s, a, &step);
			if (step == 1)
				a->number_ants = read_number_ants(s, &step);
		}
		if (step)
			ft_lstadd_end(&(a->list_line), ft_lstnew_noalloc(s, 0));
	}
	if (s)
		ft_strdel(&s);
	if (r == -1)
		exit_error(strerror(errno));
}
