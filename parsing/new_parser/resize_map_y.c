#include "parsing_map.h"

void	resize_map_y(t_game *game, char **map)
{
	int	counter;
	int iter;
	
	counter = 0;
	while (counter < game->map_y && !is_empty_line(map[counter]))
		++counter;
	iter = game->map_y;
	while (iter > counter)
	{
		--iter;
		free(map[iter]);
		map[iter] = NULL;
	}
//	printf("counter %d  map_y %d  iter %d\n", counter, game->map_y, iter);
	game->map_y = counter;
}