/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 13:33:15 by rofernan          #+#    #+#             */
/*   Updated: 2020/09/07 13:33:22 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, &*s++, 1);
}

int		print_error(char *s)
{
	ft_putstr_fd(s, 1);
	return (1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int temp;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		temp = -n;
	}
	else
		temp = n;
	if (temp < 10)
		ft_putchar_fd(temp + '0', fd);
	else
	{
		ft_putnbr_fd(temp / 10, fd);
		ft_putchar_fd(temp % 10 + '0', fd);
	}
}

int		ft_atoi(const char *str)
{
	int			i;
	long int	nb;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	if (str)
	{
		while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t' \
		|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
			i++;
		if (str[i] == '-')
			sign = -1;
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10 + str[i++] - '0';
	}
	return (sign * nb);
}
