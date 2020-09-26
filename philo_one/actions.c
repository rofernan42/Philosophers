/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 18:39:37 by rofernan          #+#    #+#             */
/*   Updated: 2020/09/12 18:39:39 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_fork(t_philo *ph)
{
	pthread_mutex_lock(&ph->param->forks[ph->l_fork]);
	display(ph, 1);
	pthread_mutex_lock(&ph->param->forks[ph->r_fork]);
	display(ph, 1);
}

void	eat(t_philo *ph)
{
	ph->is_eating = 1;
	display(ph, 2);
	ph->last_eaten = gettime();
	pthread_mutex_lock(&ph->p_eat);
	usleep(ph->param->t_eat * 1000);
	ph->is_eating = 0;
	ph->eat_count++;
	pthread_mutex_unlock(&ph->p_eat);
}

void	leave_fork(t_philo *ph)
{
	pthread_mutex_unlock(&ph->param->forks[ph->l_fork]);
	pthread_mutex_unlock(&ph->param->forks[ph->r_fork]);
}

void	sleeping(t_philo *ph)
{
	display(ph, 3);
	usleep(ph->param->t_sleep * 1000);
}
