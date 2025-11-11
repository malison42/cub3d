
#include "parsing_map.h"

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

int	get_map_x(char *line, int map_x)
{
	int	line_length;

	line_length = ft_strlen(line);
	if (line_length > 0 && line[line_length - 1] == '\n')
	{
		line[line_length - 1] = '\0';
		line_length--;
	}
	return (ft_max(map_x, line_length));
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
		*map_x = get_map_x(line, *map_x);
		tmp = ft_lstnew((void *)ft_strdup(line));
		if (is_node_null(tmp, &map_list, line))
			return (NULL);
		ft_lstadd_back(&map_list, tmp);
		free(line);
		line = get_next_line(fd);
	}
	return (map_list);
}

