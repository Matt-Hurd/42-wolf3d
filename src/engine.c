/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:44:01 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/28 05:19:14 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_vars(t_wolf *w, int x)
{
	double cam;

	cam = 2 * x / (double)WINDOW_SIZE_X - 1;
	w->rayposx = w->posx;
	w->rayposy = w->posy;
	w->mapy = w->posy;
	w->mapx = w->posx;
	w->raydir = w->dir - 0.33 * cam;
	w->raydirx = cos(w->raydir);
	w->raydiry = sin(w->raydir);
	w->dirx = cos(w->dir);
	w->diry = sin(w->dir);
	w->deltadistx = sqrt(1 + (w->raydiry * w->raydiry)
		/ (w->raydirx * w->raydirx));
	w->deltadisty = sqrt(1 + (w->raydirx * w->raydirx)
		/ (w->raydiry * w->raydiry));
	w->hit = 0;
}

void	setup_dda(t_wolf *w)
{
	w->stepx = (w->raydirx < 0) ? -1 : 1;
	w->stepy = (w->raydiry < 0) ? -1 : 1;
	if (w->raydirx < 0)
		w->sidedistx = (w->rayposx - w->mapx) * w->deltadistx;
	else
		w->sidedistx = (w->mapx + 1.0 - w->rayposx) * w->deltadistx;
	if (w->raydiry < 0)
		w->sidedisty = (w->rayposy - w->mapy) * w->deltadisty;
	else
		w->sidedisty = (w->mapy + 1.0 - w->rayposy) * w->deltadisty;
}

void	do_dda(t_wolf *w)
{
	while (w->hit == 0)
	{
		w->side = (w->sidedistx < w->sidedisty) ? 0 : 1;
		if (w->sidedistx < w->sidedisty)
		{
			w->sidedistx += w->deltadistx;
			w->mapx += w->stepx;
		}
		else
		{
			w->sidedisty += w->deltadisty;
			w->mapy += w->stepy;
		}
		if (w->mapy >= 0 && w->mapy < w->plot->width - 1
			&& w->mapx >= 0 && w->mapx < w->plot->height)
		{
			if (w->plot->points[w->mapx][w->mapy] > 0)
				w->hit = 1;
		}
		else
			w->hit = 1;
	}
}
