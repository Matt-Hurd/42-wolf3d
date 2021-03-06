/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:44:10 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/28 05:23:35 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_map(t_data *d, t_wolf *w)
{
	int x;
	int lineheight;
	int drawstart;

	x = -1;
	while (++x < WINDOW_SIZE_X)
	{
		init_vars(w, x);
		setup_dda(w);
		do_dda(w);
		if (w->side == 0)
			w->perpwalldist = (w->mapx - w->rayposx +
				(1 - w->stepx) / 2) / w->raydirx;
		else
			w->perpwalldist = (w->mapy - w->rayposy +
				(1 - w->stepy) / 2) / w->raydiry;
		lineheight = (int)(WINDOW_SIZE_Y / w->perpwalldist);
		drawstart = -lineheight / 2 + WINDOW_SIZE_Y / 2 - (WINDOW_SIZE_Y *
			0.1 * w->crouch) + w->height * 30 / w->perpwalldist;
		ft_3d_draw_vert(d, x, drawstart, lineheight);
	}
	w->oldtime = w->currenttime;
	w->currenttime = clock();
	w->ms = (w->currenttime - w->oldtime) / 20000 * .04 * d->w->sprint;
	w->rotspeed = (w->currenttime - w->oldtime) / 20000 * .025;
}

void	draw_reload(t_data *d, t_wolf *w)
{
	d->img = mlx_new_image(d->mlx, WINDOW_SIZE_X + 100, WINDOW_SIZE_Y + 100);
	d->pixel_img = mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	if (w->jumpspeed > -1)
	{
		w->jumpspeed -= 0.05;
		w->height = MAX(1, w->height + w->jumpspeed);
	}
	draw_map(d, w);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	mlx_destroy_image(d->mlx, d->img);
}

int		expose_hook(t_data *d)
{
	draw_reload(d, d->w);
	return (0);
}

int		ft_red(t_data *d)
{
	mlx_destroy_window(d->mlx, d->win);
	exit(0);
}

void	draw_everything(t_data *d, t_wolf *w)
{
	w->posx = 5.5;
	w->posy = 5.5;
	w->sprint = 1;
	w->dir = M_PI;
	load_textures(d);
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "Wolf3D");
	mlx_expose_hook(d->win, expose_hook, d);
	mlx_hook(d->win, 2, 0, key_pressed, d);
	mlx_hook(d->win, 3, 0, key_released, w);
	mlx_hook(d->win, 17, 0, ft_red, d);
	mlx_loop_hook(d->mlx, main_hook, d);
	mlx_loop(d->mlx);
}
