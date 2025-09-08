/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:58:47 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 17:58:52 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit_hex(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	if (c <= 'f' && c >= 'a')
		return (1);
	if (c <= 'F' && c >= 'A')
		return (1);
	return (0);
}

unsigned int	ft_atoi_hex(const char *str)
{
	unsigned int	number;
	int				i;
	int				digit;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	number = 0;
	while (ft_isdigit_hex(str[i]))
	{
		if (str[i] <= '9' && str[i] >= '0')
			digit = str[i] - '0';
		else if (str[i] <= 'f' && str[i] >= 'a')
			digit = str[i] - 'a' + 10;
		else
			digit = str[i] - 'A' + 10;
		number = number * 16 + digit;
		++i;
	}
	return (number);
}
