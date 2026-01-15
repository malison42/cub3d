#include "cub.h"

void	init_minimap(t_game *game)
{
	game->map2D.scale = ft_min((int)((C) / game->map_x),
							  (int)((D) / game->map_y));
	game->map2D.player.x = game->player.x / SCALE * game->map2D.scale +
							game->map2D.scale / 2;
	game->map2D.player.y = game->player.y / SCALE * game->map2D.scale +
							game->map2D.scale / 2;
	game->map2D.player.direction = game->player.direction;
	game->map2D.shift_x = (C - game->map_x * game->map2D.scale) / 2;
	game->map2D.shift_y = (D - game->map_y * game->map2D.scale) / 2;
	game->map2D.wall_color = new_color(200, 200, 200);
	game->map2D.ray_color = new_color(150, 150, 0);
	game->map2D.image.img = NULL;
	printf("2D-scale %d\n", game->map2D.scale);
	printf("x %.1f   y %.1f\n", game->map2D.player.x, game->map2D.player.y);
}

int	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->texture = malloc(sizeof(t_textures));
	if (!game->texture)
		return (perror("malloc"), 0);
	game->texture->side[NORTH] = NULL;
	game->texture->side[SOUTH] = NULL;
	game->texture->side[WEST] = NULL;
	game->texture->side[EAST] = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (perror("mlx_init"), 0);
	game->win = mlx_new_window(game->mlx, A, B, "GAME");
	if (!game->win)
		return (perror("mlx_window_init"), 0);
	game->image.img = NULL;
	game->minimap_on = 0;
	return (1);
}
