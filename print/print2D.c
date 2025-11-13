#include "../cub.h"

void	init_map2D(t_game *game)
{
	game->map2D.scale = ft_min((int)((A) / game->map_x),
							  (int)((B) / game->map_y));
	game->map2D.player.x = game->player.x / SCALE * game->map2D.scale +
							game->map2D.scale / 2;
	game->map2D.player.y = game->player.y / SCALE * game->map2D.scale +
							game->map2D.scale / 2;
	game->map2D.player.direction = game->player.direction;
	game->map2D.shift_x = (A - game->map_x * game->map2D.scale) / 2;
	game->map2D.shift_y = (B - game->map_y * game->map2D.scale) / 2;
	game->map2D.wall_color = new_color(200, 200, 200);
	game->map2D.ray_color = new_color(150, 150, 0);
	printf("scale %d\n", game->map2D.scale);
	printf("x %.1f   y %.1f\n", game->map2D.player.x, game->map2D.player.y);
}

// void recalculate_player(t_game *game)
// {
// 	game->map2D.player.x = game->player.x / SCALE * game->map2D.scale;
// 	game->map2D.player.y = game->player.y / SCALE * game->map2D.scale;
// 	game->map2D.player.direction = game->player.direction;
// }

void	draw_walls(t_game *game)
{
	int x;
	int y;
	int pix;
	
	x = 0;
	pix = game->map2D.scale;
	while (x < A && x / pix < game->map_x)
	{
		y = 0;
		while (y < B && y / pix < game->map_y)
		{
			if (game->map[y / pix][x / pix] == '1')
			{
				put_pixel(&game->image, x, y, game->map2D.wall_color);
			}
			++y;
		}
		++x;
	}
}

// void	draw_ray(t_game *game, double ray)
// {
// 	double x;
// 	double y;
// 	int pix;

// 	pix = game->map2D.scale;
// 	x = game->map2D.player.x;
// 	y = game->map2D.player.y;
// 	while (x < A && x / pix < game->map_x
// 			&& y < B && y / pix < game->map_y)
// 	{
// 		if (game->map[(int)(y / pix)][(int)(x / pix)] == '1')
// 			break ;
// 		put_pixel(&game->image, (int)x, (int)y, game->map2D.ray_color);
// 		x += cos(ray);
// 		y += sin(ray);
// 	}
// }

void	draw_line_ray(t_game *game, double ray)
{
	t_wall	wall;
	t_point	a;
	t_point	b;

	wall = find_wall(game, ray);
	wall.x = 1.0 * wall.x / SCALE * game->map2D.scale;
	wall.y = 1.0 * wall.y / SCALE * game->map2D.scale;
	a = new_point(game->map2D.player.x, game->map2D.player.y);
	b = new_point(wall.x, wall.y);
	line(a, b, game);
}

void	draw_fow(t_game *game)
{
	double	ray;
	double	step;
	
	(void)ray;
	step = M_PI / 3 / 1440;
	ray = game->map2D.player.direction;
	draw_line_ray(game, game->map2D.player.direction);
	while (ray >= game->map2D.player.direction - M_PI / 6)
	{
		draw_line_ray(game, ray);
		ray -= step;
	}
	ray = game->map2D.player.direction;
	while (ray <= game->map2D.player.direction + M_PI / 6)
	{
		draw_line_ray(game, ray);
		ray += step;
	}
}

void	print_2D_map(t_game *game)
{
	// recalculate_player(game);
	game->map2D.player.x = game->player.x / SCALE * game->map2D.scale;
	game->map2D.player.y = game->player.y / SCALE * game->map2D.scale;
	game->map2D.player.direction = game->player.direction;
	draw_walls(game);
	draw_fow(game);
}
