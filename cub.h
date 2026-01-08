/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <tskubits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:10:14 by tskubits          #+#    #+#             */
/*   Updated: 2025/09/08 13:29:27 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

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

# define A 1280
# define B 800
# define C 1280
# define D 800
// # define SIDE 20
# define SCALE 64
# define WALL 64
# define COEF 277
# define RAYS 640

//messages
// # define MESSAGE_WRONG_ARGS "Wrong number of arguments"
// # define MESSAGE_WRONG_FILE_TYPE "Wrong type of file"
# define MESSAGE_WRONG_FILE "File error"
# define MESSAGE_SCENE_NOT_VALID "Scene is not valid"
// # define MESSAGE_MALLOC "Unable to allocate memory"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_textures
{
	int		north;
	int		south;
	int		west;
	int		east;
	t_color	floor;
	t_color	ceiling;
}	t_textures;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	int		x;
	int 	y;
	double	view;
}	t_player;

typedef struct s_wall
{
	double	x;
	double	y;
	char	face;
}	t_wall;



typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
}	t_image;

typedef struct s_ray
{
	double	x;
	double	y;
	double	direction;
}	t_ray;

typedef struct s_collision
{
	t_ray	dir;
	t_point	step;
	t_point map;
	t_ray	delta;
	t_ray	side;
}	t_collision;

typedef struct s_map2D
{
	int				scale;
	t_color			wall_color;
	t_color			ray_color;
	t_ray			player;
	int				shift_x;
	int 			shift_y;
}	t_map2D;

typedef struct s_game
{
	void 			*mlx;
	void 			*win;
	t_image 		image;
	t_textures		*texture;
	int				map_x;
	int				map_y;
	char			**map;
	t_player		start;
	t_map2D			map2D;
	t_ray			player;
}	t_game;

//parsing
int		parse_data(char *filepath, t_game *game);
void	free_tokens(char **tokens);
char	**parse_tokens(int fd);
char	***read_lines(int fd);
int		parse_wall(char ***lines, char	*orientation);
t_color	parse_color(char ***lines, char *surface);
int		parse_textures(int fd, t_textures *tex);

t_color	new_color(int r, int g, int b);
char	*get_line(int fd);

//pixel
void	put_pixel(t_image *img, int x, int y, t_color color);
int		create_color(t_color color);
void	put_square(t_game *game, int x, int y, t_color color);

t_point	new_point(int x, int y);


//print
void	print_2D_map(t_game *game);
//void	draw_ray(t_game *game, double direction);
void	draw_fow(t_game *game);
void	calculate_small_map(t_game *game);

void	init_map2D(t_game *game);

//hooks
int	close_win(void);
int	key_hook(int key, t_game *game);


void	draw_line(t_game *game, double ray, int pix_x);
void	draw_game(t_game *game);

t_wall	find_wall(t_game *game, double ray);
void	line(t_point a, t_point b, t_game *game);

void	draw_image(t_game *game);

void	init_game(t_game *game);

t_ray recalculate_point(t_game *game, t_ray point);
t_ray	find_wall3(t_game *game, double ray);
t_wall	find_collision(t_game *game, double ray);
double	fdistance(t_wall a, t_ray b);
void    init_collision_structure(t_game *game, t_collision *c);
t_color define_color(char face);
void    define_surface(t_game *game, t_wall *c);


#endif
