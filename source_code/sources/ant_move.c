/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 16:24:35 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/07 18:46:57 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*find_destination(t_room *actual, t_list *elem, t_anthill *ah)
{
	t_room *room;

	room = (t_room*)elem->content;
	if (room->type == R_END ||
		(room->path > actual->path && room->path_id == actual->path_id))
	{
		return (room);
	}
	else
	{
		return (find_destination(actual, elem->next, ah));
	}
}

void	move_ant(t_anthill *ah, t_room *room, int ant)
{
	t_room *next;

	if (room->type != R_END)
	{
		next = find_destination(room, room->linked_room, ah);
		move_ant(ah, next, room->occupy);
	}
	if (room->type == R_END && ant > 0)
		ah->finish_ants += 1;
	room->occupy = ant;
	if (ant > 0)
	{
		if (ah->turn_begin)
		{
			ft_printf("L%d-%s", ant, room->name);
			ah->turn_begin = 0;
		}
		else
			ft_printf(" L%d-%s", ant, room->name);
	}
}

void	one_turn(t_anthill *ah)
{
	int	i;

	i = 0;
	ah->turn_begin = 1;
	while (i < ah->nwl)
	{
		if (WL[i].size > 0)
		{
			ah->last_departure_id += 1;
			move_ant(ah, WL[i].room, ah->last_departure_id);
			WL[i].size -= 1;
		}
		else
		{
			move_ant(ah, WL[i].room, 0);
		}
		i++;
	}
	ft_putendl("");
}
