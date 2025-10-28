#include "../cub.h"

t_color	check_wall(t_game *game, int x, int y)
{
	return (new_color(0, 0, 0));
}

t_wall	find_x_wall(t_game *game, double ray)
{

}

t_wall	find_wall(t_game *game, double ray)
{
	int bias_x;
	int bias_y;
	int dx;
	int dy;
	int x1;
	int y1;
	int x_new;
	int y_new;
	
	if (sin(ray) == 0)
		return (NULL);
	if (cos(ray) == 0)
		return (NULL);
	
	bias_x = cos(ray) > 0;
	bias_y = sin(ray) > 0;
	
	dx = (game->player.x / SCALE + bias_x) * SCALE;
	dy = (game->player.y / SCALE + bias_y) * SCALE;
	y1 = game->player.y + dx * tan(ray);
	x1 = game->player.x + dy / tan(ray);
	if (y1 - game->player.y < dy)
	{
		x_new = game->player.x + dx;
		y_new = y1;
	}
	
}