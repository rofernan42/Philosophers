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
	int		i;

	i = 0;
	if (param)
	{
		if (param->philo)
		{
			while (i < param->nb_ph)
			{
				sem_unlink(param->philo[i].sem_name);
				free(param->philo[i].sem_name);
				param->philo[i].sem_name = NULL;
				i++;
			}
			free(param->philo);
			param->philo = NULL;
		}
		sem_unlink("sem_fork");
		sem_unlink("sem_disp");
	}
}

int		print_error(char *s, t_param *param)
{
	ft_putstr_fd(s, 1);
	free_all(param);
	return (1);
}
