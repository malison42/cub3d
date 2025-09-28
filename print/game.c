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

void	draw_w(t_game *game, int x, int h)
{
	int	y;
	int	finish;
	
	y = (B - h) / 2;
	finish = B / 2 + h;
	while (y < finish)
	{
		put_pixel(&game->image, x, y, new_color(255, 255, 255));
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

void	draw_line(t_game *game, double ray, int pix_x)
{
	double	x;
	double	y;
	double	dist;
	double	height;

	x = game->player.x;
	y = game->player.y;
	while (x > 0 && x / SCALE < game->map_x
		   && y > 0 && y / SCALE < game->map_y)
	{
		if (game->map[(int)(y / SCALE)][(int)(x / SCALE)] == '1')
		{
			dist = sqrt(pow(x - game->player.x, 2) + pow(y - game->player.y, 2));
			height = WALL / dist * COEF;
//			printf("h %f\n", height);
			draw_ceiling(game, pix_x, height);
			draw_w(game, pix_x, height);
			draw_floor(game, pix_x, height);
			break ;
		}
		x += cos(ray);
		y += sin(ray);
	}
}

void	draw_game(t_game *game)
{
	double	ray;
	int 	x;
	
	ray = game->player.direction - M_PI / 6;
	x = 0;
	while (x < A)
	{
		draw_line(game, ray, x);
		ray += M_PI / 3 / A;
		++x;
	}
}
