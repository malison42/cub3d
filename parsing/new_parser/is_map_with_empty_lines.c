// #include "parsing_map.h"

// int is_empty_line(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] != '#')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	find_first_empty_line(t_game *game, int start, char **map)
// {
// 	int	i;

// 	i = start;
// 	while (i < game->map_y)
// 	{
// 		if (is_empty_line(map[i]))
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// int	find_first_non_empty_line(t_game *game, int start, char **map)
// {
// 	int	i;

// 	i = start;
// 	while (i < game->map_y)
// 	{
// 		if (!is_empty_line(map[i]))
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// int	get_new_map_x(t_game *game, char **map)
// {
// 	int	i;
// 	int	x;
// 	int	x_2;

// 	x = 0;
// 	i = 0;
// 	x_2 = 0;
// 	while (i < game->map_y)
// 	{
// 		while (ft_isspace(map[i][x_2]))
// 			x_2++;
// 		while (map[i][x_2])
// 		{
// 			if (map[i][x_2] != '#' )
// 				x_2++;
// 			else
// 				break ;
// 		}
// 		if (x_2 > x)
// 			x = x_2;
// 		i++;
// 	}
// 	return (x);
// }

// int	resize_map_x(t_game *game, char **map)
// {
// 	int	i;
// 	int	x;

// 	i = 0;
// 	x = get_new_map_x(game, map);
// 	while (i < game->map_y)
// 	{
// 		map[i][x] = '\0';
// 		i++;
// 	}
// 	return (x);
// }

// void	resize_map(t_game *game, char **map, int first_empty)
// {
// 	int	i;

// 	i = first_empty;
// 	while (i < game->map_y)
// 	{
// 		if (is_empty_line(map[i]))
// 		{
// 			free(map[i]);
// 			map[i] = NULL;
// 		}
// 		i++;
// 	}
// 	game->map_y = first_empty;
// 	game->map_x = resize_map_x(game, map);
// }

// int	is_map_with_empty_lines(t_game *game, char **map)
// {
// 	int	first_non_empty_after;
// 	int	first_empty;


// 	first_empty = find_first_empty_line(game, 0, map);
// 	if (first_empty == -1)
// 		return (0);
// 	printf("first_empty: %d\n", first_empty);
// 	first_non_empty_after = find_first_non_empty_line(game,
// 			first_empty + 1, map);
// 	printf("first_non_empty_after: %d\n", first_non_empty_after);
// 	if (first_non_empty_after != -1)
// 	{
// 		printf("Error\nMap contains empty line\n");
// 		return (1);
// 	}
// 	printf("map_x: %d\n", game->map_x);
// 	printf("map_y: %d\n", game->map_y);
// 	// resize_map(game, map, first_empty);
// 	// // game->map_x = 34 ;
// 	printf("Map resized map x: %d\n", game->map_x);
// 	printf("Map resized map y: %d\n", game->map_y);
// 	return (0);
// }
