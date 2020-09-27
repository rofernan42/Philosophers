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

static void	free_sem(t_param *param)
{
	int		i;
	char	*sem_name;

	i = 0;
	sem_name = NULL;
	while (i < param->nb_ph)
	{
		sem_name = sem_n("sem_p_eat", i);
		printf("%s\n", sem_name);
		sem_unlink(sem_name);
		free(sem_name);
		sem_name = NULL;
		sem_name = sem_n("sem_eat_count", i);
		printf("%s\n", sem_name);
		sem_unlink(sem_name);
		free(sem_name);
		sem_name = NULL;
		i++;
	}
}

void		free_all(t_param *param)
{
	int i;

	i = 0;
	if (param)
	{
		sem_unlink("sem_fork");
		sem_unlink("sem_disp");
		sem_unlink("sem_order");
		if (param->philo)
		{
			while (i < param->nb_ph)
				kill(param->philo[i++].pid, SIGKILL);
			free_sem(param);
			free(param->philo);
		}
	}
}

int			print_error(char *s, t_param *param)
{
	ft_putstr_fd(s, 1);
	free_all(param);
	return (1);
}
