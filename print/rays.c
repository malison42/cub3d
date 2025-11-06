#include "../cub.h"

t_wall	check_wall(t_game *game, t_point p, t_point dir)
{
	t_wall	wall;

	wall.x = p.x;
	wall.y = p.y;
//	printf("check point %d %d\n", p.x, p.y);
	if (dir.x && game->map[(p.y - dir.y) / SCALE][(p.x + 5 * dir.x) / SCALE] == '1')
	{
		if (dir.x > 0)
			wall.color = new_color(195, 205, 250); // WEST
		else
			wall.color = new_color(195, 250, 205); // EAST
	}
	else if (dir.y && game->map[(p.y + 5 * dir.y) / SCALE][(p.x - dir.x) / SCALE] == '1')
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

//	printf("straight line\n");
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
//		printf("line_x %d, line_y %d\n", line.x, line.y);
		x.x = line.x * SCALE;
		y.y = line.y * SCALE;
//		printf("rescale_x %d, rescale_y %d\n", x.x, y.y);
//		printf("player_x %f, player_y %f\n", game->player.x, game->player.y);
//		printf("tan %f\n", tan(ray));
		x.y = game->player.y + (x.x - game->player.x) * tan(ray);
		y.x = game->player.x + (y.y - game->player.y) / tan(ray);
//		printf("x.x %d x.y %d\n", x.x, x.y);
//		printf("y.x %d y.y %d\n", y.x, y.y);
//		printf("delta y %f   delta x %f\n", fabs(y.y - game->player.y), fabs(x.y - game->player.y));
		if (fabs(y.y - game->player.y) < fabs(x.y - game->player.y))
		{
//			printf("y\n");
//			printf("x %d y %d\n", y.x, y.y);
			wall = check_wall(game, y, dir);
			line.y += dir.y;
		}
		else
		{
//			printf("x\n");
//			printf("x %d y %d\n", x.x, x.y);
			wall = check_wall(game, x, dir);
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
//	printf("%d\n", cos(3*M_PI_2) == cos(ray));
//	printf("dir.x %d  dir.y %d\n", dir.x, dir.y);
	if (dir.x == 0 || dir.y == 0)
		return (straight_line(game, ray, dir));
	else
		return (inclined_line(game, ray, dir));
}