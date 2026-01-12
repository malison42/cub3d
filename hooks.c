#include "cub.h"

int	close_win(void)
{
	exit(0);
}

// static int	isobstacle(t_game *game, double x, double y)
// {
// 	if (game->map[(int)(y + 0.2)][(int)(x)] == '1')
// 		return (1);
// 	if (game->map[(int)(y - 0.2)][(int)(x)] == '1')
// 		return (1);
// 	if (game->map[(int)(y)][(int)(x + 0.2)] == '1')
// 		return (1);
// 	if (game->map[(int)(y)][(int)(x - 0.2)] == '1')
// 		return (1);
// 	return (0);
// }

void	walk(t_game *game, int sign, int axis)
{
	double	x;
	double	y;

	if (axis == 1)
	{
		x = game->player.x + sign * cos(game->player.direction) / 10;
		y = game->player.y + sign * sin(game->player.direction) / 10;
	}
	else
	{
		x = game->player.x - sign * sin(game->player.direction) / 10;
		y = game->player.y + sign * cos(game->player.direction) / 10;
	}
	if (game->map[(int)(y)][(int)(x)] != '1')
	// if (!isobstacle(game, x, y))
	{
		game->player.x = x;
		game->player.y = y;
	}
}

int	key_hook(int key, t_game *game)
{
	// printf("new key %d\n", key);
	if (key == ESC)
		exit(0);
	else if (key == UP)
		walk(game, +1, 1);
	else if (key == DOWN)
		walk(game, -1, 1);
	else if (key == RIGHT)
		walk(game, +1, 0);
	else if (key == LEFT)
		walk(game, -1, 0);
	else if (key == LEFT_VIEW)
		game->player.direction -= M_PI / 90;
	else if (key == RIGHT_VIEW)
		game->player.direction += M_PI / 90;
	else if (key == MINI_MAP)
		game->minimap_on = (game->minimap_on + 1) % 2;
	else
		printf("key %d\n", key);

	draw_image(game);
	return (0);
}
