#include "../cub.h"

void	draw_ceiling(t_game *game, int x, int h)
{
	int	y;
	int	finish;

	y = 0;
	if (h < 0 || h > B)
	{
		finish = 0;
	}
	else
		finish = (B - h) / 2;
	while (y < finish)
	{
		put_pixel(&game->image, x, y, create_color(game->texture->ceiling));
		++y;
	}
}

void	draw_wall_line(t_game *game, int x, int h, t_wall *collision)
{
	int		y;
	int		start;
	int		finish;
	double	x_text;
	int		color;

	x_text = find_x_for_texture(collision);
	if (h < 0 || h > B)
	{
		start = 0;
		finish = B;
	}
	else
	{
		start = ft_max((B - h) / 2, 0);
		finish = ft_min((B + h) / 2, B);
	}
	y = 0;
	while (start + y < finish)
	{
		color = get_color_from_texture(x_text, 1.0 * y / h,
				define_texture(collision->face, game->texture));
		put_pixel(&game->image, x, start + y, color);
		++y;
	}
}
	// destroy_texture(game, texture);

void	draw_floor(t_game *game, int x, int h)
{
	int	y;
	int	start;
	int	finish;

	if (h < 0 || h > B)
	{
		start = B;
	}
	else
		start = ft_min((B + h) / 2, B);
	finish = B;
	y = 0;
	while (start + y < finish)
	{
		put_pixel(&game->image, x, start + y, create_color(game->texture->floor));
		++y;
	}

	// start = ft_max((B - h) / 2, 0);
	// finish = ft_min((B + h) / 2, B);
	// y = 0;
	// while (start + y < finish)
	// {
	// 	color = get_color_from_texture(x_text, 1.0 * y / h,
	// 			define_texture(collision->face, game->texture));
	// 	put_pixel(&game->image, x, start + y, color);
	// 	++y;
	// }
}

void	draw_vertical_line(t_game *game, double ray, int x)
{
	double	height;
	double	dist;
	t_wall	collision;

	collision = find_collision(game, ray);
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
	int		x;

	ray = game->player.direction - M_PI / 6;
	x = 0;
	while (x < A)
	{
		draw_vertical_line(game, ray, x);
		ray += M_PI / 3 / A;
		++x;
	}
}
