#include "../cub.h"

t_wall	straight_ray(t_game *game, t_collision *c)
{
	t_wall	point;

	c->map.x = game->player.x;
	c->map.y = game->player.y;
	while (game->map[c->map.y][c->map.x] != '1')
	{
		c->map.y += c->step.y;
		c->map.x += c->step.x;
	}
	if (c->dir.x == 0)
	{
		point.x = game->player.x;
		point.y = c->map.y + (c->step.y < 0);
		point.face = 'Y';
	}
	else
	{
		point.x = c->map.x + (c->step.x < 0);
		point.y = game->player.y;
		point.face = 'X';
	}
	return (point);
}

t_wall	inclined_ray(t_game *game, t_collision *c)
{
	t_wall	point;
	double	t;

	init_collision_structure(game, c);
	while (game->map[c->map.y][c->map.x] != '1')
	{
		if (c->side.x < c->side.y)
		{
			c->side.x += c->delta.x;
			c->map.x += c->step.x;
			point.face = 'X';
		}
		else
		{
			c->side.y += c->delta.y;
			c->map.y += c->step.y;
			point.face = 'Y';
		}
	}
	if (point.face == 'X')
		t = (c->map.x - game->player.x + (c->step.x < 0)) / c->dir.x;
	else
		t = (c->map.y - game->player.y + (c->step.y < 0)) / c->dir.y;
	point.x = game->player.x + c->dir.x * t;
	point.y = game->player.y + c->dir.y * t;
	return (point);
}

t_wall	find_collision(t_game *game, double ray)
{
	t_wall		collision;
	t_collision	c;

	c.dir.x = cos(ray);
	c.dir.y = sin(ray);
	if (cos(ray) == cos(3 * M_PI_2))
		c.dir.x = 0;
	if (sin(ray) == sin(M_PI))
		c.dir.y = 0;
	c.step.x = (c.dir.x > 0) - (c.dir.x < 0);
	c.step.y = (c.dir.y > 0) - (c.dir.y < 0);
	if (c.dir.x == 0 || c.dir.y == 0)
		collision = (straight_ray(game, &c));
	else
		collision = (inclined_ray(game, &c));
	define_surface(game, &collision);
	return (collision);
}
