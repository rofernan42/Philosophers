/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:25:48 by rofernan          #+#    #+#             */
/*   Updated: 2020/09/23 14:25:50 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_param *param)
{
	int i;

	i = 0;
	if (param)
	{
		if (param->forks)
		{
			while (i < param->nb_ph)
				pthread_mutex_destroy(&param->forks[i++]);
			free(param->forks);
		}
		pthread_mutex_destroy(&param->disp);
		if (param->philo)
		{
			i = 0;
			while (i < param->nb_ph)
				pthread_mutex_destroy(&param->philo[i++].p_eat);
			free(param->philo);
			param->philo = NULL;
		}
	}
}

int		print_error(char *s, t_param *param)
{
	ft_putstr_fd(s, 1);
	free_all(param);
	return (1);
}
