/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/15 15:20:10 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	display_controls(void)
{
	ft_putendl("CONTROLS:\n\
Movement:\n\
	Arrow Keys");
}

int		main(int ac, char **av)
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
		display_controls();
		draw_everything(data, wolf);
	}
	else
	{
		ft_putstr("Usage: ");
		ft_putstr(av[0]);
		ft_putendl(" [map_name]");
	}
	return (0);
}
