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

char	*sem_n(char *str, int j)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(tmp = malloc(sizeof(char) * 100)))
		return (NULL);
	while (i < ft_strlen(str))
	{
		tmp[i] = str[i];
		i++;
	}
	while (j > 0)
	{
		tmp[i++] = j % 10 + '0';
		j = j / 10;
	}
	tmp[i] = 0;
	return (tmp);
}

static int	init_philo(t_param *param)
{
	int		i;
	char	*sem_name;

	i = 0;
	while (i < param->nb_ph)
	{
		param->philo[i].i = i;
		param->philo[i].is_alive = 1;
		param->philo[i].is_eating = 0;
		param->philo[i].eat_count = 0;
		sem_name = sem_n("sem_p_eat", i);
		sem_unlink(sem_name);
		//printf("%s\n", sem_name);
		if ((param->philo[i].p_eat = sem_open(sem_name, O_CREAT, 0644, 1)) \
		== SEM_FAILED)
			return (1);
		free(sem_name);
		param->philo[i].param = param;
		i++;
	}
	return (0);
}

static int	init_sem(t_param *param)
{
	sem_unlink("sem_fork");
	sem_unlink("sem_disp");
	sem_unlink("sem_order");
	if ((param->forks = sem_open("sem_fork", O_CREAT, 0644, param->nb_ph)) \
	== SEM_FAILED)
		return (1);
	if ((param->disp = sem_open("sem_disp", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (1);
	if ((param->order = sem_open("sem_order", O_CREAT, 0644, 1)) == SEM_FAILED)
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
	//pthread_mutex_init(&param->disp2, NULL);
	return (init_sem(param));
}
