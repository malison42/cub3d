#include "../cub.h"

double	fdistance(t_wall a, t_ray b)
{
	a.x *= SCALE;
	a.y *= SCALE;
	b.x *= SCALE;
	b.y *= SCALE;
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

void	init_collision_structure(t_game *game, t_collision *c)
{
	c->map.x = game->player.x;
	c->map.y = game->player.y;
	c->delta.x = fabs(1 / c->dir.x);
	c->delta.y = fabs(1 / c->dir.y);
	if (c->step.x < 0)
		c->side.x = (game->player.x - c->map.x) * c->delta.x;
	else
		c->side.x = (1 - game->player.x + c->map.x) * c->delta.x;
	if (c->step.y < 0)
		c->side.y = (game->player.y - c->map.y) * c->delta.y;
	else
		c->side.y = (1 - game->player.y + c->map.y) * c->delta.y;
}

// t_color define_color(char face)
// {
// 	if (face == 'N')
// 		return (new_color(0, 100, 200));
// 	else if (face == 'W')
// 		return (new_color(0, 200, 50));
// 	else if (face == 'S')
// 		return (new_color(200, 200, 0));
// 	else
// 		return (new_color(160, 160, 160));
// }

void	define_surface(t_game *game, t_wall *collision)
{
	if (collision->face == 'X' && game->player.x < collision->x)
		collision->face = 'W';
	else if (collision->face == 'X' && game->player.x > collision->x)
		collision->face = 'E';
	else if (collision->face == 'Y' && game->player.y < collision->y)
		collision->face = 'S';
	else
		collision->face = 'N';
}
