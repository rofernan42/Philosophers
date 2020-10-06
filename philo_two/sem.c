/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:35:23 by rofernan          #+#    #+#             */
/*   Updated: 2020/09/27 13:35:29 by rofernan         ###   ########.fr       */
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

int		create_sem(t_philo *philo, int i)
{
	if (!(philo->sem_name = sem_n("sem_p_eat", i)))
		return (1);
	sem_unlink(philo->sem_name);
	if ((philo->p_eat = sem_open(philo->sem_name, O_CREAT, 0644, 1)) \
	== SEM_FAILED)
		return (1);
	return (0);
}
