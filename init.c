#include "cub.h"

int	init_minimap(t_game *game)
{
	game->map2D.scale = ft_min(
			(int)((C) / game->map_x),
			(int)((D) / game->map_y));
	game->map2D.player.x = game->player.x / SCALE * game->map2D.scale
		+ game->map2D.scale / 2;
	game->map2D.player.y = game->player.y / SCALE * game->map2D.scale
		+ game->map2D.scale / 2;
	game->map2D.player.direction = game->player.direction;
	game->map2D.shift_x = (C - game->map_x * game->map2D.scale) / 2;
	game->map2D.shift_y = (D - game->map_y * game->map2D.scale) / 2;
	game->map2D.wall_color = new_color(200, 200, 200);
	game->map2D.ray_color = new_color(150, 150, 0);
	game->map2D.image.img = NULL;
	game->map2D.image.img = mlx_new_image(game->mlx, C, D);
	if (!game->map2D.image.img)
		return (perror("mlx_image"), 0);
	game->map2D.image.addr = mlx_get_data_addr(
			game->map2D.image.img,
			&game->map2D.image.bpp,
			&game->map2D.image.line_size,
			&game->map2D.image.endian);
	printf("2D-scale %d\n", game->map2D.scale);
	printf("x %.1f   y %.1f\n", game->map2D.player.x, game->map2D.player.y);
	return (1);
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
	game->image.img = mlx_new_image(game->mlx, A, B);
	if (!game->image.img)
		return (perror("mlx_image"), 0);
	game->image.addr = mlx_get_data_addr(
			game->image.img,
			&game->image.bpp,
			&game->image.line_size,
			&game->image.endian);
	game->minimap_on = 0;
	return (1);
}
