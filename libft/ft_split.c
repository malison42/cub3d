/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:04:39 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 18:04:41 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_word(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str && str[i] != '\0')
	{
		while (str[i] == c)
			++i;
		if (str[i] != '\0')
			++count;
		while (str[i] != '\0' && str[i] != c)
			++i;
	}
	return (count);
}

char	*copy(char const *str, char c)
{
	int		i;
	int		sz;
	char	*line;

	i = 0;
	while (str[i] != '\0' && str[i] == c)
		++i;
	sz = 0;
	while (str[i + sz] != '\0' && str[i + sz] != c)
	{
		++sz;
	}
	line = (char *)malloc(sz + 1);
	if (line == NULL)
		return (NULL);
	sz = 0;
	while (str[i + sz] != '\0' && str[i + sz] != c)
	{
		line[sz] = str[i + sz];
		++sz;
	}
	line[sz] = '\0';
	return (line);
}

char	**clear(char **lines, int i)
{
	while (i >= 0)
	{
		free(lines[i]);
		--i;
	}
	free(lines);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	int		sz;
	int		i;
	char	**lines;

	sz = count_word(str, c);
	lines = (char **)malloc((sz + 1) * sizeof(char *));
	if (lines == NULL)
		return (NULL);
	i = 0;
	while (i < sz)
	{
		lines[i] = copy(str, c);
		if (lines[i] == NULL)
			return (clear(lines, i));
		while (*str != '\0' && *str == c)
			str += 1;
		str = str + ft_strlen(lines[i]);
		++i;
	}
	lines[i] = NULL;
	return (lines);
}
