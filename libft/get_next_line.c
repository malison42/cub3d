/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzots <vzots@student.42yerevan.am>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:18:45 by vzots             #+#    #+#             */
/*   Updated: 2026/01/15 21:15:52 by vzots            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free_line(char **line)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
}

static char	*ft_relload_line(char *line)
{
	int		len;
	int		i;
	char	*reload_line;

	len = 0;
	i = 0;
	if (!line)
		return (NULL);
	while (line[len] != '\n' && line[len])
		len++;
	if (!line[len])
		return (free(line), NULL);
	len++;
	reload_line = (char *)malloc(sizeof(char) * (ft_strlen(line) - len + 1));
	if (!reload_line)
		return (free(line), NULL);
	while (line[len + i])
	{
		reload_line[i] = line[len + i];
		i++;
	}
	reload_line[i] = '\0';
	if (reload_line[0] == '\0')
		return (free(line), free(reload_line), NULL);
	return (free(line), reload_line);
}

static char	*ft_get_res_line(char *line, char *res_line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!line)
		return (NULL);
	while (line[len] != '\n' && line[len])
		len++;
	if (line[len] == '\n')
		len++;
	if (len == 0)
		return (NULL);
	res_line = (char *)malloc((len + 1) * sizeof(char));
	if (!res_line)
		return (NULL);
	while (i < len)
	{
		res_line[i] = line[i];
		i++;
	}
	res_line[i] = '\0';
	return (res_line);
}

static char	*ft_get_line(int fd, char *line)
{
	ssize_t	read_byte;
	char	*buffer;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		ft_free_line(&line);
		return (NULL);
	}
	read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte < 0)
			return (free(buffer), free(line), NULL);
		if (read_byte == 0)
			break ;
		buffer[read_byte] = '\0';
		line = ft_strjoin2(line, buffer);
		if (!line)
			return (free(buffer), NULL);
		if (ft_strchr2(line, '\n'))
			break ;
	}
	return (free(buffer), line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*res_line;

	res_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		ft_free_line(&line);
		return (NULL);
	}
	line = ft_get_line(fd, line);
	res_line = ft_get_res_line(line, res_line);
	line = ft_relload_line(line);
	if (!res_line)
		ft_free_line(&line);
	return (res_line);
}
