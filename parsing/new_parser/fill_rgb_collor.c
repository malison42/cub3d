#include "parsing_map.h"

t_color	new_color(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

int	get_col(char *str)
{
	int	channel;

	if (!str || !*str)
		return (-1);
	channel = 0;
	while (ft_isdigit(*str))
	{
		if (channel > 25)
			return (-1);
		channel = channel * 10 + (*str) - '0';
		if (channel > 255)
			return (-1);
		str++;
	}
	if (*str)
		return (-1);
	return (channel);
}

t_color	parse_color(char *token_config)
{
	char	**col;
	t_color	color;

	col = ft_split(token_config, ',');
	if (!col)
		return (perror("malloc"), new_color(-1, -1, -1));
	color = new_color(get_col(col[0]), get_col(col[1]), get_col(col[2]));
	if (color.r < 0 || color.g < 0 || color.b < 0 || col[3])
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(MESSAGE_SCENE_NOT_VALID, STDERR_FILENO);
		return (free_tokens(col), new_color(-1, -1, -1));
	}
	free_tokens(col);
	return (color);
}

int	set_rgb(t_parsing_var *game_var, t_color temp_color, char *specificer)
{
	if (!ft_strcmp(specificer, "F"))
		game_var->floor = temp_color;
	else if (!ft_strcmp(specificer, "C"))
		game_var->ceiling = temp_color;
	else
		return (0);
	return (1);
}

int	fill_rgb_color(char *specificer, t_parsing_var *game_var, char *rgb_collors)
{
	t_color	temp_color;

	if (!uniqueness_verification(game_var->flags_mask, specificer))
		return (0);
	temp_color = parse_color(rgb_collors);
	if (temp_color.r == -1)
		return (0);
	if (!set_flags(specificer, &game_var->flags_mask))
		return (0);
	if (!set_rgb(game_var, temp_color, specificer))
		return (0);
	return (1);
}
