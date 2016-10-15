/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/15 13:50:09 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>

int	main(int ac, char **av)
{
	t_data	*data;
	t_wolf	*wolf;

	if (ac == 2)
	{
		data = (t_data *)ft_memalloc(sizeof(t_data));
		wolf = (t_wolf *)ft_memalloc(sizeof(t_wolf));
		if (!data || !wolf)
			ft_error("Malloc Error");
		data->w = wolf;
		wolf->plot = parse_file(av[1]);
		draw_everything(data, wolf);
	}
	return (0);
}
