#include "parsing_map.h"

int	fill_config(t_parsing_var *game_var, char **token_config)
{
	char	*specificer;

	specificer = token_config[0];
	if (is_rgb_coloor(specificer))
		return (fill_rgb_color(specificer, game_var, token_config[1]));
	else if (is_path_texture(specificer))
	{
		if (ft_strcmp(&token_config[1][ft_strlen(token_config[1]) - 4], ".xpm"))
		{
			printf("Error\nTexture file has to be with the "
				".xpm extension: %s\n", token_config[1]);
			return (0);
		}
		return (fill_path_texture(game_var, specificer, token_config[1]));
	}
	else
		return (0);
}

static int	process_token_config(int fd, t_parsing_var *game_var,
			char **config_specificers)
{
	char	**token_config;

	token_config = get_token_config(fd);
	if (!token_config)
		return (-1);
	if (!validate_token_config(token_config, config_specificers))
	{
		free_tokens(token_config);
		return (-2);
	}
	if (!fill_config(game_var, token_config))
	{
		free_tokens(token_config);
		return (-3);
	}
	free_tokens(token_config);
	return (0);
}

int	parsing_configs(int fd, t_parsing_var *game_var)
{
	char	**config_specificers;
	int		res;

	config_specificers = get_specificers(1);
	while (game_var->flags_mask != 63)
	{
		res = process_token_config(fd, game_var, config_specificers);
		if (res == -1)
		{
			if (game_var->flags_mask != 63)
				printf("Не все конфиги найдены\n");
			free(config_specificers);
			return (0);
		}
		if (res < 0)
		{
			if (game_var->flags_mask != 63)
				printf("Не все конфиги найдены\n");
			free(config_specificers);
			return (0);
		}
	}
	free(config_specificers);
	return (1);
}

// int	parsing_configs(int fd, t_parsing_var *game_var)
// {
// 	char	**token_config;
// 	char	**config_specificers;

// 	config_specificers = get_specificers(1);
// 	while (game_var->flags_mask != 63)
// 	{
// 		token_config = get_token_config(fd);
// 		if (!token_config)
// 		{
// 			if (game_var->flags_mask != 63)
// 				printf("Не все конфиги найдены\n");
// 			return (free(config_specificers), 0);
// 		}
// 		if (!validate_token_config(token_config, config_specificers))
// 		{
// 			if (game_var->flags_mask != 63)
// 			{
// 				printf("Не все конфиги найдены\n");
// 				free_tokens(token_config);
// 				return (free(config_specificers), 0);
// 			}
// 			return (free(config_specificers), free_tokens(token_config), 0);
// 		}
// 		if (!fill_config(game_var, token_config))
// 			return (free(config_specificers), free_tokens(token_config), 0);
// 		free_tokens(token_config);
// 	}
// 	if (game_var->flags_mask != 63)
// 		printf("Не все конфиги найдены\n");
// 	free(config_specificers);
// 	return (1);
// }
