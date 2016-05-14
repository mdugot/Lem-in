/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:26:46 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/07 19:54:51 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			add_room(t_anthill *ah, t_coor c, char *name, t_type_room t)
{
	t_room new;

	ft_bzero(&new, sizeof(t_room));
	new.x = c.x;
	new.y = c.y;
	new.name = ft_strdup(name);
	new.type = t;
	new.distance = -1;
	new.distance_path = -1;
	new.path = -1;
	new.path_id = -1;
	new.construction_id = -1;
	if (t == R_END)
		new.path = -2;
	ah->number_room += 1;
	ft_lstadd_end(&ah->list_room, ft_lstnew(&new, sizeof(t_room)));
}

t_room			*find_room(t_list *elem, char *name)
{
	t_room	*room;

	if (elem == NULL)
		return (NULL);
	room = elem->content;
	if (ft_strcmp(room->name, name) == 0)
		return (room);
	else
		return (find_room(elem->next, name));
}

int				already_linked(t_room *r1, t_room *r2)
{
	t_list	*tmp;
	t_room	*room;

	tmp = r1->linked_room;
	while (tmp)
	{
		room = (t_room*)tmp->content;
		if (ft_strcmp(r2->name, room->name) == 0)
			return (1);
		tmp = tmp->next;
	}
	tmp = r2->linked_room;
	while (tmp)
	{
		room = (t_room*)tmp->content;
		if (ft_strcmp(r1->name, room->name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void			add_tube(t_anthill *anthill, char *s1, char *s2)
{
	t_room *r1;
	t_room *r2;

	r1 = find_room(anthill->list_room, s1);
	r2 = find_room(anthill->list_room, s2);
	if (!r2 || !r1)
	{
		exit_error("Try to link room that does not exist");
	}
	if (already_linked(r1, r2))
	{
		ft_putendl(s1);
		ft_putendl(s2);
		exit_error("Multiple links between the same two rooms are forbidden");
	}
	ft_lstadd_end(&(r2->linked_room), ft_lstnew_noalloc(r1, sizeof(t_room)));
	ft_lstadd_end(&(r1->linked_room), ft_lstnew_noalloc(r2, sizeof(t_room)));
	if (r1->type == R_BEGIN && r2->type != R_END)
		r2->type = R_FIRST;
	else if (r2->type == R_BEGIN && r1->type != R_END)
		r1->type = R_FIRST;
}

t_type_room		special_command(t_anthill *ah, t_special special)
{
	(void)ah;
	if (special == S_START)
		return (R_BEGIN);
	if (special == S_END)
		return (R_END);
	return (R_NORMAL);
}
