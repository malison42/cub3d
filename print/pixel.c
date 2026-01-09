#include "../cub.h"

int	create_color(t_color color)
{
	int	t;
	
	t = 0;
	return (t << 24 | color.r << 16 | color.g << 8 | color.b);
}

// void	put_pixel(t_image *img, int x, int y, t_color color)
// {
// 	char	*dst;
	
// 	if (y >= 1024)
// 		printf("x %d y %d\n", x, y);
// 	dst = img->addr + (y * img->line_size + x * (img->bpp / 8));
// 	*(unsigned int *)dst = create_color(color);
// }

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;
	
	if (y >= 1024)
		printf("x %d y %d\n", x, y);
	dst = img->addr + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_point	new_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}
