/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 01:12:45 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/28 05:14:22 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	do_jump(t_data *d)
{
	if (d->w->height > 1)
		return ;
	d->w->jumpspeed = 1;
	system("afplay sounds/jump2.mp3 &");
}

int		key_pressed(int keycode, t_data *d)
{
	if (keycode == KEY_UP)
		d->w->direction |= 1;
	if (keycode == KEY_DOWN)
		d->w->direction |= 2;
	if (keycode == KEY_LEFT)
		d->w->direction |= 4;
	if (keycode == KEY_RIGHT)
		d->w->direction |= 8;
	if (keycode == KEY_Z)
		d->w->sprint = 2;
	if (keycode == KEY_SPACE)
		do_jump(d);
	else if (keycode == KEY_X)
	{
		d->w->sprint = 0.5;
		d->w->crouch = 1;
	}
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(d->mlx, d->win);
		free_all(d);
		exit(0);
	}
	return (0);
}

int		key_released(int keycode, t_wolf *w)
{
	if (keycode == KEY_UP && w->direction & 1)
		w->direction -= 1;
	if (keycode == KEY_DOWN && w->direction & 2)
		w->direction -= 2;
	if (keycode == KEY_LEFT && w->direction & 4)
		w->direction -= 4;
	if (keycode == KEY_RIGHT && w->direction & 8)
		w->direction -= 8;
	if (keycode == KEY_Z)
		w->sprint = 1;
	if (keycode == KEY_X)
	{
		w->sprint = 1;
		w->crouch = 0;
	}
	return (0);
}

int		main_hook(t_data *d)
{
	t_wolf *w;

	w = d->w;
	if (w->direction & 1)
	{
		if (!w->plot->points[(int)(w->posx + cos(w->dir)
			* w->ms)][(int)w->posy])
			w->posx += cos(w->dir) * w->ms;
		if (!w->plot->points[(int)w->posx][(int)(w->posy + w->diry * w->ms)])
			w->posy += w->diry * w->ms;
	}
	if (w->direction & 2)
	{
		if (!w->plot->points[(int)(w->posx - cos(w->dir)
			* w->ms)][(int)w->posy])
			w->posx -= cos(w->dir) * w->ms;
		if (!w->plot->points[(int)w->posx][(int)(w->posy - w->diry * w->ms)])
			w->posy -= w->diry * w->ms;
	}
	if (w->direction & 4)
		w->dir += w->rotspeed;
	if (w->direction & 8)
		w->dir -= w->rotspeed;
	draw_reload(d, d->w);
	return (0);
}
