#include "../cub.h"

void	line_x(t_point a, t_point b, t_game *game)
{
	t_point	c;
	double	k;
	int		i;
	int		sign_i;

	k = 1.0 * abs(b.y - a.y) / abs(b.x - a.x);
	c = a;
	i = 0;
	sign_i = 1 * (b.y > a.y) - 1 * (b.y < a.y);
	while (i < (int)(abs(b.x - a.x)))
	{
		if (fabs(k * i * sign_i + a.y - c.y) > 0.5)
			c.y += sign_i;
		if (c.x > 0 && c.x < A && c.y > 0 && c.y < B)
		{
			put_pixel(&game->map2D.image, c.x + game->map2D.shift_x,
				c.y + game->map2D.shift_y, create_color(game->map2D.ray_color));
		}
		c.x += 1 * (b.x - a.x > 0) - 1 * (b.x - a.x < 0);
		++i;
	}
}

void	line_y(t_point a, t_point b, t_game *game)
{
	t_point	c;
	double	k;
	int		i;
	int		sign_i;

	k = 1.0 * abs(b.x - a.x) / abs(b.y - a.y);
	c = a;
	i = 0;
	sign_i = 1 * (b.x > a.x) - 1 * (b.x < a.x);
	while (i < (int)(abs(b.y - a.y)))
	{
		if (fabs(k * i * sign_i + a.x - c.x) > 0.5)
			c.x += 1 * (b.x - a.x > 0) - 1 * (b.x - a.x < 0);
		if (c.x > 0 && c.x < A && c.y > 0 && c.y < B)
		{
			put_pixel(&game->map2D.image, c.x + game->map2D.shift_x,
				c.y + game->map2D.shift_y, create_color(game->map2D.ray_color));
		}
		c.y += 1 * (b.y - a.y > 0) - 1 * (b.y - a.y < 0);
		++i;
	}
}

void	line(t_point a, t_point b, t_game *game)
{
	if (a.x == b.x || 1.0 * abs(b.y - a.y) / abs(b.x - a.x) > 1)
		line_y(a, b, game);
	else
		line_x(a, b, game);
}
