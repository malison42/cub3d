#include "cub.h"

int	close_win(void)
{
	exit(0);
}

void	walk(t_game *game, int sign, int axis)
{
	double	x;
	double	y;

	if (axis == 1)
	{
		x = game->player.x + sign * cos(game->player.direction) * 2;
		y = game->player.y + sign * sin(game->player.direction) * 2;
	}
	else
	{
		x = game->player.x - sign * sin(game->player.direction) * 2;
		y = game->player.y + sign * cos(game->player.direction) * 2;
	}
	if (game->map[(int)(y / SCALE)][(int)(x / SCALE)] != '1')
	{
		game->player.x = x;
		game->player.y = y;
	}
}

int	key_hook(int key, t_game *game)
{
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
	else
		printf("key %d\n", key);
	// print_2D_map(game);
	draw_image(game);
	return (0);
}
