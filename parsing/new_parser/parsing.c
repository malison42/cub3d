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

void	free_map_array(char **map, int rows_to_free)
{
	int	i;

	i = 0;
	while (i < rows_to_free)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	get_fd_texture(t_game *game, t_parsing_var *game_var)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture->side[i]
			= create_texture(game, game_var->texturs[i].path_texture);
		if (!game->texture->side[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_free_path_texture(t_parsing_var *game_var)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("free path texture: %s\n", game_var->texturs[i].path_texture);
		if (game_var->texturs[i].path_texture)
		{
			free(game_var->texturs[i].path_texture);
			game_var->texturs[i].path_texture = NULL;
		}
		i++;
	}
}

// int	parse_game_file(t_game *game, char *argv[], int argc)
int	parse_game_file(t_game *game, int fd)
{
	t_parsing_var	game_var;

	ft_bzero(&game_var, sizeof(t_parsing_var));
	game_var.flags_mask = 0;
	if (!parsing_configs(fd, &game_var))
	{
		get_next_line(-1);
		return (close(fd), ft_free_path_texture(&game_var), 0);
	}
	if (!get_fd_texture(game, &game_var))
		return (close(fd), ft_free_path_texture(&game_var), 0);
	game_var.map = parse_map(fd, game);
	if (!game_var.map)
	{
		ft_free_path_texture(&game_var);
		return (close(fd), 0);
	}
	game->map = game_var.map;
	game->start = game_var.start;
	game->texture->ceiling = game_var.ceiling;
	game->texture->floor = game_var.floor;
	ft_free_path_texture(&game_var);
	close(fd);
	return (1);
}
