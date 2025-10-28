#include "../cub.h"

t_wall	check_wall(t_game *game, t_point p, t_point dir)
{
	t_wall	wall;

	wall.x = p.x;
	wall.y = p.y;
	if (dir.x && game->map[(p.y) / SCALE][(p.x + 5 * dir.x) / SCALE] == '1')
	{
		if (dir.x > 0)
			wall.color = new_color(195, 205, 250); // WEST
		else
			wall.color = new_color(195, 250, 205); // EAST
	}
	else if (dir.y && game->map[(p.y + 5 * dir.y) / SCALE][(p.x) / SCALE] == '1')
	{
		if (dir.y > 0)
			wall.color = new_color(250, 250, 190); // NORTH
		else
			wall.color = new_color(250, 200, 190); // SOUTH
	}
	else
		wall.color = new_color(-1, -1, -1);
	return (wall);
}

t_point	calc_direction(double ray)
{
	t_point	dir;

	dir.x = (cos(ray) > 0) - (cos(ray) < 0);
	dir.y = (sin(ray) > 0) - (sin(ray) < 0);
	return (dir);
}

t_wall	line_ray(t_game *game, double ray, t_point dir)
{
	int		point;
	t_wall	wall;

	wall.x = game.player.x;
	wall.y = game.player.y;
	wall.color = new_color(-1, -1, -1);
	if (dir.y == 0)
	{
		point = game.player.x / SCALE;
		if (dir.x > 0)
			point += 1;
		while (wall.color.r < 0 && point >= 0 && point < game.map_x)
		{
			wall = check_wall(game, new_point(point * SCALE, game.player.y), dir);
			point += dir.x;
		}
	}
	else
	{
		point = game.player.y / SCALE;
		if (dir.y > 0)
			point += 1;
		while (wall.color.r < 0 && point >= 0 && point < game.map_y)
		{
			wall = check_wall(game, new_point(game.player.x, point * SCALE), dir);
			point += dir.y;
		}
	}
	return (wall);
}

t_wall	find_wall(t_game *game, double ray)
{
	t_point dir;
	t_point x; // intersection with x-line
	t_point	y; // intersection with y-line
	t_wall	wall;
	t_point line; // current point

	wall.x = game.player.x;
	wall.y = game.player.y;
	wall.color = new_color(-1, -1, -1);
	dir = calc_direction(ray);
	if (dir.x == 0 || dir.y == 0)
		return (line_ray(game, ray, dir));
	line = new_point(game.player.x / SCALE, game.player.y / SCALE);
	if (dir.x > 0)
		line.x += 1;
	if (dir.y > 0)
		line.y += 1;
	
	while (line.x >= 0 && line.y >= 0 && line.x < game.map_x && line.y < game.map_y)
	{
		x.x = line.x * SCALE;
		y.y = line.y * SCALE;
		x.y = game.player.y + (x.x - game.player.x) * tan(ray);
		y.x = game.player.x + (y.y - game.player.y) / tan(ray);

		if (abs(y.y - line.y) < abs(x.y - line.y))
			wall = check_wall(game, y);
		else
			wall = check_wall(game, x);
		if (wall.color.r < 0)
		{
			line.x += dir.x;
			line.y += dir.y;
		}

	}
	return (wall);
}