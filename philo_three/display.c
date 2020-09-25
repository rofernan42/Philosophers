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

static void	display_action(int n)
{
	if (n == 1)
		ft_putstr_fd(" has taken a fork\n", 1);
	else if (n == 2)
		ft_putstr_fd(" is eating\n", 1);
	else if (n == 3)
		ft_putstr_fd(" is sleeping\n", 1);
	else if (n == 4)
		ft_putstr_fd(" is thinking\n", 1);
	else if (n == 5)
		ft_putstr_fd(" has died\n", 1);
	else if (n == 6)
		ft_putstr_fd("\tnumber of meals reached\n", 1);
}

void		display(t_philo *philo, int n)
{
	sem_wait(philo->param->disp);
	if (!philo->param->stop)
	{
		ft_putnbr_fd(timestamp(philo->param->init_time), 1);
		if (n != 6)
		{
			ft_putstr_fd("\tphilo. ", 1);
			ft_putnbr_fd(philo->i + 1, 1);
		}
		display_action(n);
		if (n == 5 || n == 6)
		{
			philo->param->stop = 1;
			//printf("philo %d  eat_count %d\n", philo->i+1, philo->eat_count);
			exit(0);
		}
	}
	sem_post(philo->param->disp);
}
