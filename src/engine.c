/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 09:42:57 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/18 12:20:18 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_vars(t_wolf *w, int x)
{
	double cam;

	cam = 2 * x / (double)WINDOW_SIZE_X - 1;
	w->rayPosX = w->posX;
	w->rayPosY = w->posY;
	w->mapY = w->posY;
	w->mapX = w->posX;
	w->rayDir = w->dir - w->planeY * cam;
	w->rayDirX = cos(w->rayDir);
	w->rayDirY = sin(w->rayDir);
	w->dirX = cos(w->dir);
	w->dirY = sin(w->dir);
	w->deltaDistX = sqrt(1 + (w->rayDirY * w->rayDirY)
		/ (w->rayDirX * w->rayDirX));
	w->deltaDistY = sqrt(1 + (w->rayDirX * w->rayDirX)
		/ (w->rayDirY * w->rayDirY));
	w->hit = 0;
}

void	setup_dda(t_wolf *w)
{
	w->stepX = (w->rayDirX < 0) ? -1 : 1;
	w->stepY = (w->rayDirY < 0) ? -1 : 1;
	if (w->rayDirX < 0)
		w->sideDistX = (w->rayPosX - w->mapX) * w->deltaDistX;
	else
		w->sideDistX = (w->mapX + 1.0 - w->rayPosX) * w->deltaDistX;
	if (w->rayDirY < 0)
		w->sideDistY = (w->rayPosY - w->mapY) * w->deltaDistY;
	else
		w->sideDistY = (w->mapY + 1.0 - w->rayPosY) * w->deltaDistY;
}

void	do_dda(t_wolf *w)
{
	while (w->hit == 0)
	{
		w->side = (w->sideDistX < w->sideDistY) ? 0 : 1;
		if (w->sideDistX < w->sideDistY)
		{
			w->sideDistX += w->deltaDistX;
			w->mapX += w->stepX;
		}
		else
		{
			w->sideDistY += w->deltaDistY;
			w->mapY += w->stepY;
		}
		if (w->plot->points[w->mapX][w->mapY] > 0)
			w->hit = 1;
	}
}
