/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <tskubits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:37:34 by tskubits          #+#    #+#             */
/*   Updated: 2025/07/20 23:37:36 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	len;
	char	*dup;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	if (n < len)
		len = n;
	dup = (char *)malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dup[i] = src[i];
		++i;
	}
	dup[i] = '\0';
	return (dup);
}
