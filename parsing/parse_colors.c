#include "../cub.h"

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

	if (!str)
		return (-1);
	channel = 0;
	while (ft_isdigit(*str))
	{
		if (channel < 0 || channel > 255)
			return (-1);
		channel = channel * 10 + (*str) - '0';
		str++;
	}
	if (*str)
		return (-1);
	return (channel);
}

t_color	parse_color(char ***lines, char *specifier)
{
	char	**col;
	t_color	color;
	int		i;

	i = 0;
	while (i < 6 && ft_strcmp(lines[i][0], specifier))
		++i;
	if (i == 6)
		return (ft_putstr_fd(MESSAGE_SCENE_NOT_VALID, STDERR_FILENO), new_color(-1, -1, -1));
	col = ft_split(lines[i][1], ',');
	if (!col)
		return (perror("malloc"), new_color(-1, -1, -1));
	color = new_color(get_col(col[0]), get_col(col[1]), get_col(col[2]));

	if (color.r < 0 || color.g < 0 || color.b < 0 || col[3])
	{
		ft_putstr_fd(MESSAGE_SCENE_NOT_VALID, STDERR_FILENO);
		return (new_color(-1, -1, -1));
	}
		free_tokens(col);
	return (color);
}


