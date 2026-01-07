#include "../cub.h"

// добавить пометку с осью, с которой пересекается луч
t_wall	check_wall(t_game *game, t_point p, t_point dir)
{
	t_wall	wall;

	wall.x = p.x;
	wall.y = p.y;
	if (dir.x && game->map[(p.y) / SCALE][(p.x - (dir.x < 0)) / SCALE] == '1')
	{
		if (dir.x > 0)
			wall.color = new_color(195, 205, 250); // WEST
		else
			wall.color = new_color(195, 250, 205); // EAST
	}
	else if (dir.y && game->map[(p.y - (dir.y < 0)) / SCALE][(p.x) / SCALE] == '1')
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
			wall = check_wall(game, new_point(point * SCALE, game->player.y), dir);
			point += dir.x;
		}
	}
	else
	{
		point = game->player.y / SCALE + (dir.y > 0);
		while (wall.color.r < 0 && point > 0 && point < game->map_y)
		{
			wall = check_wall(game, new_point(game->player.x, point * SCALE), dir);
			point += dir.y;
		}
	}
	return (wall);
}


t_ray	straight_line2(t_game *game, double ray, t_point dir)
{
	int		step_y;
	int 	step_x;
	t_ray	collision;
	
	
	(void)ray;
	step_x = game->player.x / SCALE;
	step_y = game->player.y / SCALE;
	if (dir.y == 0)
	{
		while (step_x >= 0 && step_x < game->map_x)
		{
			if (game->map[step_y][step_x] == '1')
			{
				collision.y = game->player.y;
				collision.x = (step_x + (dir.x < 0)) * SCALE;
				return (collision);
			}
			step_x += dir.x;
		}
	}
	else
	{
		while (step_y >= 0 && step_y < game->map_y)
		{
			if (game->map[step_y][step_x] == '1')
			{
				collision.x = game->player.x;
				collision.y = (step_y + (dir.y < 0)) * SCALE;
				return (collision);
			}
			step_y += dir.y;
		}
	}
	collision.x = 0;
	collision.y = 0;
	return (collision);
}

double	distance(t_ray a, t_ray b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

t_ray	inclined_line2(t_game *game, double ray, t_point dir)
{
//	t_point x; // intersection with x-line
//	t_point	y; // intersection with y-line
//	t_wall	wall;
//	t_point line; // current lines
	t_ray collision_x;
	t_ray collision_y;
	int step_y;
	int	step_x;
	
//	wall.x = game->player.x;
//	wall.y = game->player.y;
//	wall.color = new_color(-1, -1, -1);
//	line = new_point(game->player.x / SCALE + (dir.x > 0), game->player.y / SCALE + (dir.y > 0));
	
	step_x = game->player.x / SCALE + (dir.x > 0);
	step_y = game->player.y / SCALE + (dir.y > 0);
	while (1)
	{
		if (game->map[step_y][step_x] == '1')
		{
			collision_x.x = (step_x + (dir.x < 0)) * SCALE;
			collision_x.y = game->player.y + tan(ray) * (collision_x.x - game->player.x);
			break ;
		}
		step_x += dir.x;
	}
	
	step_x = game->player.x / SCALE + (dir.x > 0);
	step_y = game->player.y / SCALE + (dir.y > 0);
	while (1)
	{
		if (game->map[step_y][step_x] == '1')
		{
			collision_y.y = (step_y + (dir.y < 0)) * SCALE;
			collision_y.x = game->player.x + (collision_y.y - game->player.y) / tan(ray);
			break ;
		}
		step_y += dir.y;
	}
	
	if (distance(game->player, collision_x) < distance(game->player, collision_y))
		return (collision_x);
	else
		return (collision_y);
	
	
//	while (line.x > 0 && line.y > 0 && line.x < game->map_x && line.y < game->map_y)
//	{
//		x.x = line.x * SCALE;
//		y.y = line.y * SCALE;
//		x.y = game->player.y + (x.x - game->player.x) * tan(ray);
//		y.x = game->player.x + (y.y - game->player.y) / tan(ray);
//		if (fabs(y.y - game->player.y) < fabs(x.y - game->player.y))
//		{
//			wall = check_wall(game, y, dir);
//			line.y += dir.y;
//		}
//		else
//		{
//			wall = check_wall(game, x, dir);
//			line.x += dir.x;
//		}
//		if (wall.color.r >= 0)
//			break ;
//	}
//	return (wall);
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
			wall = check_wall(game, y, dir);
			line.y += dir.y;
		}
		else
		{
			wall = check_wall(game, x, dir);
			line.x += dir.x;
		}
		if (wall.color.r >= 0)
			break ;
	}
	return (wall);
}

t_wall	wall_color(t_game *game, t_point dir, t_ray collision)
{
	int wall_x;
	int wall_y;
	t_wall	wall;
	
	wall_x = collision.x / SCALE;
	wall_y = collision.y / SCALE;
	wall.x = collision.x;
	wall.y = collision.y;
	
	if (dir.x > 0 && dir.y > 0)
	{
		if (game->map[wall_y - 1][wall_x] != '1')
			wall.color = new_color(250, 200, 190); // NORTH
		else
			wall.color = new_color(195, 205, 250); // WEST
	}
	else if (dir.x > 0 && dir.y == 0)
	{
		wall.color = new_color(195, 205, 250); // WEST
	}
	else if (dir.x > 0 && dir.y < 0)
	{
		if (game->map[wall_y][wall_x] == '1')
			wall.color = new_color(195, 205, 250); // WEST
		else
			wall.color = new_color(250, 250, 190); // SOUTH
	}
	else if (dir.x < 0 && dir.y < 0)
	{
		if (game->map[wall_y][wall_x - 1] != '1')
			wall.color = new_color(250, 250, 190); // SOUTH
		else
			wall.color = new_color(195, 250, 205); // EAST
	}
	else if (dir.x < 0 && dir.y == 0)
	{
		wall.color = new_color(195, 250, 205); // EAST
	}
	else if (dir.x == 0 && dir.y > 0)
	{
		wall.color = new_color(250, 200, 190); // NORTH
	}
	else if (dir.x == 0 && dir.y < 0)
	{
		wall.color = new_color(250, 250, 190); // SOUTH
	}
	else
	{
		if (game->map[wall_y][wall_x] == '1')
			wall.color = new_color(250, 200, 190); // NORTH
		else
			wall.color = new_color(195, 250, 205); // EAST
	}
	
	return (wall);
}

t_wall	find_wall(t_game *game, double ray)
{
	t_point dir;
	t_ray	collision;

	dir.x = (cos(ray) > 0) - (cos(ray) < 0);
	dir.y = (sin(ray) > 0) - (sin(ray) < 0);
	if (cos(ray) == cos(3 * M_PI_2))
		dir.x = 0;
	if (sin(ray) == sin(M_PI))
		dir.y = 0;
	if (dir.x == 0 || dir.y == 0)
		collision = (straight_line2(game, ray, dir));
	else
		collision = (inclined_line2(game, ray, dir));
	return (wall_color(game, dir, collision));
}