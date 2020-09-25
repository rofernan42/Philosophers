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

/*
void	check_end(t_param *param)
{
	int	i;
	int	count;

	count = 0;
	while (1)
	{
		i= 0;
		//count = 0;
		while (i < param->nb_ph)
		{
			if (!param->philo[i].is_eating \
			&& gettime() - param->philo[i].last_eaten > param->t_die)
			{
				//param->philo[i].is_alive = 0;
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
*/
/*void	*check_end(void *arg)
{
	int		i;
	int		count;
	t_param	*param;

	param = arg;
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
				return (NULL);
			}
			if (param->nb_eat > 0 \
			&& param->philo[i].eat_count == param->nb_eat)
				count++;
			if (count == param->nb_ph)
			{
				display(&param->philo[i], 6);
				return (NULL);
			}
			i++;
		}
	}
}
*/
void	*check_die(void *arg)
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

void	*check_count(void *arg)
{
	int		i;
	int		count;
	t_param	*param;

	param = arg;
	count = 0;
	while (count < param->nb_ph && !param->stop)
	{
		i = 0;
		count = 0;
		while (i < param->nb_ph)
		{
			if (param->philo[i].eat_count >= param->nb_eat)
				count++;
			i++;
		}
	}
	display(&param->philo[0], 6);
	return (NULL);
}

void		*actions(void *arg)
{
	t_philo		*philo;
	pthread_t	thd;

	philo = arg;
	philo->last_eaten = gettime();
	if (pthread_create(&thd, NULL, check_die, arg))
		return ((void*)1);
	pthread_detach(thd);
	while (!philo->param->stop)
	{
		take_fork(philo);
		eat(philo);
		leave_fork(philo);
		sleeping(philo);
		display(philo, 4);
	}
	return (NULL);
}

int		start_threads(t_param *param)
{
	long int	i;
	//pthread_t	thd;

	i = 0;
	param->init_time = gettime();
	while (i < param->nb_ph)
	{
		if (pthread_create(&param->thd, NULL, actions, (void*)&param->philo[i]))
			return (1);
		//pthread_detach(param->thd);
		usleep(100);
		i++;
	}
	if (param->nb_eat > 0)
	{
		if (pthread_create(&param->thd, NULL, check_count, (void*)param))
			return (1);
		//pthread_detach(param->thd);
	}
	//check_end(param);
	//if (pthread_create(&param->thd, NULL, check_end, (void*)param))
	//	return (1);
	pthread_join(param->thd, NULL);
	return (0);
}

int		main(int ac, char **av)
{
	t_param	param;

	memset(&param, 0, sizeof(t_param));
	if (ac < 5 || ac > 6)
		return (print_error("error: wrong number of arguments\n", NULL));
	if (init_param(&param, av) == 1)
		return (print_error("error: problem in initialization\n", &param));
	if (start_threads(&param) == 1)
		return (print_error("error: thread\n", &param));
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

	free_all(&param);
	return (0);
}
