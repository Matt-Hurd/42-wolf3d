/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:06:16 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/11 06:24:36 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "mlx.h"
# include "libft.h"
# include "libgfx.h"
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>

/*
** KEYS
*/

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_Z	6
# define KEY_X	7

t_plot		*parse_file(char *filename);
void		draw_everything(t_data *d, t_wolf *f);
int			key_hook(int keycode, t_data *d);
void		draw_reload(t_data *d, t_wolf *f);
void		init_vars(t_wolf *w, int x);
void		ft_exit(void);
void		ft_error_unknown(void);
void		ft_error(char *s);
void		setup_dda(t_wolf *w);
void		do_dda(t_wolf *w);
void		load_textures(t_data *d);
int			main_hook(t_data *d);
int			key_released(int keycode, t_wolf *w);
int			key_pressed(int keycode, t_data *d);
#endif
