#include "../cub.h"

int	parse_map(char *filepath)
{
	int			fd;
	t_textures	*tex;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (perror(filepath), 1);
	tex = malloc(sizeof(t_textures));
	if (!tex)
		return (perror("malloc"), close(fd), 1);
	parse_textures(fd, tex);
	printf("\nnorth %d\nsouth %d\nwest %d\neast %d\n", tex->north, tex->south, tex->west, tex->east);
	printf("floor %d, %d, %d\n", tex->floor.r, tex->floor.g, tex->floor.b);
	printf("ceiling %d, %d, %d\n", tex->ceiling.r, tex->ceiling.g, tex->ceiling.b);
	return (0);
}
