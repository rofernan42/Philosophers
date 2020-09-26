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

static void	init_philo(t_param *param)
{
	int i;

	i = 0;
	while (i < param->nb_ph)
	{
		param->philo[i].i = i;
		param->philo[i].is_alive = 1;
		param->philo[i].is_eating = 0;
		param->philo[i].eat_count = 0;
		param->philo[i].param = param;
		i++;
	}
}

static int	init_sem(t_param *param)
{
	sem_unlink("sem_fork");
	sem_unlink("sem_disp");
	if ((param->forks = sem_open("sem_fork", O_CREAT, 0644, param->nb_ph)) \
	== SEM_FAILED)
		return (1);
	if ((param->disp = sem_open("sem_disp", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (1);
	return (0);
}

int			init_param(t_param *param, char **av)
{
	param->nb_ph = ft_atoi(av[1]);
	param->t_die = ft_atoi(av[2]);
	param->t_eat = ft_atoi(av[3]);
	param->t_sleep = ft_atoi(av[4]);
	param->nb_eat = ft_atoi(av[5]);
	param->stop = 0;
	if (param->nb_ph < 2 || param->t_die < 20 || param->t_eat < 20 \
	|| param->t_sleep < 20 || param->nb_eat < 0)
		return (1);
	if (!(param->philo = malloc(sizeof(t_param) * param->nb_ph)))
		return (1);
	init_philo(param);
	return (init_sem(param));
}
