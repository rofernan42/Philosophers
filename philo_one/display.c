/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:50:25 by rofernan          #+#    #+#             */
/*   Updated: 2020/09/10 17:50:27 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*display_action(int n)
{
	if (n == 1)
		return (" has taken a fork\n");
	else if (n == 2)
		return (" is eating\n");
	else if (n == 3)
		return (" is sleeping\n");
	else if (n == 4)
		return (" is thinking\n");
	else if (n == 5)
		return (" has died\n");
	return ("\tnumber of meals reached\n");
}

void		display(t_philo *philo, int n)
{
	char *str;

	pthread_mutex_lock(&philo->param->disp);
	if (!philo->param->stop)
	{
		str = display_action(n);
		ft_putnbr_fd(timestamp(philo->param->init_time), 1);
		if (n != 6)
		{
			write(1, "\tphilo. ", 8);
			ft_putnbr_fd(philo->i + 1, 1);
		}
		write(1, str, ft_strlen(str));
		str = NULL;
		if (n == 5 || n == 6)
		{
			philo->param->stop = 1;
			return ;
		}
	}
	pthread_mutex_unlock(&philo->param->disp);
}
