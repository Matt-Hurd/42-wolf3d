/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:48:59 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/15 13:48:05 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

static unsigned int	get_color(float z)
{
	if (z == 1)
		return (0xFF0000);
	else if (z == 2)
		return (0x00FF00);
	else if (z == 3)
		return (0x0000FF);
	else if (z == 4)
		return (0xFFFFFF);
	else if (z == 255)
		return (0x331F05);
	else if (z == 256)
		return (0x72A6D0);
	else
		return (0x00FFFF);
}

static void			draw_point(t_data *d, int x, int y, int z)
{
	int i;
	int color;

	if (x > 0 && y > 0 && x < WINDOW_SIZE_X && y < WINDOW_SIZE_Y)
	{
		color = get_color(z);
		if (d->w->side && z < 255)
			color /= 2;
		i = (x * 4) + (y * d->s_line);
		d->pixel_img[i] = color;
		d->pixel_img[++i] = color >> 8;
		d->pixel_img[++i] = color >> 16;
	}
}

void				ft_3d_draw_vert(t_data *d, int x, int y, int height)
{
	int i;

	i = -1;
	while (++i < y)
		draw_point(d, x, i, 256);
	while (++i < y + height)
		draw_point(d, x, i, d->w->plot->points[d->w->mapY][d->w->mapX]);
	i--;
	while (++i < WINDOW_SIZE_Y)
		draw_point(d, x, i, 255);
}
