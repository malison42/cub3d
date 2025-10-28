#include "../cub.h"

t_wall	check_wall(t_game *game, t_point p, t_point dir)
{
	t_wall	wall;

	wall.x = p.x;
	wall.y = p.y;
	if (game->map[(p.y) / SCALE][(p.x + 5 * dir.x) / SCALE] == '1')
	{
		if (dir.x > 0)
			wall.color = new_color(195, 205, 250); // WEST
		else
			wall.color = new_color(195, 250, 205); // EAST
	}
	else if (game->map[(p.y + 5 * dir.y) / SCALE][(p.x) / SCALE] == '1')
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

	if (cos(ray) > 0)
		dir.x = 1;
	else
		dir.x = -1;
	if (sin(ray) > 0)
		dir.y = 1;
	else
		dir.y = -1;
	return (dir);
}

t_wall	find_wall(t_game *game, double ray)
{
	t_point dir;
	t_point x; // intersection with x-line
	t_point	y; // intersection with y-line
	t_wall	wall;
	t_point line; // current point

	if (sin(ray) == 0)
		return (NULL);
	if (cos(ray) == 0)
		return (NULL);
	
	wall.x = game.player.x;
	wall.y = game.player.y;
	wall.color = new_color(-1, -1, -1);
	dir = calc_direction(ray);
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