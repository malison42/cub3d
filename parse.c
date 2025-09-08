#include "cub.h"

int	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		++i;
	}
	free(tokens);
}

int	parse_wall(int fd, char	*orientation)
{
	char	*str;
	char	**tokens;
	int		texture_fd;

	str = get_next_line(fd);
	if (!str)
		return (perror("malloc"), -1);
	while (str && ft_strcmp(str, ""))
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			return (perror("malloc"), -1);
	}
	if (!str)
		return (-2);
	tokens = ft_split(str);
	free(str);
	if (!tokens)
		return (perror("malloc"), -1);
	if (tokens[2] || ft_strcmp(orientation, tokens[0]))
		return (free_tokens(tokens), -2);
	texture_fd = open(tokens[1], O_RDONLY);
	free_tokens(tokens);
	return (texture_fd);
}

int	parse_textures(int fd, t_textures *tex)
{
	tex->north = parse_wall(fd, "NO");
	tex->south = parse_wall(fd, "SO");
	tex->west = parse_wall(fd, "WE");
	tex->east = parse_wall(fd, "EA");
	if (tex->north == -1 || tex->south == -1\
		|| tex->west == -1 || tex->east == -1)
		return (EXIT_FAILURE);
	if (tex->north == -2 || tex->south == -2\
		|| tex->west == -2 || tex->east == -2)
	{
		perror(MESSAGE_SCENE_NOT_VALID);
		return (EXIT_FAILURE);
	}
}

int parse_map(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (perror(MESSAGE_WRONG_FILE, model), 1);

}