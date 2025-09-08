/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:06:23 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 18:06:24 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((char)c == 0)
		return (&((char *)s)[i]);
	while (s[i] != (char)c && i != 0)
		--i;
	if (s[i] == (char)c)
		return (&((char *)s)[i]);
	return (NULL);
}
