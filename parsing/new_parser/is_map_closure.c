#include "parsing_map.h"

void free_array(char **array)
{
	int i = 0;

	if (!array)
		return;
	while (array[i]) // Остановка по NULL-терминатору
	{
		free(array[i]);
		i++;
	}
	free(array); // Освобождение самого массива указателей
}

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
	int wrapped_cols;

	wrapped_cols = game->map_x + 2;
	wrapped_line= malloc(sizeof(char) * (wrapped_cols + 1));
	if (!wrapped_line)
		return (NULL);
	if (i == 0 || i ==  game->map_y + 1)
		ft_memset(wrapped_line, '#', wrapped_cols);
	else
	{
		wrapped_line[0] = '#';
		ft_strlcpy(wrapped_line + 1, map[i - 1], game->map_x + 1);
		wrapped_line[wrapped_cols - 1] = '#';
	}
	wrapped_line[wrapped_cols] = '\0';
	return (wrapped_line);
}

char **create_wrapped_map(t_game *game, char **map)
{
	char	**map_wrapped;
	int		i;
	int		wrapped_rows;

	i = 0;
	wrapped_rows = game->map_y + 2;
	map_wrapped = malloc(sizeof(char *) * (wrapped_rows + 1)); // +1 для NULL-терминатора
	if (!map_wrapped)
		return (NULL);
	while (i < wrapped_rows)
	{
		map_wrapped[i] = create_wrapped_cols(game, map, i);
		if (!map_wrapped[i])
			return(free_map_array(map_wrapped, i), NULL);
		i++;
	}
	map_wrapped[wrapped_rows] = NULL;
	return (map_wrapped);
}

int	flood_fill_accessibility(t_game *game,char **map_wrapped, int y, int x)
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
	if (!flood_fill_accessibility(game, map_wrapped, y + 1, x) || // Вниз
		!flood_fill_accessibility(game, map_wrapped, y - 1, x) || // Вверх
		!flood_fill_accessibility(game, map_wrapped, y, x + 1) || // Вправо
		!flood_fill_accessibility(game, map_wrapped, y, x - 1))   // Влево
	{
		return (0);
	}
	return (1);
}

int	flood_fill_closure(t_game *game,char **map_wrapped, int y, int x)
{
	char	curent_char;

	if (y < 0 || x < 0 || x >= (game->map_x + 3) || y >= (game->map_y + 3))
		return (1);
	curent_char = map_wrapped[y][x];
	if (curent_char == '0' || ft_isset(curent_char, "NSWE") || curent_char == ' ')
		return (0);
	if (curent_char == '1' || curent_char == 'F')
		return (1);
	if (curent_char == '#')
		map_wrapped[y][x] = 'F';
	else
		return (0);
	if (!flood_fill_closure(game, map_wrapped, y + 1, x) || // Вниз
		!flood_fill_closure(game, map_wrapped, y - 1, x) || // Вверх
		!flood_fill_closure(game, map_wrapped, y, x + 1) || // Вправо
		!flood_fill_closure(game, map_wrapped, y, x - 1))   // Влево
	{
		return (0);
	}
	return (1);
}

int check_all_reachable( char **map_wrapped)
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
				return(0);
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
	if (!flood_fill_closure(game, copy_map, 0 , 0))
		return (free_array(copy_map), 0);
	if (!flood_fill_accessibility(game, copy_map, game->start.y + 1 , game->start.x + 1))
		return (free_array(copy_map), 0);
	if (!check_all_reachable(copy_map))
		return (free_array(copy_map), 0);
	free_array(copy_map);
	return (1);
}
