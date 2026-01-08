#include "../cub.h"

void	draw_ceiling(t_game *game, int x, int h)
{
	int	y;
	int	finish;
	
	y = 0;
	finish = (B - h) / 2;
	while (y < finish)
	{
		put_pixel(&game->image, x, y, game->texture->ceiling);
		++y;
	}
}

void	draw_wall_line(t_game *game, int x, int h, t_color color)
{
	int	y;
	int	finish;
	
	y = (B - h) / 2;
	finish = B / 2 + h;
	while (y < finish)
	{
		put_pixel(&game->image, x, y, color);
		++y;
	}
}

void	draw_floor(t_game *game, int x, int h)
{
	int	y;
	int	finish;
	
	y = B / 2 + h;
	finish = B;
	while (y < finish)
	{
		put_pixel(&game->image, x, y, game->texture->floor);
		++y;
	}
}


double	fdistance(t_ray a, t_ray b)
{
	a.x *= SCALE;
	a.y *= SCALE;
	b.x *= SCALE;
	b.y *= SCALE;
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

void	draw_vertical_line(t_game *game, double ray, int x)
{
	double	height;
	double	dist;
	t_ray	collision;

	collision = find_collision(game, ray);
	// printf("collision x %f  y %f\n", collision.x, collision.y);
	dist = fdistance(collision, game->player);
	height = WALL / dist * COEF;
	draw_ceiling(game, x, height);
// printf("h %f\n", height);
	draw_wall_line(game, x, height, new_color(160, 160, 160));
	draw_floor(game, x, height);
}

void	draw_game(t_game *game)
{
	double	ray;
	int 	x;
	
	printf("\nredraw   x %f y %f\n", game->player.x, game->player.y);
	ray = game->player.direction - M_PI / 6;
	x = 0;
	while (x < A)
	{
		// draw_line2(game, ray, x);
		// collision = find_collision(game, ray);
		draw_vertical_line(game, ray, x);
		ray += M_PI / 3 / A;
		++x;
	}
	printf("redraw   x %f y %f\n", game->player.x, game->player.y);
}
