/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:03:42 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 18:03:43 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	if (len == 0)
		return (b);
	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		++i;
	}
	return (b);
}
