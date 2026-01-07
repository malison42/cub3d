#include "cub.h"


t_walls_array	*create_pix_array(t_game *game, int scale)
{
	int				i;
	t_walls_array	*walls;

	walls = malloc(sizeof(t_walls_array));
	if (!walls)
		return (NULL);
	walls->x_size = game->map_x * scale;
	walls->y_size = game->map_y * scale;
	walls->pix = malloc(sizeof(char *) * walls->y_size);
	if (!walls->pix)
		return (free(walls), NULL);
	i = -1;
	while (++i < walls->y_size)
	{
		walls->pix[i] = malloc(walls->x_size);
		if (!walls->pix[i])
		{
			while (i-- > 0)
				free(walls->pix[i]);
			return (free(walls->pix), free(walls), NULL);
		}
		ft_bzero(walls->pix[i], walls->x_size);
	}
	return (walls);
}

void	fill_walls_array(t_game *game, t_walls_array *walls, int scale)
{
	int	i;
	int	j;

	printf("scale %d, x %d, y %d\n", scale, walls->x_size, walls->y_size);
	i = 0;
	while (i < walls->y_size)
	{
		j = 0;
		while (j < walls->x_size)
		{
			if (game->map[i / scale][j / scale] == '1')
				walls->pix[i][j] = 1;
			else
				walls->pix[i][j] = 0;
			++j;
		}
		++i;
	}
	printf("finish %d\n", scale);
}

void	init_walls(t_game *game)
{
	game->walls = create_pix_array(game, SCALE);
	if (!game->walls) {} // handle error
	game->map2D.walls = create_pix_array(game, game->map2D.scale);
	if (!game->map2D.walls) {} // handle error
	fill_walls_array(game, game->walls, SCALE);
	fill_walls_array(game, game->map2D.walls, game->map2D.scale);
}

void	init_map2D(t_game *game)
{
	game->map2D.scale = ft_min((int)((C) / game->map_x),
							  (int)((D) / game->map_y));
	game->map2D.player.x = game->player.x / SCALE * game->map2D.scale +
							game->map2D.scale / 2;
	game->map2D.player.y = game->player.y / SCALE * game->map2D.scale +
							game->map2D.scale / 2;
	game->map2D.player.direction = game->player.direction;
	game->map2D.shift_x = (A - game->map_x * game->map2D.scale) / 2;
	game->map2D.shift_y = (B - game->map_y * game->map2D.scale) / 2;
	game->map2D.wall_color = new_color(200, 200, 200);
	game->map2D.ray_color = new_color(150, 150, 0);
	printf("2D-scale %d\n", game->map2D.scale);
	printf("x %.1f   y %.1f\n", game->map2D.player.x, game->map2D.player.y);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, A, B, "GAME");
	game->image.img = NULL;
	init_map2D(game);
	init_walls(game);
}
