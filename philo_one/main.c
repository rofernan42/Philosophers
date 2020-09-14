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

void	free_all(t_param *param)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&param->disp);
	pthread_mutex_destroy(&param->ph_dead);
	if (param->forks)
	{
		while (i < param->nb_ph)
			pthread_mutex_destroy(&param->forks[i++]);
		free(param->forks);
	}
	if (param->philo)
		free(param->philo);
}

void	check_end(t_param *param)
{
	int	i;
	int	count;

	while (1)
	{
		i= 0;
		count = 0;
		while (i < param->nb_ph)
		{
			if (!param->philo[i].is_eating \
			&& gettime() - param->philo[i].last_eaten > param->t_die)
			{
				param->philo[i].is_alive = 0;
				display(&param->philo[i], 5);
				return ;
			}
			if (param->nb_eat > 0 \
			&& param->philo[i].eat_count == param->nb_eat)
				count++;
			if (count == param->nb_ph)
			{
				display(&param->philo[i], 6);
				return ;
			}
			i++;
		}
	}
}

//void	*check_end(void *arg)
//{
//	int		i;
//	int		count;
//	t_param	*param;
//
//	param = arg;
//	while (1)
//	{
//		i= 0;
//		while (i < param->nb_ph)
//		{
//			if (!param->philo[i].is_eating
//			&& gettime() - param->philo[i].last_eaten > param->t_die)
//			{
//				param->philo[i].is_alive = 0;
//				display(&param->philo[i], 5);
//				return (NULL);
//			}
//			if (param->nb_eat > 0
//			&& param->philo[i].eat_count == param->nb_eat)
//				count++;
//			if (count == param->nb_ph)
//			{
//				display(&param->philo[i], 6);
//				return (NULL);
//			}
//			i++;
//		}
//	}
//}

//void	*check_end(void *arg)
//{
//	int		i;
//	t_philo	*philo;
//
//	philo = arg;
//	while (philo->alive)
//	{
//		if (gettime() - philo->last_eaten > philo->param->t_die)
//		{
//			philo->alive = 0;
//			display(philo, 5);
//			break ;
//		}
//	}
//	return (NULL);
//}

int		start_threads(t_param *param)
{
	long int	i;

	i = 0;
	param->init_time = gettime();
	while (i < param->nb_ph)
	{
		if (pthread_create(&param->thd, NULL, actions, (void*)&param->philo[i]))
			return (1);
		pthread_detach(param->thd);
		usleep(100);
		i++;
	}
	check_end(param);
	//if (pthread_create(&param->thd, NULL, check_end, (void*)param))
	//	return (1);
	pthread_join(param->thd, NULL);
	return (0);
}

int		main(int ac, char **av)
{
	t_param	param;

	if (ac < 5 || ac > 6)
		return (print_error("error: wrong number of arguments\n"));
	if (init_param(&param, av) == 1)
	{
		free_all(&param);
		return (print_error("error: error argument value\n"));
	}
	if (start_threads(&param) == 1)
	{
		free_all(&param);
		return (print_error("error: thread\n"));
	}
	//printf("nb_ph: %d   t_die: %d   t_eat: %d    t_sleep:%d    nb_eat: %d\n", param.nb_ph, param.t_die, param.t_eat, param.t_sleep, param.nb_eat);
	
//	int i ;

//	i = 0;
//	while (i < param.nb_ph)
//	{
//		printf("philo %d  %d  %d\n", param.philo[i].i, param.philo[i].l_fork, param.philo[i].r_fork);
///		i++;
//	}
	//printf("initial time : %d\n", param.init_time);
	//usleep(1000000);
	//printf("time passed time : %d\n", gettime() - param.init_time);
	
	int i = 0;
	while (i < param.nb_ph)
	{
		printf("philo %d  eat_count %d\n", param.philo[i].i+1, param.philo[i].eat_count);
		i++;
	}

	pthread_mutex_lock(&param.ph_dead);
	pthread_mutex_unlock(&param.ph_dead);
	//free_all(&param);
	return (0);
}