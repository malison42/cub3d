#include "../cub.h"

void	draw_font(t_game *game)
{
	int x;
	int y;
	
	y = 0;
	while(y < D)
	{
		x = 0;
		while (x < C)
		{
			put_pixel(&game->map2D.image, x, y, 0);
			++x;
		}
		++y;
	}
}

void	draw_walls(t_game *game)
{
	int	x;
	int	y;
	int	pix;

	pix = game->map2D.scale;
	x = 0;
	while (x < C && x / pix < game->map_x)
	{
		y = 0;
		while (y < D && y / pix < game->map_y)
		{
			if (game->map[y / pix][x / pix] == '1')
			{
				put_pixel(&game->map2D.image,
					x + game->map2D.shift_x,
					y + game->map2D.shift_y,
					create_color(game->map2D.wall_color));
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
	a = new_point(game->player.x * game->map2D.scale,
			game->player.y * game->map2D.scale);
	ray = game->player.direction - M_PI / 6;
	while (ray < game->player.direction + M_PI / 6)
	{
		collision = find_collision(game, ray);
		b = new_point(collision.x * game->map2D.scale,
				collision.y * game->map2D.scale);
		line(a, b, game);
		ray += M_PI_4 / RAYS;
	}
}

void	draw_minimap(t_game *game)
{
	draw_font(game);
	draw_walls(game);
	draw_fow(game);
}
