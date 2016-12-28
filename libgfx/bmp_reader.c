/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:42:46 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/28 04:57:40 by mhurd            ###   ########.fr       */
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
	if (f <= 0)
		return (0);
	fread(info, sizeof(unsigned char), 2, f);
	if (info[0] != 0x42 || info[1] != 0x4D)
		return (0);
	fread(info + 2, sizeof(unsigned char), 52, f);
	f_info->width = *(int*)&info[18];
	f_info->height = *(int*)&info[22];
	size = 3 * f_info->width * f_info->height;
	data = (unsigned char *)ft_memalloc(size);
	fread(data, 1, size, f);
	fclose(f);
	return (data);
}
