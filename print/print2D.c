#include "../cub.h"

// void	init_map2D(t_game *game)
// {
// 	game->map2D.scale = ft_min((int)((A) / game->map_x),
// 							  (int)((B) / game->map_y));
// 	game->map2D.player.x = game->player.x / SCALE * game->map2D.scale +
// 							game->map2D.scale / 2;
// 	game->map2D.player.y = game->player.y / SCALE * game->map2D.scale +
// 							game->map2D.scale / 2;
// 	game->map2D.player.direction = game->player.direction;
// 	game->map2D.shift_x = (A - game->map_x * game->map2D.scale) / 2;
// 	game->map2D.shift_y = (B - game->map_y * game->map2D.scale) / 2;
// 	game->map2D.wall_color = new_color(200, 200, 200);
// 	game->map2D.ray_color = new_color(150, 150, 0);
// 	printf("scale %d\n", game->map2D.scale);
// 	printf("x %.1f   y %.1f\n", game->map2D.player.x, game->map2D.player.y);
// }

t_ray recalculate_point(t_game *game, t_ray point)
{
	t_ray	new_point;

	new_point.x = point.x / SCALE * game->map2D.scale;
	new_point.y = point.y / SCALE * game->map2D.scale;
	new_point.direction = game->player.direction;
	// printf("player: x = %f  y = %f\n", game->player.x, game->player.y);
	// printf("2D player: x = %f  y = %f\n", game->map2D.player.x, game->map2D.player.y);
	return (new_point);
}

void	draw_walls(t_game *game)
{
	int x;
	int y;
	
	x = 0;
	while (x < game->map2D.walls->x_size)
	{
		y = 0;
		while (y < game->map2D.walls->y_size)
		{
			if (game->map2D.walls->pix[y][x])
			{
				put_pixel(&game->image, x, y, game->map2D.wall_color);
			}
			++y;
		}
		++x;
	}
}

void	draw_ray(t_game *game, double ray)
{
	double x;
	double y;
//	int x_pix;
//	int y_pix;
	int pix;

	pix = game->map2D.scale;
	x = game->map2D.player.x;
	y = game->map2D.player.y;
	while (x < A && x / pix < game->map_x
			&& y < B && y / pix < game->map_y)
	{
		if (game->map[(int)(y / pix)][(int)(x / pix)] == '1')
			break ;
//				x_pix = x + game->map2D.shift_x;
//				y_pix = y + game->map2D.shift_y;
		put_pixel(&game->image, (int)x, (int)y, game->map2D.ray_color);
		x += cos(ray);
		y += sin(ray);
	}
}

void	draw_line_ray(t_game *game, double ray)
{
	// t_wall	wall;
	t_point	a;
	t_point	b;
	t_ray	collision;
//	t_point c;
	
//	printf("ququ\n");
	// wall = find_wall(game, ray);
//	printf("cross:  %d %d\nplayer: %f %f\n", wall.x, wall.y, game->player.x, game->player.y);
	// wall.x = 1.0 * wall.x / SCALE * game->map2D.scale;
	// wall.y = 1.0 * wall.y / SCALE * game->map2D.scale;
	collision = recalculate_point(game, find_wall3(game, ray));
//	printf("cross:  %d %d\n", wall.x, wall.y);
	a = new_point(game->map2D.player.x, game->map2D.player.y);
//	printf("player: %d %d\n", a.x, a.y);
//	a = new_point(0, 0);
//	printf("ququ\n");
	b = new_point(collision.x, collision.y);
	// printf("a.x %d a.y %d\n b.x %d b.y %d\n", a.x, a.y, b.x, b.y);
	line(a, b, game);
//	printf("ququ\n");
}

void	draw_fow(t_game *game)
{
	double	ray;
	
	(void)ray;
	ray = game->map2D.player.direction - M_PI / 6;
	draw_line_ray(game, game->map2D.player.direction);
	// while (ray < game->map2D.player.direction + M_PI / 6)
	// {
	// 	draw_line_ray(game, ray);
	// 	ray += M_PI_4 / RAYS_2D;
	// }
}

void	print_2D_map(t_game *game)
{
//	init_map2D(game);
	game->map2D.player = recalculate_point(game, game->player);
	draw_walls(game);
//	printf("ququ\n");
	draw_fow(game);
}
