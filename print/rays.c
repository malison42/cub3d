#include "../cub.h"

// добавить пометку с осью, с которой пересекается луч
t_wall	check_wall(t_game *game, t_point p, t_point dir, char axis)
{
	t_wall	wall;

	wall.x = p.x;
	wall.y = p.y;
	if (axis == 'x' && dir.x && game->map[(p.y) / SCALE][(p.x + 1 * dir.x) / SCALE] == '1')
	{
		if (dir.x > 0)
			wall.color = new_color(195, 205, 250); // WEST
		else
			wall.color = new_color(195, 250, 205); // EAST
	}
	else if (dir.y && game->map[(p.y + 1 * dir.y) / SCALE][(p.x) / SCALE] == '1')
	{
		if (dir.y > 0)
			wall.color = new_color(250, 250, 190); // NORTH
		else
			wall.color = new_color(250, 200, 190); // SOUTH
	}
	else
		wall.color = new_color(-1, -1, -1);
	wall.x += dir.x;
	wall.y += dir.y;
	return (wall);
}

t_wall	straight_line(t_game *game, double ray, t_point dir)
{
	int		point;
	t_wall	wall;

	(void)ray;
	wall.x = game->player.x;
	wall.y = game->player.y;
	wall.color = new_color(-1, -1, -1);
	if (dir.y == 0)
	{
		point = game->player.x / SCALE + (dir.x > 0);
		while (wall.color.r < 0 && point > 0 && point < game->map_x)
		{
			wall = check_wall(game, new_point(point * SCALE, game->player.y), dir, 'x');
			point += dir.x;
		}
	}
	else
	{
		point = game->player.y / SCALE + (dir.y > 0);
		while (wall.color.r < 0 && point > 0 && point < game->map_y)
		{
			wall = check_wall(game, new_point(game->player.x, point * SCALE), dir, 'y');
			point += dir.y;
		}
	}
	return (wall);
}

t_wall	inclined_line(t_game *game, double ray, t_point dir)
{
	t_point x; // intersection with x-line
	t_point	y; // intersection with y-line
	t_wall	wall;
	t_point line; // current lines

	wall.x = game->player.x;
	wall.y = game->player.y;
	wall.color = new_color(-1, -1, -1);
	line = new_point(game->player.x / SCALE + (dir.x > 0), \
					game->player.y / SCALE + (dir.y > 0));
	
	while (line.x > 0 && line.y > 0 && line.x < game->map_x && line.y < game->map_y)
	{
		x.x = line.x * SCALE;
		y.y = line.y * SCALE;
		x.y = game->player.y + (x.x - game->player.x) * tan(ray);
		y.x = game->player.x + (y.y - game->player.y) / tan(ray);
		if (fabs(y.y - game->player.y) < fabs(x.y - game->player.y))
		{
			wall = check_wall(game, y, dir, 'y');
			line.y += dir.y;
		}
		else
		{
			wall = check_wall(game, x, dir, 'x');
			line.x += dir.x;
		}
		if (wall.color.r >= 0)
			break ;
	}
	return (wall);
}

t_wall	find_wall(t_game *game, double ray)
{
	t_point dir;

	dir.x = (cos(ray) > 0) - (cos(ray) < 0);
	dir.y = (sin(ray) > 0) - (sin(ray) < 0);
	if (cos(ray) == cos(3 * M_PI_2))
		dir.x = 0;
	if (sin(ray) == sin(M_PI))
		dir.y = 0;
	if (dir.x == 0 || dir.y == 0)
		return (straight_line(game, ray, dir));
	else
		return (inclined_line(game, ray, dir));
}