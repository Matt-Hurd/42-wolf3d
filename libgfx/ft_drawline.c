/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:48:59 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/18 10:26:58 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"




#include <stdio.h>


static int		find_sheet(t_data *d, int z)
{
	int ret;

	if (z == 1)
		ret = (0);
	else if (z == 2)
		ret = -220416;
	else if (z == 3)
		ret = -368256;
	else if (z == 4)
		ret = -884352;
	else if (z == 5)
		ret = -1179648;
	else
		ret = 0;
	if (d->w->side)
		ret += 64 * 3;
	return (ret);
}

static unsigned char	*get_color(t_data *d, t_3d p, float height, int start)
{
	double	wallX;
	int		texWidth;
	int		y;
	int		texX;

	texWidth = d->w->tex_info.width / 6;
	if (d->w->side == 0)
		wallX = d->w->rayPosY + d->w->perpWallDist * d->w->rayDirY;
	else
		wallX = d->w->rayPosX + d->w->perpWallDist * d->w->rayDirX;
	wallX -= floor(wallX);

	texX = (int)(wallX * (double)texWidth);
	if (d->w->side == 0 && d->w->rayDirX > 0)
		texX = texWidth - texX - 1;
	if (d->w->side == 1 && d->w->rayDirY < 0)
		texX = texWidth - texX - 1;

	y = d->w->tex_info.height - ((p.y - start) / height * 64);
	return (d->w->textures + ((texX + y * d->w->tex_info.width) * 3) + find_sheet(d, p.z));
}

static void			draw_point(t_data *d, t_3d p, float height, int start)
{
	int				i;
	unsigned char	*color;
	float			darken;

	i = (p.x * 4) + (p.y * d->s_line);
	if (p.z < 255)
	{
		color = get_color(d, p, height, start);
		darken = MAX(0, MIN(1, height / WINDOW_SIZE_Y - 0.05));
	}
	else
	{
		darken = MAX(0, MIN(1, 1 - (WINDOW_SIZE_Y - p.y) /
			(float)WINDOW_SIZE_Y * 1.3));
		d->pixel_img[i] = (p.z == 255) ? 0x30 * darken : 0;
		d->pixel_img[++i] = (p.z == 255) ? 0x30 * darken : 0;
		d->pixel_img[++i] = (p.z == 255) ? 0x30 * darken: 0;
		return ;
	}
	if (p.x > 0 && p.y > 0 && p.x < WINDOW_SIZE_X && p.y < WINDOW_SIZE_Y)
	{
		d->pixel_img[i] = (color[0]) * darken;
		d->pixel_img[++i] = (color[1]) * darken;
		d->pixel_img[++i] = (color[2]) * darken;
	}
}

void				ft_3d_draw_vert(t_data *d, int x, int y, int height)
{
	int i;
	t_3d point;

	i = -1;
	point.x = x;
	while (++i < WINDOW_SIZE_Y)
	{
		point.y = i;
		if (i < y)
			point.z = 256;
		else if (i < y + height)
			point.z = d->w->plot->points[d->w->mapX][d->w->mapY];
		else
			point.z = 255;
		draw_point(d, point, height, y);
	}
}
