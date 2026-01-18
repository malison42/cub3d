#include "parsing_map.h"
//TODO remove start
int	set_player(t_player *start, int x, int y, char view)
{
	start->x = x;
	start->y = y;
	if (view == 'N')
		start->view = 3 * M_PI_2;
	else if (view == 'S')
		start->view = M_PI_2;
	else if (view == 'E')
		start->view = 0;
	else if (view == 'W')
		start->view = M_PI;
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_start_pos(t_game *game, int y, char **map)
{
	int	x;
	int	count_start_pos;

	count_start_pos = 0;
	x = 0;
	while (x < game->map_x)
	{
		if (ft_isset(map[y][x], "NSWE"))
		{
			if (count_start_pos == 0)
			{
				printf("X = %d Y = %d\n", x, y);
				set_player(&game->start, x, y, map[y][x]);
			}
			count_start_pos++;
		}
		++x;
	}
	return (count_start_pos);
}

int	validate_player_start(t_game *game, char **map)
{
	int	y;
	int	count_start_pos;

	count_start_pos = 0;
	y = 0;
	while (y < game->map_y)
	{
		count_start_pos += check_start_pos(game, y, map);
		if (count_start_pos > 1)
		{
			printf("Error\nMap has multiple starting positions.\n");
			return (0);
		}
		++y;
	}
	if (count_start_pos != 1)
	{
		printf("Error\nMap has no starting position.\n");
		return (0);
	}
	game->player.x = game->start.x + 0.5;
	game->player.y = game->start.y + 0.5;
	game->player.direction = game->start.view;
	return (1);
}
