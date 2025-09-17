#include "../cub.h"

void	free_tokens(char **tokens)
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

char	*get_line(int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (!str)
		return (perror("malloc"), NULL);
	str[ft_strlen(str) - 1] = 0;
	while (!ft_strcmp(str, ""))
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			return (perror("malloc"), NULL);
		str[ft_strlen(str) - 1] = 0;
	}
	return (str);
}

char	**parse_tokens(int fd)
{
	char	*str;
	char	**tokens;

	str = get_line(fd);
	if (!str)
		return (NULL);
	tokens = ft_split(str, ' ');
	free(str);
	if (!tokens)
		return (perror("malloc"), NULL);
	if (tokens[2])
	{
		ft_putstr_fd(MESSAGE_SCENE_NOT_VALID, STDERR_FILENO);
		return (free_tokens(tokens), NULL);
	}
	return (tokens);
}

int	parse_wall(char ***lines, char *specifier)
{
	int	texture_fd;
	int	i;

	i = 0;
	while (i < 6 && ft_strcmp(lines[i][0], specifier))
		++i;
	if (i == 6)
	{
		ft_putstr_fd(MESSAGE_SCENE_NOT_VALID, STDERR_FILENO);
		return (-1);
	}
	texture_fd = open(lines[i][1], O_RDONLY);
	if (texture_fd < 0)
		perror(lines[i][1]);
	return (texture_fd);
}


char	***read_lines(int fd)
{
	char	***lines;
	int		i;

	lines = malloc(sizeof(char **) * 7);
	if (!lines)
		return (NULL);
	i = 0;
	while (i < 6)
	{
		lines[i] = parse_tokens(fd);
		if (!lines[i])
			break ;
		++i;
	}
	lines[i] = NULL;
	if (i < 6)
	{
		while (--i >= 0)
			free_tokens(lines[i]);
		free(lines);
		return (NULL);
	}
	return (lines);
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
