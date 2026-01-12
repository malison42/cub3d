#include "../cub.h"
# include "../parsing/new_parser/parsing_map.h"
// typedef	enum e_sunny_side;
t_texture   *create_texture(t_game *game, char *filename)
{
    t_texture   *texture;

    texture = malloc(sizeof(t_texture));
    if (!texture) {} // error malloc
    texture->image.img = mlx_xpm_file_to_image(game->mlx, filename, \
                                            &texture->width, &texture->height);
	if (!texture->image.img) {} //error mlx
    texture->image.addr = mlx_get_data_addr(texture->image.img, \
                                            &texture->image.bpp, \
                                            &texture->image.line_size, \
                                            &texture->image.endian);
    return (texture);
}

unsigned int get_color_from_texture(double x, double y, t_texture *texture)
{
	int		x_text;
	int		y_text;
	char	*pos;

	x_text = (int)(texture->width * x);
	y_text = (int)(texture->height * y);
	pos = texture->image.addr + (y_text * texture->image.line_size + x_text * 4);
	return (*(unsigned int *)pos);
}

t_texture	*define_texture(char face, t_textures *text)
{
	if (face == 'N')
		return (text->side[NORTH]);
	else if (face == 'W')
		return (text->side[WEST]);
	else if (face == 'S')
		return (text->side[SOUTH]);
	else
		return (text->side[EAST]);
}

void    destroy_texture(t_game *game, t_texture *texture)
{
    if (texture->image.img)
		mlx_destroy_image(game->mlx, texture->image.img);
    free(texture);
}

double	find_x_for_texture(t_wall *collision)
{
	double	x;

	if (collision->face == 'N' || collision->face == 'S')
		x = collision->x - (int)collision->x;
	else
		x = collision->y - (int)collision->y;
	if (collision->face == 'N' || collision->face == 'W')
		x = 1.0 - x;
	return (x);
}
