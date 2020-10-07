/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 13:49:10 by rofernan          #+#    #+#             */
/*   Updated: 2020/09/07 13:49:15 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*check_die(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!philo->param->stop)
	{
		sem_wait(philo->p_eat);
		if (!philo->param->stop && \
		gettime() - philo->last_eaten > philo->param->t_die)
		{
			display(philo, 5);
			sem_post(philo->p_eat);
			return (NULL);
		}
		sem_post(philo->p_eat);
		usleep(100);
	}
	return (NULL);
}

static int	check_count(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->eat_count >= philo->param->nb_eat)
		philo->param->count++;
	if (philo->param->count == philo->param->nb_ph)
	{
		display(philo, 6);
		return (1);
	}
	return (0);
}

static void	*actions(void *arg)
{
	t_philo		*philo;

	philo = arg;
	philo->last_eaten = gettime();
	while (!philo->param->stop)
	{
		take_fork(philo);
		eat(philo);
		leave_fork(philo);
		if (philo->param->nb_eat > 0 && check_count(philo))
			return (NULL);
		sleeping(philo);
		display(philo, 4);
	}
	return (NULL);
}

static int	start_threads(t_param *param)
{
	int			i;
	pthread_t	thd;

	i = 0;
	param->init_time = gettime();
	while (i < param->nb_ph)
	{
		param->philo[i].last_eaten = gettime();
		if (pthread_create(&thd, NULL, &actions, &param->philo[i]))
			return (1);
		pthread_detach(thd);
		if (pthread_create(&param->philo[i].thd_ph, NULL, &check_die, \
		(void*)&param->philo[i]))
			return (1);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < param->nb_ph)
		pthread_join(param->philo[i++].thd_ph, NULL);
	return (0);
}

int			main(int ac, char **av)
{
	t_param	param;

	memset(&param, 0, sizeof(t_param));
	if (ac < 5 || ac > 6)
		return (print_error("error: wrong number of arguments\n", NULL));
	if (init_param(&param, av) == 1)
		return (print_error("error: problem in initialization\n", &param));
	if (start_threads(&param) == 1)
		return (print_error("error: thread\n", &param));
	free_all(&param);
	return (0);
}
