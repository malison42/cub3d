#include "../cub.h"

int	parse_wall(char ***lines, char *specifier)
{
	int	texture_fd;
	int	i;

	i = 0;
	while (i < 6 && lines[i][0] && ft_strcmp(lines[i][0], specifier))
		++i;
	if (i == 6 || !lines[i][1])
	{
		ft_putstr_fd(MESSAGE_SCENE_NOT_VALID, STDERR_FILENO);
		return (-1);
	}
	texture_fd = open(lines[i][1], O_RDONLY);
	if (texture_fd < 0)
		perror(lines[i][1]);
	return (texture_fd);
}

int	parse_textures(int fd, t_textures *tex)
{
	char	***lines;
	int		i;

	lines = read_lines(fd);
	if (!lines)
		return (1);
	tex->north = parse_wall(lines, "NO");
	tex->south = parse_wall(lines, "SO");
	tex->west = parse_wall(lines, "WE");
	tex->east = parse_wall(lines, "EA");
	tex->floor = parse_color(lines, "F");
	tex->ceiling = parse_color(lines, "C");
	i = 0;
	while (i < 6)
	{
		free_tokens(lines[i]);
		i++;
	}
	free(lines);
	if (tex->north < 0 || tex->south < 0
		|| tex->west < 0 || tex->east < 0)
		return (EXIT_FAILURE);
	if (tex->floor.r < 0 || tex->ceiling.r < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
