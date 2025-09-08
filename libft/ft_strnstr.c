/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:06:07 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 18:06:08 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (*to_find == '\0')
	{
		return ((char *)str);
	}
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while (to_find[j] == str[i + j] && str[i + j] != '\0' && i + j < len)
		{
			++j;
		}
		if (to_find[j] == '\0')
		{
			return (&((char *)str)[i]);
		}
		++i;
	}
	return (NULL);
}
