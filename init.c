#include "cub.h"

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
	// init_map2D(game);
	// printf("player %f %f\n", game->player.x, game->player.y);
}
