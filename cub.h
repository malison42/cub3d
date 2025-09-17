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

# define A 1800
# define B 1600
//# define SHIFT 2

//relief height
// # define H_BLUE 5
// # define H_WHITE 10
// # define H_GREEN 20
// # define H_YELLOW 50
// # define H_ORANGE 100
// # define H_RED 150

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

// typedef struct s_point
// {
// 	double	x;
// 	double	y;
// 	double	z;
// 	double	ground;
// 	t_color	color[2];
// }	t_point;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
}	t_image;

typedef struct s_textures
{
	int		north;
	int		south;
	int		west;
	int		east;
	t_color	floor;
	t_color	ceiling;
}	t_textures;


//parsing
int		parse_map(char *filepath);
void	free_tokens(char **tokens);
char	**parse_tokens(int fd);
int		parse_wall(char ***lines, char	*orientation);
t_color	parse_color(char ***lines, char *surface);
int		parse_textures(int fd, t_textures *tex);

#endif
