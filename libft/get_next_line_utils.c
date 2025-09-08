/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:45:26 by tskubits          #+#    #+#             */
/*   Updated: 2025/02/01 16:45:28 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// size_t	ft_strlen(char *s)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s && s[len] != '\0')
// 		++len;
// 	return (len);
// }

size_t	delimiter(char *str)
{
	size_t	d;

	if (!str)
		return (0);
	d = 0;
	while (str[d] != '\n' && str[d] != '\0')
	{
		++d;
	}
	if (str[d] == '\n')
	{
		++d;
	}
	return (d);
}

char	*ft_join(char *s1, char *s2, size_t start, size_t finish)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = malloc(ft_strlen(s1) + finish - start + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0' )
	{
		str[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2 && j + start < finish)
	{
		str[i + j] = s2[j + start];
		++j;
	}
	str[i + j] = '\0';
	if (s1)
	{
		free(s1);
	}
	return (str);
}

char	*ft_clear(char *line, char *rem)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (rem)
	{
		free(rem);
		rem = NULL;
	}
	return (NULL);
}
