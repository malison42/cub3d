

#include "parsing_map.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		++i;
	}
	free(tokens);
}

void free_map_array(char **map, int rows_to_free)
{
	int i = 0;
	while (i < rows_to_free)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int		fill_config(t_parsing_var *game_var, char **token_config)
{
	char	*specificer;

	specificer = token_config[0];
	if (is_rgb_coloor(specificer))
		return (fill_rgb_color(specificer, game_var,token_config[1]));
	else if (is_path_texture(specificer))
			return (fill_path_texture(game_var, specificer, token_config[1]));
	else
		return (0);
}
int parsing_configs(int fd, t_parsing_var *game_var)
{
	char	**token_config;
	char	**config_specificers;

	config_specificers = get_specificers(1);
	while (game_var->flags_mask != 63)
	{
		token_config = get_token_config(fd);
		if (!token_config)
			{
				if (game_var->flags_mask != 63)
					printf("Не все конфиги найдены\n");
				return (free(config_specificers) ,0);
			}
		if (!validate_token_config(token_config, config_specificers))
			{ printf("Error 23\n"); return (free(config_specificers) ,free_tokens(token_config), 0);}
		if (!fill_config(game_var, token_config))
			{ printf("Error 3"); return (free(config_specificers) ,free_tokens(token_config), 0);}
		free_tokens(token_config);
	}
	free(config_specificers);
	return (1);
}


char 	*pad_line_end(char *line, int map_x)
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
int	is_node_null(t_list *tmp, t_list **map_list, char *line)
{
	if (!tmp || !tmp->content)
	{
		if (tmp)
			ft_lstdelone(tmp, free);
		free(line);
		ft_lstclear(map_list, free);
		return (1);
	}
	return (0);
}

t_list	*read_map_to_list(int fd, int *map_x)
{
	t_list	*map_list;
	t_list	*tmp;
	char	*line;

	map_list = NULL;
	line = get_line(fd);
	if (!line)
	{
		ft_putstr_fd("Error: Map not found\n", STDERR_FILENO);
		return (NULL);
	}
	while (line)
	{
		*map_x = ft_max(*map_x, ft_strlen(line));
		tmp = ft_lstnew((void *)ft_strdup(line));
		if (is_node_null(tmp, &map_list, line))
			return (NULL);
		ft_lstadd_back(&map_list, tmp);
		free(line);
		line = get_next_line(fd);
	}
	return (map_list);
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
		return(NULL);
	while (i < game->map_y)
	{
		map[i] = malloc(game->map_x + 1);
		if (!map[i])
			return(free_map_array(map, i), NULL);
		ft_strlcpy(map[i], (char *)tmp->content, ft_strlen((char *)tmp->content));
		map[i] = pad_line_end(map[i], game->map_x);
		//printf("%s\n", map[i]);
		tmp = tmp->next;
		++i;
	}
	map[i] = NULL;
	return(map);
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

int	check_start_pos(t_game *game, int y, char **map)
{
	int x;
	int	count_start_pos;

	count_start_pos = 0;
	x = 0;
	while (x < game->map_x)
	{
		if (ft_isset(map[y][x], "NSWE"))
		{
			// ? Возможно стоит добавить флаг а не использовать значении данное при иницилизации
			if (count_start_pos == 0 && game->start.view == 0) // !работет при иницилизации нулями
				set_player(&game->start, x, y, map[y][x]);
			count_start_pos++;
		}
		++x;
	}
	return (count_start_pos);
}

int validate_player_start(t_game *game, char **map)
{
	int	y;
	int	count_start_pos;

	count_start_pos = 0;
	y = 0;
	while (y < game->map_y)
	{
		count_start_pos += check_start_pos(game, y, map);
		if (count_start_pos > 1)
			return (0);
		++y;
	}
	if (count_start_pos != 1)
		return (0);
	game->player.x = game->start.x * SCALE + SCALE / 2;
	game->player.y = game->start.y * SCALE + SCALE / 2;
	game->player.direction = game->start.view;
	return (1);
}




int	is_valid_map(t_game *game, char **map)
{
	if (!is_valid_sym(game, map, VALID_CHARS))
		return (0);
	if (!validate_player_start(game, map))
		return (0);
	if (!is_mape_closure(game, map))
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
	ft_lstclear(&map_list, free); // освобождаем так как дальше лист не нужен
	if (!is_valid_map(game, map))
		return (NULL);
	return (map);
}

void	close_fd(int *fd, int i)
{
	while (i > -1)
	{
		close(fd[i]);
		i--;
	}
}

int	get_fd_texture(t_game *game, t_parsing_var *game_var)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("fd =%d", game->texture->fd_texture[i]);
		game->texture->fd_texture[i] = open(game_var->texturs[i].path_texture, O_RDONLY);
		printf("str =%s", game_var->texturs[i].path_texture);
		if (game->texture->fd_texture[i] == -1)
		{
			perror("file_texture");
			close_fd(game->texture->fd_texture, i - 1);
			return(0);
		}
		i++;
	}
	return(1);
}

void	ft_free_path_texture(t_parsing_var *game_var)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(game_var->texturs[i].path_texture);
		i++;
	}
}
int	parse_game_file(t_game *game, char *argv[], int argc)
{
	int	fd;
	t_parsing_var game_var;

	game_var.flags_mask = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return(perror("Open"), 0);
	if (!parsing_configs(fd, &game_var))
		return (close(fd), 0);
	if (!get_fd_texture(game, &game_var))
		return (close(fd), 0); // добавить perror
	game_var.map = parse_map(fd, game);
	if (!game_var.map)
		return(close(fd), 0);
	game->map = game_var.map;
	game->start = game_var.start;
	game->texture->ceiling = game_var.ceiling;
	game->texture->floor = game_var.floor;
	ft_free_path_texture(&game_var);
	close(fd);
	return (1);
}
