#include "parsing_map.h"

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
	for (size_t i = 0; map[i] != NULL; i++)
	{
		printf("MgfAP[%zu]: %s\n", i, map[i]);
	}
	return (map);
}
