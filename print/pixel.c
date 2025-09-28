#include "../cub.h"

int	create_color(t_color color)
{
	int	t;
	
	t = 0;
	return (t << 24 | color.r << 16 | color.g << 8 | color.b);
}

void	put_pixel(t_image *img, int x, int y, t_color color)
{
	char	*dst;
	
	dst = img->addr + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int*)dst = create_color(color);
}

