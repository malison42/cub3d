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
