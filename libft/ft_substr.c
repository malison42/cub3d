/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:06:45 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 18:06:46 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	n;
	size_t	sz;
	char	*sub;

	if (s == NULL)
		return (NULL);
	n = ft_strlen(s);
	if (start >= n || len == 0)
		sz = 0;
	else if (start + len > n)
		sz = n - start;
	else
		sz = len;
	sub = malloc(sz + 1);
	if (sub == NULL)
		return (NULL);
	n = 0;
	while (n < sz)
	{
		sub[n] = s[start + n];
		++n;
	}
	sub[n] = '\0';
	return (sub);
}
