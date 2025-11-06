#include "../cub.h"

char	**parse_map(int fd, t_game *game)
{
	char	**map;
	t_list	*map_list;
	char	*line;
	int		i;
	t_list	*tmp;
	
	map_list = NULL;
	line = get_line(fd);
	if (!line)
	{
		ft_putstr_fd("wrong map", STDERR_FILENO);
		return (NULL);
	}
	game->map_x = 0;
	while (line)
	{
		game->map_x = ft_max(game->map_x, ft_strlen(line));
		ft_lstadd_back(&map_list, ft_lstnew((void *)ft_strdup(line)));
		free(line);
		line = get_next_line(fd);
	}
	game->map_y = ft_lstsize(map_list);
	map = malloc(sizeof(char *) * (game->map_y + 1));
	i = 0;
	tmp = map_list;
	while (i < game->map_y)
	{
		map[i] = malloc(game->map_x + 1);
		ft_bzero(map[i], game->map_x + 1);
		ft_strlcpy(map[i], (char *)tmp->content, ft_strlen((char *)tmp->content));
		printf("%s\n", map[i]);
		tmp = tmp->next;
		++i;
	}
	map[i] = NULL;
	return (map);
}

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

void	parse_player(t_game *game)
{
	int	i;
	int j;
	
	i = 0;
	while (i < game->map_x)
	{
		j = 0;
		while (j < game->map_y)
		{
			if (ft_isset(game->map[j][i], "NSWE"))
				set_player(&game->start, i, j, game->map[j][i]);
			++j;
		}
		++i;
	}
	game->player.x = game->start.x * SCALE + SCALE / 2;
	game->player.y = game->start.y * SCALE + SCALE / 2;
	game->player.direction = game->start.view;
}

int	parse_data(char *filepath, t_game *game)
{
	int			fd;
	t_textures	*tex;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (perror(filepath), 1);
	(void)game;
	tex = malloc(sizeof(t_textures));
	if (!tex)
		return (perror("malloc"), close(fd), 1);
	parse_textures(fd, tex);
	game->texture = tex;
	game->map = parse_map(fd, game);
	parse_player(game);
	return (0);
}
