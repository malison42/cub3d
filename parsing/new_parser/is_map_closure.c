#include "parsing_map.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	flood_fill_accessibility(t_game *game, char **map_wrapped, int y, int x)
{
	char	curent_char;

	if (y < 0 || x < 0 || x >= (game->map_x + 3) || y >= (game->map_y + 3))
		return (1);
	curent_char = map_wrapped[y][x];
	if (curent_char == ' ' || curent_char == '#')
		return (0);
	if (curent_char == '1' || curent_char == 'F')
		return (1);
	map_wrapped[y][x] = 'F';
	if (!flood_fill_accessibility(game, map_wrapped, y + 1, x)
		|| !flood_fill_accessibility(game, map_wrapped, y - 1, x)
		|| !flood_fill_accessibility(game, map_wrapped, y, x + 1)
		|| !flood_fill_accessibility(game, map_wrapped, y, x - 1))
	{
		return (0);
	}
	return (1);
}

int	flood_fill_closure(t_game *game, char **map_wrapped, int y, int x)
{
	char	curent_char;

	if (y < 0 || x < 0 || x >= (game->map_x + 2) || y >= (game->map_y + 2)
		|| map_wrapped[y] == NULL || map_wrapped[y][x] == '\0')
		return (1);
	curent_char = map_wrapped[y][x];
	if (curent_char == '0' || ft_isset(curent_char, "NSWE"))
		return (0);
	if (curent_char == '1' || curent_char == 'F')
		return (1);
	if (curent_char == '#' || curent_char == ' ')
		map_wrapped[y][x] = 'F';
	else
		return (0);
	if (!flood_fill_closure(game, map_wrapped, y + 1, x)
		|| !flood_fill_closure(game, map_wrapped, y - 1, x)
		|| !flood_fill_closure(game, map_wrapped, y, x + 1)
		|| !flood_fill_closure(game, map_wrapped, y, x - 1))
	{
		return (0);
	}
	return (1);
}

int	check_all_reachable( char **map_wrapped)
{
	int	x;
	int	y;

	y = 0;
	while (map_wrapped[y])
	{
		x = 0;
		while (map_wrapped[y][x])
		{
			if (ft_isset(map_wrapped[y][x], "0NSWE"))
			{
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	is_mape_closure(t_game *game, char **map)
{
	char	**copy_map;

	copy_map = create_wrapped_map(game, map);
	if (!copy_map)
		return (0);
	if (!flood_fill_closure(game, copy_map, 0, 0))
	{
		printf("Error\nMap is not closed: map is open to the outside.\n");
		return (free_array(copy_map), 0);
	}
	if (!flood_fill_accessibility(game, copy_map, game->start.y + 1,
			game->start.x + 1))
	{
		printf("Error\nMap is not enclosed:"
			"player can reach empty space at start (%d,%d).\n",
			game->start.x, game->start.y);
		return (free_array(copy_map), 0);
	}
	free_array(copy_map);
	return (1);
}
