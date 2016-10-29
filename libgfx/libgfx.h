/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgfx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:42:11 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/29 10:40:05 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGFX_H
# define LIBGFX_H
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <string.h>
# define ABS(x) ((x > 0) ? x : x * -1)
# define WINDOW_SIZE_X 1600
# define WINDOW_SIZE_Y 1200

typedef struct	s_2d
{
	short	x;
	short	y;
}				t_2d;

typedef struct	s_3d
{
	float	x;
	float	y;
	float	z;
}				t_3d;

typedef struct	s_vertex
{
	t_3d	*local;
	t_3d	*world;
	t_3d	*aligned;
}				t_vertex;

typedef struct	s_plot
{
	int		**points;
	int		width;
	int		height;
}				t_plot;

typedef struct	s_bmp_info
{
	unsigned long	width;
	unsigned long	height;
}				t_bmp_info;

typedef struct	s_wolf
{
	float			posx;
	float			posy;
	clock_t			time;
	clock_t			oldtime;
	double			rayposx;
	double			rayposy;
	double			raydir;
	double			raydirx;
	double			raydiry;
	double			dirx;
	double			diry;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	double			movespeed;
	double			rotspeed;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				mapy;
	int				mapx;
	int				lineheight;
	float			dir;
	t_plot			*plot;
	unsigned char	*textures;
	t_bmp_info		tex_info;
}				t_wolf;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*pixel_img;
	int		bpp;
	int		s_line;
	int		ed;
	t_plot	*plot;
	float	zr;
	float	scale;
	t_wolf	*w;
}				t_data;

void			ft_mat_copy(float source[4][4], float dest[4][4]);
void			ft_mat_mult(float m1[4][4], float m2[4][4], float d[4][4]);
void			ft_vec_mult_mat(t_3d *s, float mat[4][4], t_3d *d);
float			ft_cos(int x);
float			ft_sin(int x);
void			ft_tr_translate(float m[4][4], float tx, float ty, float tz);
void			ft_tr_scale(float matrix[4][4], float sx, float sy, float sz);
void			ft_tr_rotate(float matrix[4][4], float ax, float ay, float az);
void			ft_make_identity_matrix(float matrix[4][4]);
void			ft_3d_draw_vert(t_data *d, int x, int y, int height);
t_3d			*ft_make_3d(int x, int y, int z);
t_vertex		*ft_make_vertex(int x, int y, int z);
unsigned char	*read_bmp(char *filename, t_bmp_info *info);
#endif
