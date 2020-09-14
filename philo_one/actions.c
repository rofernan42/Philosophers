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

static void	take_fork(t_philo *ph)
{
	pthread_mutex_lock(&ph->param->forks[ph->i]);
	//pthread_mutex_lock(&ph->param->forks[ph->l_fork]);
	display(ph, 1);
	pthread_mutex_lock(&ph->param->forks[(ph->i + 1) % ph->param->nb_ph]);
	//pthread_mutex_lock(&ph->param->forks[ph->r_fork]);
	display(ph, 1);
}

static void	eat(t_philo *ph)
{
	ph->is_eating = 1;
	display(ph, 2);
	ph->last_eaten = gettime();
	usleep(ph->param->t_eat * 1000);
	ph->is_eating = 0;
	ph->eat_count++;
}

static void	leave_fork(t_philo *ph)
{
	pthread_mutex_unlock(&ph->param->forks[ph->i]);
	pthread_mutex_unlock(&ph->param->forks[(ph->i + 1) % ph->param->nb_ph]);
}

static void	sleeping(t_philo *ph)
{
	display(ph, 3);
	usleep(ph->param->t_sleep * 1000);
}

void		*actions(void *arg)
{
	t_philo		*philo;

	philo = arg;
	//if (pthread_create(&philo->param->thd, NULL, check_end, arg))
	//	return (NULL);
	//pthread_detach(philo->param->thd);
	//printf("philo %d  %d\n", philo->i, philo->param->t_eat);
	while (philo->is_alive)
	{
		take_fork(philo);
		eat(philo);
		leave_fork(philo);
		sleeping(philo);
		display(philo, 4);
	}
	return (NULL);
}
