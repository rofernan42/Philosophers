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
	while (philo->is_alive)
	{
		if (!philo->is_eating \
		&& gettime() - philo->last_eaten > philo->param->t_die)
		{
			philo->is_alive = 0;
			display(philo, 5);
		}
		usleep(100);
	}
	return (NULL);
}

static void	*check_count(void *arg)
{
	int		count;
	int		i;
	t_param	*param;

	param = arg;
	count = 0;
	while (count < param->nb_eat && !param->stop)
	{
		i = 0;
		while (i < param->nb_ph)
			sem_wait(param->philo[i++].sem_eat_count);
		count++;
	}
	display(&param->philo[0], 6);
	usleep(100);
	return (NULL);
}

static int	actions(t_philo *philo)
{
	pthread_t	thd;

	philo->last_eaten = gettime();
	if (pthread_create(&thd, NULL, &check_die, (void*)philo))
		return (1);
	pthread_detach(thd);
	while (!philo->param->stop)
	{
		take_fork(philo);
		eat(philo);
		leave_fork(philo);
		sleeping(philo);
		display(philo, 4);
	}
	return (0);
}

static int	start_forks(t_param *param)
{
	int			i;
	pthread_t	thd;

	i = 0;
	param->init_time = gettime();
	while (i < param->nb_ph)
	{
		if (!(param->philo[i].pid = fork()))
		{
			actions(&param->philo[i]);
			exit(0);
		}
		else if (param->philo[i].pid < 0)
			return (1);
		usleep(100);
		i++;
	}
	if (param->nb_eat > 0)
	{
		if (pthread_create(&thd, NULL, &check_count, (void*)param))
			return (1);
		pthread_detach(thd);
	}
	waitpid(0, NULL, 0);
	return (0);
}

// static int	thread_count(t_param *param)
// {
// 	pthread_t	thd;

// 	if (param->nb_eat > 0)
// 	{
// 		if (pthread_create(&thd, NULL, &check_count, (void*)param))
// 			return (1);
// 		pthread_detach(thd);
// 	}
// 	return (0);
// }

int			main(int ac, char **av)
{
	t_param	param;

	memset(&param, 0, sizeof(t_param));
	if (ac < 5 || ac > 6)
		return (print_error("error: wrong number of arguments\n", NULL));
	if (init_param(&param, av) == 1)
		return (print_error("error: problem in initialization\n", &param));
	if (start_forks(&param) == 1)
		return (print_error("error: thread\n", &param));
	free_all(&param);
	return (0);
}
