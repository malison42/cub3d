

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
		// printf("fd =%d", game->texture->fd_texture[i]);
		// int fd = open(game_var->texturs[i].path_texture, O_RDONLY);
		// game->texture->fd_texture[i] = fd;
		// printf("str =%s", game_var->texturs[i].path_texture);
		game->texture->side[i] = \
		create_texture(game, game_var->texturs[i].path_texture);
		// free(game_var->texturs[i].path_texture);
		if (!game->texture->side[i])
		{
			// perror("file_texture");
			//close_fd(game->texture->fd_texture, i - 1);
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
		if (game_var->texturs[i].path_texture)
			free(game_var->texturs[i].path_texture);
		i++;
	}
}
// int	parse_game_file(t_game *game, char *argv[], int argc)
int	parse_game_file(t_game *game, int fd)
{
	// int	fd;
	t_parsing_var game_var;

	// if (argc != 2)
	// {
	// 	ft_putstr_fd("Error\nEnter map filename", STDERR_FILENO);
	// 	return (0);
	// }
	// if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
	// {
	// 	ft_putstr_fd("Error\n"
	// 				 "File has to be with the .cub extension", STDERR_FILENO);
	// 	return (0);
	// }
	game_var.flags_mask = 0;
	// fd = open(argv[1], O_RDONLY);
	// if (fd == -1)
	// 	return(perror("Open"), 0);
	if (!parsing_configs(fd, &game_var))
		return (close(fd), ft_free_path_texture(&game_var),0);
	if (!get_fd_texture(game, &game_var))
		return (close(fd), ft_free_path_texture(&game_var),0); // добавить perror
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
