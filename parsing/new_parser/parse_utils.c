#include "parsing_map.h"


int	set_flags(char *specificer, t_config_flags *flags_mask)
{
	if (!ft_strcmp(specificer, "F"))
		*flags_mask |= FLAG_F;
	else if (!ft_strcmp(specificer, "C"))
		*flags_mask |= FLAG_C;
	else if (!ft_strcmp(specificer, "NO"))
		*flags_mask |= FLAG_NO;
	else if (!ft_strcmp(specificer, "WE"))
		*flags_mask |= FLAG_WE;
	else if (!ft_strcmp(specificer, "SO"))
		*flags_mask |= FLAG_SO;
	else if (!ft_strcmp(specificer, "EA"))
		*flags_mask |= FLAG_EA;
	else
		return (0);
	return (1);
}


int	is_rgb_coloor(char	*specificer)
{
	if (!ft_strcmp(specificer, "F"))
		return (1);
	else if (!ft_strcmp(specificer, "C"))
		return (1);
	return (0);
}

int	is_path_texture(char *specificer)
{
	if (!ft_strcmp(specificer, "NO"))
		return (1);
	else if (!ft_strcmp(specificer, "SO"))
		return (1);
	else if (!ft_strcmp(specificer, "WE"))
		return (1);
	else if (!ft_strcmp(specificer, "EA"))
		return (1);
	return (ERROR);
}
