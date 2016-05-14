/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 19:08:16 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/07 21:44:25 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		sort_room_by_distance(void *a1, void *a2)
{
	t_room *r1;
	t_room *r2;

	r1 = (t_room*)a1;
	r2 = (t_room*)a2;
	if (r1->distance == -1 && r2->distance != -1)
		return (1);
	if (r1->distance != -1 && r2->distance == -1)
		return (0);
	if (r2->distance < r1->distance)
		return (1);
	return (0);
}

void	sort_link(t_list *elem)
{
	t_room *room;

	if (elem == NULL)
		return ;
	room = (t_room*)elem->content;
	ft_lstsort(&room->linked_room, sort_room_by_distance);
	sort_link(elem->next);
}
