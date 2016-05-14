/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 13:02:55 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/07 14:44:42 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	main(void)
{
	t_anthill	*anthill;

	anthill = secure_alloc(sizeof(t_anthill));
	read_anthill(0, anthill);
	print_overview(anthill->list_line);
	overview(anthill);
	ft_putendl("");
	while (anthill->finish_ants < anthill->number_ants)
	{
		one_turn(anthill);
	}
	return (0);
}
