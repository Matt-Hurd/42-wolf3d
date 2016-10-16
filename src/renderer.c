/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 04:47:42 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/15 23:51:49 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
void	draw_map(t_data *d, t_wolf *w)
{
	int x;

	x = -1;
	while (++x < WINDOW_SIZE_X)
	{
		init_vars(w, x);
		setup_dda(w);
		do_dda(w);
		if (w->side == 0)
			w->perpWallDist = (w->mapX - w->rayPosX + (1 - w->stepX) / 2) / w->rayDirX;
		else
			w->perpWallDist = (w->mapY - w->rayPosY + (1 - w->stepY) / 2) / w->rayDirY;

		int lineHeight = (int)(WINDOW_SIZE_Y / w->perpWallDist);
		int drawStart = -lineHeight / 2 + WINDOW_SIZE_Y / 2;
		ft_3d_draw_vert(d, x, drawStart, lineHeight);
		w->oldTime = w->time;
		w->time = clock();
		// double frameTime = (double)(w->time - w->oldTime) / 100;
		w->moveSpeed = .25;
		w->rotSpeed = .15;
	}
}

void	draw_reload(t_data *d, t_wolf *w)
{
	d->img = mlx_new_image(d->mlx, WINDOW_SIZE_X + 100, WINDOW_SIZE_Y + 100);
	d->pixel_img = mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
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
	w->posX = 22;
	w->posY = 12;
	w->dir = M_PI;
	w->planeX = 0;
	w->planeY = 0.33;
	load_textures(d);
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "Wolf3D");
	mlx_expose_hook(d->win, expose_hook, d);
	mlx_hook(d->win, 2, 3, key_hook, d);
	mlx_hook(d->win, 17, 0, ft_red, d);
    mlx_loop(d->mlx);
}