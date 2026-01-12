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
# define C A / 5
# define D B / 5
// # define SIDE 20
# define SCALE 64
# define WALL 64
# define COEF 1108
# define RAYS 1280

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

typedef struct s_texture
{
	t_image	image;
	int		width;
	int		height;
}	t_texture;

typedef struct s_textures
{
	t_texture	*north;
	t_texture	*south;
	t_texture	*west;
	t_texture	*east;
	t_color	floor;
	t_color	ceiling;
}	t_textures;

typedef struct s_map2D
{
	int				scale;
	t_color			wall_color;
	t_color			ray_color;
	t_ray			player;
	int				shift_x;
	int 			shift_y;
	t_image			image;
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
	int				minimap_on;
}	t_game;



//parsing
// int		parse_data(char *filepath, t_game *game);
// void	free_tokens(char **tokens);
// char	**parse_tokens(int fd);
// char	***read_lines(int fd);
// int		parse_wall(char ***lines, char	*orientation);
// t_color	parse_color(char *token_config);
// int		parse_textures(int fd, t_textures *tex);

// t_color	new_color(int r, int g, int b);
// char	*get_line(int fd);
int	parse_game_file(t_game *game, char *argv[], int argc);
t_color	new_color(int r, int g, int b);
char	*get_line(int fd);

/*RENDER*/

//game.c
void	draw_game(t_game *game);

//minimap.c
void	draw_minimap(t_game *game);

//rays.c
t_wall	find_collision(t_game *game, double ray);

//rays_utils.c
void    init_collision_structure(t_game *game, t_collision *c);
void    define_surface(t_game *game, t_wall *collision);
double	fdistance(t_wall a, t_ray b);

//pixel.c
int		create_color(t_color color);
void	put_pixel(t_image *img, int x, int y, int color);
t_point	new_point(int x, int y);

//textures.c
t_texture		*create_texture(t_game *game, char *filename);
unsigned int	get_color_from_texture(double x, double y, t_texture *texture);
t_texture		*define_texture(char face, t_textures *text);
void			destroy_texture(t_game *game, t_texture *texture);
double			find_x_for_texture(t_wall *collision);

//lines.c
void	line(t_point a, t_point b, t_game *game);


/*MAIN*/

//main.c
void	draw_image(t_game *game);

//init.c
void	init_minimap(t_game *game);
void	init_game(t_game *game);

//hooks.c
int		close_win(void);
int		key_hook(int key, t_game *game);

#endif
