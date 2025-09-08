/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:04:46 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 18:04:47 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if ((char)c == 0)
		return (&((char *)s)[ft_strlen(s)]);
	i = 0;
	while (s[i] != (char)c && s[i] != '\0')
		++i;
	if (s[i] != '\0')
		return (&((char *)s)[i]);
	return (NULL);
}
