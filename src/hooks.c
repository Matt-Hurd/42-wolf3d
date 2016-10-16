/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 01:12:45 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/15 23:45:33 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static	void	key_hook_movement(int keycode, t_wolf *w)
{
	if (keycode == KEY_UP)
	{
      if(!w->plot->points[(int)(w->posX + cos(w->dir))][(int)w->posY])
      	w->posX += cos(w->dir) * w->moveSpeed;
      if(!w->plot->points[(int)w->posX][(int)(w->posY + w->dirY)])
      	w->posY += w->dirY * w->moveSpeed;
	}
	else if (keycode == KEY_DOWN)
	{		
      if(!w->plot->points[(int)(w->posX - cos(w->dir))][(int)w->posY])
      	w->posX -= cos(w->dir) * w->moveSpeed;
      if(!w->plot->points[(int)w->posX][(int)(w->posY - w->dirY)])
      	w->posY -= w->dirY * w->moveSpeed;
	}
	else if (keycode == KEY_LEFT)
	{
		w->dir += w->rotSpeed;
	}
	else if (keycode == KEY_RIGHT)
	{
		w->dir -= w->rotSpeed;
	}
}

int				key_hook(int keycode, t_data *d)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	key_hook_movement(keycode, d->w);
	draw_reload(d, d->w);
	return (0);
}