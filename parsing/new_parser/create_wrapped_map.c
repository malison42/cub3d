#include "parsing_map.h"

char	*fill_str_symb(char	*str, char symb, int len_alloc)
{
	int	i;

	i = 0;
	while (i < len_alloc)
	{
		str[i] = symb;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*create_wrapped_cols(t_game *game, char **map, int i)
{
	char	*wrapped_line;
	int		wrapped_cols;

	wrapped_cols = game->map_x + 2;
	wrapped_line = malloc(sizeof(char) * (wrapped_cols + 1));
	if (!wrapped_line)
		return (NULL);
	if (i == 0 || i == game->map_y + 1)
		ft_memset(wrapped_line, '#', wrapped_cols);
	else
	{
		wrapped_line[0] = '#';
		ft_memcpy(wrapped_line + 1, map[i - 1], game->map_x);
		wrapped_line[wrapped_cols - 1] = '#';
	}
	wrapped_line[wrapped_cols] = '\0';
	return (wrapped_line);
}

char	**create_wrapped_map(t_game *game, char **map)
{
	char	**map_wrapped;
	int		i;
	int		wrapped_rows;

	i = 0;
	wrapped_rows = game->map_y + 2;
	map_wrapped = malloc(sizeof(char *) * (wrapped_rows + 1));
	if (!map_wrapped)
		return (NULL);
	while (i < wrapped_rows)
	{
		map_wrapped[i] = create_wrapped_cols(game, map, i);
		if (!map_wrapped[i])
			return (free_map_array(map_wrapped, i), NULL);
		i++;
	}
	map_wrapped[wrapped_rows] = NULL;
	return (map_wrapped);
}
