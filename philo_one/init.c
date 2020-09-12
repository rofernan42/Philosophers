/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 15:05:46 by rofernan          #+#    #+#             */
/*   Updated: 2020/09/09 15:05:50 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philo(t_param *param)
{
	int i;

	i = 0;
	if (!(param->philo = malloc(sizeof(t_param) * param->nb_ph)))
		return (1);
	while (i < param->nb_ph)
	{
		param->philo[i].i = i;
		param->philo[i].is_alive = 1;
		param->philo[i].is_eating = 0;
		param->philo[i].eat_count = 0;
		param->philo[i].param = param;
		i++;
	}
	return (0);
}

static int	init_forks(t_param *param)
{
	int i;

	i = 0;
	if (!(param->forks = malloc(sizeof(pthread_mutex_t) * param->nb_ph)))
		return (1);
	while (i < param->nb_ph)
		pthread_mutex_init(&param->forks[i++], NULL);
	pthread_mutex_init(&param->disp, NULL);
	return (0);
}

int			init_param(t_param *param, char **av)
{
	param->nb_ph = ft_atoi(av[1]);
	param->t_die = ft_atoi(av[2]);
	param->t_eat = ft_atoi(av[3]);
	param->t_sleep = ft_atoi(av[4]);
	param->nb_eat = ft_atoi(av[5]);
	param->init_time = gettime();
	param->stop = 0;
	if (param->nb_ph < 2 || param->t_die < 0 || param->t_eat < 0 \
	|| param->t_sleep < 0 || param->nb_eat < 0)
		return (1);
	if (init_philo(param))
		return (1);
	if (init_forks(param))
		return (1);
	return (0);
}
