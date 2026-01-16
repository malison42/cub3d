#include "parsing_map.h"

int	is_valid_sym(t_game *game, char **map, char *set)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_y)
	{
		x = 0;
		while (x < game->map_x)
		{
			if (!ft_isset(map[y][x], set))
			{
				printf("Error\nInvalid symbol in map: %c\n", map[y][x]);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_for_duplicate(t_config_flags flags_mask,
	t_config_flags flag, char *specificer)
{
	if (flags_mask & flag)
	{
		ft_putstr_fd("Error\nDuplicate config item: ", STDERR_FILENO);
		ft_putstr_fd(specificer, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	uniqueness_verification(t_config_flags flags_mask, char *specificer)
{
	if (!ft_strcmp(specificer, "F"))
		return (check_for_duplicate(flags_mask, FLAG_F, specificer));
	else if (!ft_strcmp(specificer, "C"))
		return (check_for_duplicate(flags_mask, FLAG_C, specificer));
	else if (!ft_strcmp(specificer, "NO"))
		return (check_for_duplicate(flags_mask, FLAG_NO, specificer));
	else if (!ft_strcmp(specificer, "WE"))
		return (check_for_duplicate(flags_mask, FLAG_WE, specificer));
	else if (!ft_strcmp(specificer, "SO"))
		return (check_for_duplicate(flags_mask, FLAG_SO, specificer));
	else if (!ft_strcmp(specificer, "EA"))
		return (check_for_duplicate(flags_mask, FLAG_EA, specificer));
	return (0);
}

char	*find_config(const char *str, char **config_specificers)
{
	int	i;

	i = 0;
	while (config_specificers[i])
	{
		if (!ft_strcmp(str, config_specificers[i]))
			return (config_specificers[i]);
		i++;
	}
	return (NULL);
}

int	validate_token_config(char **token_config, char **config_specificers)
{
	if (!find_config(token_config[0], config_specificers))
	{
		printf("Error\nInvalid config specificer: %s\n", token_config[0]);
		return (0);
	}
	if (token_config[2])
	{
		printf("Error\nUnnecessary token: %s\n", token_config[2]);
		return (0);
	}
	return (1);
}
