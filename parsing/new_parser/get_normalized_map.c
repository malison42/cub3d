#include "parsing_map.h"

char	*pad_line_end(char *line, int map_x)
{
	int	i;

	i = ft_strlen(line);
	while (i < map_x)
	{
		line[i] = '#';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	**get_normalized_map(t_game *game, t_list *map_list)
{
	int		i;
	t_list	*tmp;
	char	**map;

	i = 0;
	tmp = map_list;
	map = malloc(sizeof(char *) * (game->map_y + 1));
	if (!map)
		return (NULL);
	while (i < game->map_y)
	{
		map[i] = malloc(game->map_x + 1);
		if (!map[i])
			return (free_map_array(map, i), NULL);
		ft_strlcpy(map[i], (char *)tmp->content, game->map_x + 1);
		map[i] = pad_line_end(map[i], game->map_x);
		tmp = tmp->next;
		++i;
	}
	map[i] = NULL;
	return (map);
}
