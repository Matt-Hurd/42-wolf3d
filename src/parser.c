/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:26:41 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/11 07:39:47 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	valid_map(t_plot *plot)
{
	int x;

	x = -1;
	if (plot->height < 10 || plot->width < 10)
		ft_error("Map Must Be At Least 10x10");
	if (plot->points[5][5])
		ft_error("Starting Point (5, 5) Must Be Clear");
	while (++x < plot->width)
		if (plot->points[0][x] == 0 || plot->points[plot->height - 1][x] == 0)
			return (0);
	x = -1;
	while (++x < plot->height)
		if (plot->points[x][0] == 0 || plot->points[x][plot->width - 1] == 0)
			return (0);
	return (1);
}

static void	free_array(t_list *rows)
{
	t_list *tmp;

	while (rows)
	{
		tmp = rows->next;
		free(rows->content);
		free(rows);
		rows = tmp;
	}
}

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
			if (z < 0)
				ft_error("Negative Block ID");
		}
		ft_free_strsplit(rows->content, buff, ' ');
		rows = rows->next;
	}
	if (!valid_map(plot))
		ft_error("Unclosed Map");
}

void		setup_parser(t_plot *plot, int *fd, char *fn)
{
	plot->width = -1;
	*fd = open(fn, O_RDONLY);
}

t_plot		*parse_file(char *filename)
{
	char	*buff;
	int		result;
	int		fd;
	t_list	*list;
	t_plot	*plot;

	plot = (t_plot *)ft_memalloc(sizeof(t_plot));
	list = NULL;
	setup_parser(plot, &fd, filename);
	while ((result = ft_get_next_line(fd, &buff)) > 0)
	{
		if (plot->width == -1)
			plot->width = ft_count_words(buff, ' ');
		if (plot->width != ft_count_words(buff, ' '))
			ft_error("Invalid Map");
		ft_lst_add_back(&list, ft_lstnew(buff, ft_strlen(buff) + 1));
		(plot->height)++;
		free(buff);
	}
	if (result < 0)
		ft_error_unknown();
	list_to_array(plot, list);
	free_array(list);
	close(fd);
	return (plot);
}
