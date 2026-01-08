#include "../cub.h"

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
			if (game->map2D.walls->pix[y][x] && y % game->map2D.scale)
			{
				put_pixel(&game->image, x, y, game->map2D.wall_color);
			}
			++y;
		}
		++x;
	}
}

t_ray	straight_ray(t_game *game, t_ray dir, t_point step)
{
	t_point	map;

	map.x = game->player.x;
	map.y = game->player.y;
	while (game->map[map.y][map.x] != '1')
	{
		map.y += step.y;
		map.x += step.x;
	}

	t_ray	point;
	if (dir.x == 0)
	{
		point.x = game->player.x;
		point.y = map.y + (step.y < 0);
	}
	else
	{
		point.x = map.x + (step.x < 0);
		point.y = game->player.y;
	}
	return (point);
}

t_ray	inclined_ray(t_game *game, t_ray dir, t_point step)
{
	t_point	map;
	t_ray	delta;
	t_ray	side;

	map.x = game->player.x;
	map.y = game->player.y;
	delta.x = fabs(1 / dir.x);
	delta.y = fabs(1 / dir.y);

	if (step.x < 0)
		side.x = (game->player.x - map.x) * delta.x;
	else
		side.x = (1 - game->player.x + map.x) * delta.x;
	if (step.y < 0)
		side.y = (game->player.y - map.y) * delta.y;
	else
		side.y = (1 - game->player.y + map.y) * delta.y;

	char face = 0;
	while (game->map[map.y][map.x] != '1')
	{
		if (side.x < side.y)
		{
			side.x += delta.x;
			map.x += step.x;
			face = 'X';
		}
		else
		{
			side.y += delta.y;
			map.y += step.y;
			face = 'Y';
		}
	}

	double	t;
	if (face == 'X')
		t = (map.x - game->player.x + (step.x < 0)) / dir.x;
	else
		t = (map.y - game->player.y + (step.y < 0)) / dir.y;

	t_ray	point;
	point.x = game->player.x + dir.x * t;
	point.y = game->player.y + dir.y * t;
	return (point);
}

t_ray	find_collision(t_game *game, double ray)
{
	t_ray	dir;
	t_point	step;
	t_ray	collision;

	dir.x = cos(ray);
	dir.y = sin(ray);
	if (cos(ray) == cos(3 * M_PI_2))
		dir.x = 0;
	if (sin(ray) == sin(M_PI))
		dir.y = 0;
	step.x = (dir.x > 0) - (dir.x < 0);
	step.y = (dir.y > 0) - (dir.y < 0);
	if (dir.x == 0 || dir.y == 0)
		collision = (straight_ray(game, dir, step));
	else
		collision = (inclined_ray(game, dir, step));
	return (collision);
}

void	draw_fow(t_game *game)
{
	double	ray;
	t_ray	collision;
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
	// game->map2D.player = recalculate_point(game, game->player);
	draw_walls(game);
	draw_fow(game);
}
