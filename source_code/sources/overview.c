/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 14:31:47 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/07 19:52:58 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_overview(t_list *elem)
{
	if (elem == NULL)
		return ;
	ft_printf("%s\n", (char*)elem->content);
	print_overview(elem->next);
}

void	find_begin_and_end(t_anthill *ah, t_list *elem, int begin, int end)
{
	t_room *room;

	if (elem == NULL)
		return ;
	room = (t_room*)elem->content;
	if (room->type == R_BEGIN && begin)
		exit_error("Anthill can not have more than one start-room");
	else if (room->type == R_BEGIN)
	{
		ah->begin_room = room;
		begin = 1;
	}
	else if (room->type == R_END && end)
		exit_error("Anthill can not have more than one end-room");
	else if (room->type == R_END)
	{
		ah->end_room = room;
		end = 1;
	}
	find_begin_and_end(ah, elem->next, begin, end);
}

void	calculate_distance(t_list *elem, int d)
{
	t_room	*room;

	if (elem == NULL)
		return ;
	room = (t_room*)elem->content;
	if (room->distance == -1 || d < room->distance)
	{
		room->distance = d;
		if (room->type != R_BEGIN)
			calculate_distance(room->linked_room, d + 1);
	}
	calculate_distance(elem->next, d);
}

void	overview(t_anthill *ah)
{
	find_begin_and_end(ah, ah->list_room, 0, 0);
	if (ah->begin_room == NULL)
		exit_error("The anthill needs a start-room");
	if (ah->end_room == NULL)
		exit_error("The anthill needs an end-room");
	if (ah->end_room == ah->begin_room)
		exit_error("The start-room and the end-room can not be the same room");
	ah->end_room->distance = 0;
	calculate_distance(ah->end_room->linked_room, 1);
	if (ah->begin_room->distance == -1)
		exit_error("The start-room is not linked with the end-room");
	sort_link(ah->list_room);
	build_path(ah->begin_room->linked_room, 1);
	add_waiting_line(ah);
	add_waiting_ants(ah);
}
