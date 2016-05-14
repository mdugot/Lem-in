/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:04:35 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/07 19:55:53 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		continue_path(t_room *room, int d, int id)
{
	t_list	*tmp;
	t_room	*tmp_room;
	int		r;

	tmp = room->linked_room;
	room->construction_id = id;
	while (tmp)
	{
		tmp_room = (t_room*)tmp->content;
		if (tmp_room->type != R_BEGIN
			&& tmp_room->construction_id != id
			&& tmp_room->distance != -1
			&& !(tmp_room->type == R_FIRST && d >= 0))
		{
			if ((r = open_path(tmp, d + 1, id)) != -1)
			{
				room->path = d;
				room->path_id = id;
				return (r);
			}
		}
		tmp = tmp->next;
	}
	return (-1);
}

int		open_path(t_list *elem, int d, int id)
{
	t_room *room;

	room = (t_room*)elem->content;
	if (room->type == R_END || room->distance < 0)
		return (d);
	if (room->distance == -1)
		return (-1);
	if (room->path_id != -1)
		return (-1);
	return (continue_path(room, d, id));
}

void	build_path(t_list *elem, int id)
{
	t_room *first;

	if (elem == NULL)
		return ;
	first = (t_room*)elem->content;
	first->distance_path = open_path(elem, 0, id);
	build_path(elem->next, id + 1);
}
