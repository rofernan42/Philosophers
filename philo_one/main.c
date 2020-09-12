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

void	take_fork(t_philo *ph)
{
	pthread_mutex_lock(&ph->param->forks[ph->i]);
	display(ph, 1);
	//printf("%d\tphilo. %d has taken fork %d\n", timestamp(ph->param->init_time), ph->i, ph->i);
	pthread_mutex_lock(&ph->param->forks[(ph->i + 1) % ph->param->nb_ph]);
	display(ph, 1);
	//printf("%d\tphilo. %d has taken fork %d\n", timestamp(ph->param->init_time), ph->i, (ph->i + 1) % ph->param->nb_ph);
}

void	eat(t_philo *ph)
{
	ph->last_eaten = gettime();
	ph->is_eating = 1;
	display(ph, 2);
	usleep(ph->param->t_eat * 1000);
	ph->is_eating = 0;
	ph->eat_count++;
}

void	leave_fork(t_philo *ph)
{
	pthread_mutex_unlock(&ph->param->forks[ph->i]);
	pthread_mutex_unlock(&ph->param->forks[(ph->i + 1) % ph->param->nb_ph]);
}

void	sleeping(t_philo *ph)
{
	display(ph, 3);
	usleep(ph->param->t_sleep * 1000);
}

int		check_end(t_param *param)
{
	int	i;

	while (1)
	{
		i= 0;
		while (i < param->nb_ph)
		{
			if (!param->philo[i].is_eating \
			&& gettime() - param->philo[i].last_eaten > param->t_die)
			{
				param->philo[i].is_alive = 0;
				display(&param->philo[i], 5);
				return (1);
			}
			if (param->nb_eat > 0 \
			&& param->philo[i].eat_count >= param->nb_eat)
			{
				display(&param->philo[i], 6);
				return (1);
			}
			i++;
		}
	}
}

//void	*check_end(void *arg)
//{
//	int		i;
//	t_param	*param;
//
//	param = arg;
//	while (1)
//	{
//		i= 0;
//		while (i < param->nb_ph)
//		{
//			if (!param->philo[i].is_eating \
//			&& gettime() - param->philo[i].last_eaten > param->t_die)
//			{
//				param->philo[i].is_alive = 0;
//				display(&param->philo[i], 5);
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

void	*actions(void *arg)
{
	t_philo		*philo;

	philo = arg;
	//if (pthread_create(&philo->param->thd, NULL, check_end, arg))
	//	return (NULL);
	//pthread_detach(philo->param->thd);
	//printf("philo %d  %d\n", philo->i, philo->param->t_eat);
	while (philo->is_alive)
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
	int			i;

	i = 0;
	param->init_time = gettime();
	while (i < param->nb_ph)
	{
		if (pthread_create(&param->thd, NULL, actions, (void*)&param->philo[i]))
			return (1);
		pthread_detach(param->thd);
		//usleep(1000);
		i++;
	}
	if (check_end(param))
		return (0);
	//if (pthread_create(&param->thd, NULL, check_end, (void*)param))
	//	return (1);
	pthread_join(param->thd, NULL);
	return (0);
}

/*
void *thread_1(void *arg)
{
	printf("Nous sommes dans le thread.\n");

	//Pour enlever le warning
	(void) arg;
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t thread1;

	printf("Avant la création du thread.\n");

	if(pthread_create(&thread1, NULL, thread_1, NULL) == -1) {
	perror("pthread_create");
	return EXIT_FAILURE;
	}

	if (pthread_join(thread1, NULL)) {
	perror("pthread_join");
	return EXIT_FAILURE;
	}

	printf("Après la création du thread.\n");

//	struct timeval tv;
//	while (1)
//	{
//		gettimeofday(&tv, NULL);
//		printf("%ld  %ld\n", tv.tv_sec, tv.tv_usec);
//	}
*/

int		main(int ac, char **av)
{
	t_param	param;

	if (ac < 5 || ac > 6)
		return (print_error("error: wrong number of arguments\n"));
	if (init_param(&param, av) == 1)
		return (print_error("error: error argument value\n"));
	if (start_threads(&param) == 1)
		return (print_error("error: thread\n"));
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

	
	return (0);
}