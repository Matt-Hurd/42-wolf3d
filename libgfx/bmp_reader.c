/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 16:20:01 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/08 14:31:41 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

unsigned char	*read_bmp(char *filename, t_bmp_info *f_info)
{
	unsigned char	*data;
	FILE			*f;
	unsigned char	info[54];
	unsigned int	size;

	f = fopen(filename, "rb");
	fread(info, sizeof(unsigned char), 54, f);
	f_info->width = *(int*)&info[18];
	f_info->height = *(int*)&info[22];
	size = 3 * f_info->width * f_info->height;
	data = (unsigned char *)ft_memalloc(size);
	fread(data, 1, size, f);
	fclose(f);
	return (data);
}
