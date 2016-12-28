/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/28 05:11:50 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	display_controls(void)
{
	ft_putendl("CONTROLS:\n\
Movement:\n\
	Arrow Keys\n\
Crouch:\n\
	X\n\
Sprint:\n\
	Z");
}

void	load_textures(t_data *d)
{
	d->w->textures = read_bmp("textures/sheet.bmp", &d->w->tex_info);
	if (!d->w->textures ||
		d->w->tex_info.width * d->w->tex_info.height != 466944)
		ft_error("Bad Texture");
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
