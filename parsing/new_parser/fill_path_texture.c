#include "parsing_map.h"

int	get_sunny_side(char *specificer)
{
	if (!ft_strcmp(specificer, "NO"))
		return (NORTH);
	else if (!ft_strcmp(specificer, "SO"))
		return (SOUTH);
	else if (!ft_strcmp(specificer, "WE"))
		return (WEST);
	else if (!ft_strcmp(specificer, "EA"))
		return (EAST);
	return (ERROR);
}

int	fill_path_texture(t_parsing_var *game_var, char	*specificer,
	char *path_texture)
{
	int	sunny_side;

	sunny_side = get_sunny_side(specificer);
	if (sunny_side == ERROR)
		return (0);
	if (!uniqueness_verification(game_var->flags_mask, specificer))
		return (0);
	if (!set_flags(specificer, &game_var->flags_mask))
		return (0);
	game_var->texturs[sunny_side].path_texture = ft_strdup(path_texture);
	if (!game_var->texturs[sunny_side].path_texture)
		return (0);
	game_var->texturs[sunny_side].side = sunny_side;
	return (1);
}
