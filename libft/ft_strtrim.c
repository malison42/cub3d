/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:06:34 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 18:06:35 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		++i;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*trim;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (in_set(s1[i], set))
		++i;
	start = i;
	i = ft_strlen(s1) - 1;
	while (in_set(s1[i], set) && i != 0)
		--i;
	end = i;
	if (start > end)
		i = 0;
	else
		i = end - start + 1;
	trim = malloc(i + 1);
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, &s1[start], i + 1);
	return (trim);
}
