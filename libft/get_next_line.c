/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:45:19 by tskubits          #+#    #+#             */
/*   Updated: 2025/02/01 16:45:21 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	join_rem(char **line, char **rem)
{
	size_t	d;
	size_t	sz_rem;
	char	*tmp;

	d = delimiter(*rem);
	*line = ft_join(*line, *rem, 0, d);
	if (*line == NULL)
		return (-1);
	sz_rem = ft_strlen(*rem);
	tmp = *rem;
	*rem = ft_join(NULL, *rem, d, sz_rem);
	if (tmp)
		free(tmp);
	if (*rem == NULL)
		return (-1);
	if (ft_strlen(*rem) == 0)
	{
		free(*rem);
		*rem = NULL;
	}
	return (1);
}

int	join_buf(char **line, char **rem, int fd)
{
	size_t	d;
	int		ret;
	char	buf[BUFFER_SIZE + 1];

	ret = read(fd, buf, BUFFER_SIZE);
	while (ret)
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		d = delimiter(buf);
		*line = ft_join(*line, buf, 0, d);
		if (*line == NULL)
			return (-1);
		if (buf[d - 1] == '\n')
		{
			*rem = ft_join(*rem, buf, d, (size_t)ret);
			if (!(*rem))
				return (-1);
			return (0);
		}
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*line;
	int			res;

	line = NULL;
	if (ft_strlen(rem))
	{
		res = join_rem(&line, &rem);
		if (res < 0)
			return (ft_clear(line, rem));
		if (line[ft_strlen(line) - 1] == '\n')
			return (line);
	}
	res = join_buf(&line, &rem, fd);
	if (res < 0)
		return (ft_clear(line, rem));
	if (ft_strlen(rem) == 0)
	{
		free(rem);
		rem = NULL;
	}
	if (res == 0)
		return (line);
	return (NULL);
}
