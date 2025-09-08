/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tskubits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:04:14 by tskubits          #+#    #+#             */
/*   Updated: 2025/01/26 18:04:16 by tskubits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print(int number, int fd)
{
	char		c;
	long int	i;

	i = 10;
	while (number / i > 0)
	{
		i *= 10;
	}
	i /= 10;
	while (i > 1)
	{
		c = number / i + 48;
		write(fd, &c, 1);
		number = number % i;
		i /= 10;
	}
	c = number + 48;
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	int			number;

	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		number = nb;
		if (nb < 0)
		{
			write(fd, "-", 1);
			number *= -1;
		}
		ft_print(number, fd);
	}
}
