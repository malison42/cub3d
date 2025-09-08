/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:05:18 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 18:05:20 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	res = ft_strlen(dest) + ft_strlen(src);
	i = ft_strlen(dest);
	if (i >= size)
	{
		return (ft_strlen(src) + size);
	}
	j = 0;
	while (src[j] != '\0' && i < size - 1)
	{
		dest[i] = src[j];
		++i;
		++j;
	}
	dest[i] = '\0';
	return (res);
}
