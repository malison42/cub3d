#include "cub.h"

void	free_map_array(char **map, int rows_to_free);

void	free_game(t_game *game)
{
	if (game->map)
		free_map_array(game->map, game->map_y);
	if (game->texture)
	{
		if (game->texture->side[NORTH])
			destroy_texture(game, game->texture->side[NORTH]);
		if (game->texture->side[SOUTH])
			destroy_texture(game, game->texture->side[SOUTH]);
		if (game->texture->side[WEST])
			destroy_texture(game, game->texture->side[WEST]);
		if (game->texture->side[EAST])
			destroy_texture(game, game->texture->side[EAST]);
		free(game->texture);
	}
	if (game->image.img)
		mlx_destroy_image(game->mlx, game->image.img);
	if (game->map2D.image.img)
		mlx_destroy_image(game->mlx, game->map2D.image.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
}
