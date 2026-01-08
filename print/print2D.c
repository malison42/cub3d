#include "../cub.h"

void	draw_walls(t_game *game)
{
	int x;
	int y;
	int	pix;
	
	pix = game->map2D.scale;
	x = 0;
	while (x < A && x / pix < game->map_x)
	{
		y = 0;
		while (y < B && y / pix < game->map_y)
		{
			if (game->map[y / pix][x / pix] == '1' && y % pix)
			{
				put_pixel(&game->image, x, y, game->map2D.wall_color);
			}
			++y;
		}
		++x;
	}
}


void	draw_fow(t_game *game)
{
	double	ray;
	t_wall	collision;
	t_point	a;
	t_point	b;
	
	(void)ray;
	a = new_point(game->player.x * game->map2D.scale, game->player.y * game->map2D.scale);
	ray = game->player.direction - M_PI / 6;
	while (ray < game->player.direction + M_PI / 6)
	{
		collision = find_collision(game, ray);
		b = new_point(collision.x * game->map2D.scale, collision.y * game->map2D.scale);
		line(a, b, game);
		ray += M_PI_4 / RAYS;
	}
}

void	print_2D_map(t_game *game)
{
	draw_walls(game);
	draw_fow(game);
}
