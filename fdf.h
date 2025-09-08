/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:10:14 by tskubits          #+#    #+#             */
/*   Updated: 2025/04/21 13:10:16 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# include "mlx.h"
# include "libft.h"

# ifdef DARWIN
#  include "keys_macos.h"
# else
#  include "keys_linux.h"
# endif

# define A 1800
# define B 1600
# define SHIFT 2

//relief height
# define H_BLUE 5
# define H_WHITE 10
# define H_GREEN 20
# define H_YELLOW 50
# define H_ORANGE 100
# define H_RED 150

//messages
# define MESSAGE_WRONG_ARGS "Wrong number of arguments"
# define MESSAGE_WRONG_FILE_TYPE "Wrong type of file"
# define MESSAGE_WRONG_FILE "File error"
# define MESSAGE_MALLOC "Unable to allocate memory"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	ground;
	t_color	color[2];
}	t_point;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
}	t_image;

typedef struct s_model
{
	void		*mlx;
	void		*win;
	char		*name;
	t_image		image;
	int			map_x;
	int			map_y;
	t_point		**p;
	double		pix;
	t_point		middle;
	int			ptype;
	int			color;
}	t_model;

//parse_map
void			parse_map(char *filepath, t_model *model);

//point
t_point			new_point(double x, double y, double z, t_color color);
void			rotate_x(t_point *a, double angle);
void			rotate_y(t_point *a, double angle);
void			rotate_z(t_point *a, double angle);

//projection
void			create_image(t_model *model);
void			rescale_points(t_model *model);
void			rescale_parallel(t_model *model);

//lines
void			line(t_point a, t_point b, t_image *image, int col);

//color
t_color			new_color(int r, int g, int b);
unsigned int	create_color(t_color color);
t_color			parse_color(char *value);
t_color			default_color(double z);

//hooks
int				key_hook(int key, t_model *model);
int				mouse_hook(int key, int x, int y, t_model *model);
void			reset_image(t_model *model, int command,
					void (*f)(t_model *, int, int));
void			change_scheme(t_model *model);
int				close_win(t_model *model);

//motion
void			translate(t_model *model, int command, int it);
void			altitude(t_model *model, int command, int it);
void			zoom(t_model *model, int command, int it);
void			rotation(t_model *model, int command, int it);

//image
void			instructions(t_model *model);
void			exit_error(const char *message, t_model *model);
void			start_model(t_model *model, char *argv);
void			init_model(t_model *model);
void			clear_model(t_model *model);

#endif
