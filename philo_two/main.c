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
	while (!philo->param->stop)
	{
		sem_wait(philo->p_eat);
		if (gettime() - philo->last_eaten > philo->param->t_die)
		{
			// philo->is_alive = 0;
			display(philo, 5);
			// sem_post(philo->p_eat);
			return (NULL);
		}
		sem_post(philo->p_eat);
		usleep(1000);
	}
	return (NULL);
}

// static void	*check_die(void *arg)
// {
// 	t_param	*param;
// 	int i;

// 	param = arg;
// 	while (!param->stop)
// 	{
// 		i = 0;
// 		while (i < param->nb_ph)
// 		{
// 			sem_wait(param->philo[i].p_eat);
// 			if (!param->philo[i].is_eating \
// 			&& gettime() - param->philo[i].last_eaten > param->t_die)
// 			{
// 				display(&param->philo[i], 5);
// 				// sem_post(param->philo[i].p_eat);
// 				return (NULL);
// 			}
// 			sem_post(param->philo[i].p_eat);
// 			i++;
// 		}
// 		usleep(100);
// 	}
// 	return (NULL);
// }


// static void	*check_count(void *arg)
// {
// 	int		i;
// 	t_param	*param;

// 	param = arg;
// 	while (param->count < param->nb_ph && !param->stop)
// 	{
// 		i = 0;
// 		param->count = 0;
// 		while (i < param->nb_ph)
// 		{
// 			if (param->philo[i].eat_count >= param->nb_eat)
// 				param->count++;
// 			i++;
// 		}
// 	}
// 	if (param->count == param->nb_ph)
// 		display(&param->philo[0], 6);
// 	return (NULL);
// }

static int	check_count(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->eat_count >= philo->param->nb_eat)
		philo->param->count++;
	if (philo->param->count == philo->param->nb_ph)
	{
		display(philo, 6);
		return (1);
	}
	return (0);
}


// static void	*check_count(void *arg)
// {
// 	int		count;
// 	int		i;
// 	t_param	*param;

// 	param = arg;
// 	count = 0;
// 	while (count < param->nb_eat && !param->stop)
// 	{
// 		i = 0;
// 		while (i < param->nb_ph)
// 			sem_wait(param->philo[i++].sem_eat_count);
// 		count++;
// 	}
// 	display(&param->philo[0], 6);
// 	return (NULL);
// }


static void	*actions(void *arg)
{
	t_philo		*philo;
	// pthread_t	thd;

	philo = arg;
	philo->last_eaten = gettime();
	// if (pthread_create(&philo->param->thd, NULL, &check_die, arg))
	// if (pthread_create(&thd, NULL, &check_die, arg))
		// return ((void*)1);
	// pthread_detach(thd);
	while (!philo->param->stop)
	// whiles (1)
	{
		take_fork(philo);
		eat(philo);
		leave_fork(philo);
		if (philo->param->nb_eat > 0 && check_count(philo))
			return (NULL);
		sleeping(philo);
		display(philo, 4);
	}
	// pthread_join(philo->param->thd, NULL);
	return (NULL);
}

static int	start_threads(t_param *param)
{
	int			i;
	pthread_t	thd;
	// pthread_t	thd2;
	// pthread_t	thd3;

	i = 0;
	// thd3 = NULL;
	param->init_time = gettime();
	while (i < param->nb_ph)
	{
		// if (pthread_create(&param->thd, NULL, &actions, (void*)&param->philo[i]))
			// return (1);
		if (pthread_create(&thd, NULL, &actions, &param->philo[i]))
			return (1);
		pthread_detach(thd);
		// if (pthread_create(&thd2, NULL, &check_die, (void*)&param->philo[i]))
		if (pthread_create(&param->philo[i].thd_ph, NULL, &check_die, (void*)&param->philo[i]))
			return (1);
		// pthread_detach(thd2);
		usleep(1000);
		i++;
	}
	// if (pthread_create(&thd2, NULL, &check_die, (void*)param))
		// return (1);
	// pthread_detach(thd2);
	// if (param->nb_eat > 0)
	// {
		// if (pthread_create(&param->thd, NULL, &check_count, (void*)param))
		// if (pthread_create(&thd3, NULL, &check_count, (void*)param))
			// return (1);
		// pthread_join(thd3, NULL);
		// pthread_detach(thd3);
		//pthread_join(param->thd, NULL);
	// }
	// pthread_join(param->thd, NULL);
	// pthread_join(thd1, NULL);
	// pthread_join(thd2, NULL);
	// if (param->nb_eat > 0)
		// pthread_join(thd3, NULL);
	i = 0;
	while (i < param->nb_ph)
		pthread_join(param->philo[i++].thd_ph, NULL);
	return (0);
}

int			main(int ac, char **av)
{
	t_param	param;

	memset(&param, 0, sizeof(t_param));
	if (ac < 5 || ac > 6)
		return (print_error("error: wrong number of arguments\n", NULL));
	if (init_param(&param, av) == 1)
		return (print_error("error: problem in initialization\n", &param));
	if (start_threads(&param) == 1)
		return (print_error("error: thread\n", &param));
// int i = 0;
// while (i < param.nb_ph)
// {
// 	printf("philo %d  eat_count %d\n", param.philo[i].i+1, param.philo[i].eat_count);
// 	i++;
// }
	free_all(&param);
	return (0);
}

/*
**printf("nb_ph: %d   t_die: %d   t_eat: %d    t_sleep:%d    nb_eat: %d\n", param.nb_ph, param.t_die, param.t_eat, param.t_sleep, param.nb_eat);
**int i ;
**i = 0;
**while (i < param.nb_ph)
**{
**	printf("philo %d  %d  %d\n", param.philo[i].i, param.philo[i].l_fork, param.philo[i].r_fork);
**		i++;
**}
**printf("initial time : %d\n", param.init_time);
**usleep(1000000);
**printf("time passed time : %d\n", gettime() - param.init_time);
**int i = 0;
**while (i < param.nb_ph)
**{
**	printf("philo %d  eat_count %d\n", param.philo[i].i+1, param.philo[i].eat_count);
**	i++;
**}
*/
