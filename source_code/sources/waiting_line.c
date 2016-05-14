/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:53:16 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/07 15:59:24 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		number_line(t_list *elem)
{
	t_room *room;

	if (elem == NULL)
		return (0);
	room = (t_room*)elem->content;
	if (room->path != -1)
		return (number_line(elem->next) + 1);
	else
		return (number_line(elem->next));
}

void	add_waiting_line(t_anthill *ah)
{
	t_list	*tmp;
	t_room	*room;
	int		i;

	ah->nwl = number_line(ah->begin_room->linked_room);
	ah->waiting_line = secure_alloc(ah->nwl * sizeof(t_waiting_line));
	tmp = ah->begin_room->linked_room;
	i = 0;
	while (tmp)
	{
		room = (t_room*)tmp->content;
		if (room->path != -1)
		{
			ah->waiting_line[i].room = room;
			i++;
		}
		tmp = tmp->next;
	}
}

void	add_waiting_ants(t_anthill *ah)
{
	int i;
	int j;
	int r;
	int	min;

	i = -1;
	while (++i < ah->number_ants)
	{
		j = -1;
		r = 0;
		min = -1;
		while (++j < ah->nwl)
			if (WL[j].size + WL[j].room->distance_path < min || min == -1)
			{
				min = WL[j].size + WL[j].room->distance_path;
				r = j;
			}
		WL[r].size += 1;
	}
}
