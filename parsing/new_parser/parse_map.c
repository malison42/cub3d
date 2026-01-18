#include "parsing_map.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '#')
			return (0);
		i++;
	}
	return (1);
}

int	check_empty_line_after(t_game *game, char **map, int start_line)
{
	int	i;

	i = start_line;
	while (i < game->map_y)
	{
		if (!is_empty_line(map[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_map_with_empty_lines(t_game *game, char **map)
{
	int	i;
	int	empty_line;

	i = 0;
	empty_line = 0;
	while (i < game->map_y)
	{
		if (is_empty_line(map[i]))
		{
			empty_line = 1;
			break ;
		}
		i++;
	}
	if (empty_line && !check_empty_line_after(game, map, i + 1))
	{
		printf("Error\nMap contains empty line inside the map\n");
		return (1);
	}
	return (0);
}

int	is_valid_map(t_game *game, char **map)
{
	if (!is_valid_sym(game, map, VALID_CHARS))
		return (0);
	if (!validate_player_start(game, map))
		return (0);
	if (!is_mape_closure(game, map))
		return (0);
	if (is_map_with_empty_lines(game, map))
		return (0);
	resize_map_y(game, map);
	return (1);
}

char	**parse_map(int fd, t_game *game)
{
	char	**map;
	t_list	*map_list;

	map_list = NULL;
	map_list = read_map_to_list(fd, &game->map_x);
	if (!map_list)
		return (NULL);
	game->map_y = ft_lstsize(map_list);
	map = get_normalized_map(game, map_list);
	if (!map)
		return (ft_lstclear(&map_list, free), NULL);
	ft_lstclear(&map_list, free);
	if (!is_valid_map(game, map))
	{
		free_map_array(map, game->map_y);
		return (NULL);
	}
	return (map);
}
