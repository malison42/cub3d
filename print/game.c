#include "../cub.h"

void	draw_ceiling(t_game *game, int x, int h)
{
	int	y;
	int	finish;
	
	y = 0;
	finish = (B - h) / 2;
	while (y < finish)
	{
		put_pixel(&game->image, x, y, create_color(game->texture->ceiling));
		++y;
	}
}

// void	draw_wall_line(t_game *game, int x, int h, t_color color)
// {
// 	int		y;
// 	int		finish;
	
// 	y = ft_max((B - h) / 2, 0);
// 	finish = ft_min((B + h) / 2, B);
// 	while (y < finish)
// 	{

// 		put_pixel(&game->image, x, y, color);
// 		++y;
// 	}
// }

void	draw_wall_line(t_game *game, int x, int h, t_wall *collision)
{
	int		y;
	int		start;
	int		finish;
	double	x_text;
	int		color;

(void)x;
	
	x_text = find_x_for_texture(collision);
	start = ft_max((B - h) / 2, 0);
	finish = ft_min((B + h) / 2, B);
	y = 0;
	while (start + y < finish)
	{
		color = get_color_from_texture(x_text, 1.0 * y / h, game->t);
		put_pixel(&game->image, x, start + y, color);
		// printf("x %f y %f\n", x_text, 1.0 * y / h);
		++y;
	}
	// destroy_texture(game, texture);
}

void	draw_floor(t_game *game, int x, int h)
{
	int	y;
	int	finish;
	
	y = ft_min((B + h) / 2, B);
	finish = B;
	while (y < finish)
	{
		put_pixel(&game->image, x, y, create_color(game->texture->floor));
		++y;
	}
}

void	draw_vertical_line(t_game *game, double ray, int x)
{
	double	height;
	double	dist;
	t_wall	collision;
	t_color	color;

	collision = find_collision(game, ray);
	color = define_color(collision.face);
	dist = fdistance(collision, game->player);
	height = WALL / dist * COEF;
	height = height / cos(game->player.direction - ray);
	draw_ceiling(game, x, height);
	draw_wall_line(game, x, height, &collision);
	draw_floor(game, x, height);
}

void	draw_game(t_game *game)
{
	double	ray;
	int 	x;

	ray = game->player.direction - M_PI / 6;
	x = 0;
	while (x < A)
	{
		draw_vertical_line(game, ray, x);
		ray += M_PI / 3 / A;
		++x;
	}
}
