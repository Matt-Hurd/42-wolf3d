/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:26:41 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/15 20:16:25 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	list_to_array(t_plot *plot, t_list *rows)
{
	int		y;
	int		x;
	char	**buff;
	int		z;

	plot->points = (int **)ft_memalloc(sizeof(int *) * plot->height);
	y = -1;
	while (++y < plot->height)
	{
		plot->points[y] = (int	*)ft_memalloc(sizeof(int) * plot->width);
		buff = ft_strsplit(rows->content, ' ');
		x = -1;
		while (++x < plot->width)
		{
			z = ft_atoi(buff[x]);
			plot->points[y][x] = z;
		}
		rows = rows->next;
	}
}

t_plot	*parse_file(char *filename)
{
	char	*buff;
	int		result;
	int		fd;
	t_list	*list;
	t_plot	*plot;

	plot = (t_plot *)ft_memalloc(sizeof(t_plot));
	plot->width = -1;
	plot->height = 0;
	fd = open(filename, O_RDONLY);
	list = NULL;
	while ((result = ft_get_next_line(fd, &buff)) > 0)
	{
		if (plot->width == -1)
			plot->width = ft_count_words(buff, 0, ' ');
		if (plot->width != ft_count_words(buff, 0, ' '))
			ft_error("Invalid Map");
		ft_lst_add_back(&list, ft_lstnew(buff, sizeof(char) * (ft_strlen(buff) + 1)));
		(plot->height)++;
	}
	if (result < 0)
		ft_error_unknown();
	list_to_array(plot, list);
	close(fd);
	return (plot);
}



#include <stdio.h>




void	load_textures(t_data *d)
{
	d->w->textures = read_bmp("textures/sheet.bmp", &d->w->tex_info);
}