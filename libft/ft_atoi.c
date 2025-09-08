/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:58:47 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 17:58:52 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	number;
	int	i;
	int	sign;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		++i;
	}
	number = 0;
	while (ft_isdigit(str[i]))
	{
		number = (sign * number * 10 + str[i] - '0') * sign;
		++i;
	}
	return (number);
}
