/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:59:11 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 17:59:12 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	vol;

	vol = count * size;
	if (vol == 0)
		vol = 1;
	ptr = malloc(vol);
	if (ptr != NULL)
		ft_bzero(ptr, vol);
	return (ptr);
}
