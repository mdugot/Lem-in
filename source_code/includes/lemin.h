/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 13:00:30 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/07 19:52:56 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define WL ah->waiting_line

typedef enum		e_special
{
	NOT_SPECIAL = 0, S_START = 1, S_END = 2
}					t_special;

typedef enum		e_type_room
{
	R_BEGIN, R_END, R_NORMAL, R_FIRST
}					t_type_room;

typedef struct		s_coor
{
	int				x;
	int				y;
}					t_coor;

typedef struct		s_room
{
	char			*name;
	t_type_room		type;
	int				occupy;
	int				distance;
	int				distance_path;
	int				path;
	int				path_id;
	int				construction_id;
	int				x;
	int				y;
	t_list			*linked_room;
}					t_room;

typedef struct		s_waiting_line
{
	int				size;
	t_room			*room;
}					t_waiting_line;

typedef struct		s_anthill
{
	t_list			*list_line;
	int				number_ants;
	int				finish_ants;
	int				last_departure_id;
	int				number_room;
	t_room			*begin_room;
	t_room			*end_room;
	int				nwl;
	t_waiting_line	*waiting_line;
	t_list			*list_room;
	char			turn_begin;
}					t_anthill;

void				*secure_alloc(size_t size);
void				exit_error(char *str);
void				read_anthill(int fd, t_anthill *anthill);
void				add_tube(t_anthill *anthill, char *s1, char *s2);
void				add_room(t_anthill *ah, t_coor c, char *n, t_type_room t);
void				print_overview(t_list *elem);
void				overview(t_anthill *ah);
t_type_room			special_command(t_anthill *ah, t_special special);
void				build_path(t_list *elem, int id);
void				one_turn(t_anthill *ah);
void				add_waiting_line(t_anthill *ah);
void				add_waiting_ants(t_anthill *ah);
int					open_path(t_list *elem, int d, int id);
void				sort_link(t_list *elem);

#endif
