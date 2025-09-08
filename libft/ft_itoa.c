/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:01:09 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 18:01:14 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count(int n)
{
	size_t	sz;

	if (n == 0)
		return (1);
	sz = 0;
	if (n < 0)
	{
		++sz;
	}
	while (n != 0)
	{
		n = n / 10;
		++sz;
	}
	return (sz);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		sign;
	size_t	sz;
	char	c;

	sz = count(n);
	number = malloc(sz + 1);
	if (number == NULL)
		return (NULL);
	if (n == 0)
		number[0] = '0';
	sign = 1;
	if (n < 0)
		sign = -1;
	number[sz] = '\0';
	while (n != 0)
	{
		--sz;
		c = (n % 10) * sign + '0';
		number[sz] = c;
		n = n / 10;
	}
	if (sign < 0)
		number[0] = '-';
	return (number);
}
