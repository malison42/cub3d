# include "parsing_map.h"

int		str_is_skip(const char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*get_line(int fd)
{
	char	*str;
	size_t	len_str;

	str = get_next_line(fd);
	if (!str)
		return (perror("malloc"), NULL);
	len_str = ft_strlen(str);
	if (len_str > 0 && str[len_str - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	while (str_is_skip(str))
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			return (get_next_line(-1), NULL);
		len_str = ft_strlen(str);
		if (len_str > 0 && str[len_str - 1] == '\n')
			str[ft_strlen(str) - 1] = '\0';
	}
	
	return (str);
}

char	**get_token_config(int fd)
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
	// for (size_t i = 0; tokens[i] != NULL; i++)
	// {
	// 	printf("tikens config[%ld] = %s\n", i, tokens[i]);
	// }

	return (tokens);
}
