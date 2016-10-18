/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:06:16 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/18 12:20:36 by mhurd            ###   ########.fr       */
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

# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78

# define KEY_ROT_X_U 86
# define KEY_ROT_X_D 83
# define KEY_ROT_Y_U 87
# define KEY_ROT_Y_D 84
# define KEY_ROT_Z_U 88
# define KEY_ROT_Z_D 85

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
#endif
