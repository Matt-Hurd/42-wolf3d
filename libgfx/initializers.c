/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:42:53 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/11 07:35:04 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

void		free_plot(t_data *d)
{
	int y;

	if (!d->w->plot)
		return ;
	y = -1;
	while (++y < d->w->plot->height)
		free(d->w->plot->points[y]);
	free(d->w->plot->points);
	free(d->w->plot);
}

void		free_all(t_data *d)
{
	if (d->w)
	{
		free_plot(d);
		if (d->w->textures)
			free(d->w->textures);
	}
}

t_3d		*ft_make_3d(int x, int y, int z)
{
	t_3d *ret;

	ret = (t_3d *)ft_memalloc(sizeof(t_3d));
	ret->x = x;
	ret->y = y;
	ret->z = z;
	return (ret);
}

t_vertex	*ft_make_vertex(int x, int y, int z)
{
	t_vertex *ret;

	ret = (t_vertex *)ft_memalloc(sizeof(t_vertex));
	ret->local = ft_make_3d(x, y, z);
	ret->world = ft_make_3d(0, 0, 0);
	ret->aligned = ft_make_3d(0, 0, 0);
	return (ret);
}
