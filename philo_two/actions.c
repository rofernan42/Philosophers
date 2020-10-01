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
	sem_wait(ph->param->order);
	sem_wait(ph->param->forks);
	display(ph, 1);
	sem_wait(ph->param->forks);
	display(ph, 1);
	sem_post(ph->param->order);
}

void	eat(t_philo *ph)
{
	sem_wait(ph->p_eat);
	ph->is_eating = 1;
	display(ph, 2);
	ph->last_eaten = gettime();
	usleep(ph->param->t_eat * 1000);
	ph->is_eating = 0;
	ph->eat_count++;
	sem_post(ph->p_eat);
	//sem_post(ph->sem_eat_count);
}

void	leave_fork(t_philo *ph)
{
	sem_post(ph->param->forks);
	sem_post(ph->param->forks);
}

void	sleeping(t_philo *ph)
{
	display(ph, 3);
	usleep(ph->param->t_sleep * 1000);
}
