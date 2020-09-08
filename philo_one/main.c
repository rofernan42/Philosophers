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

int		init_philo(t_param *param)
{
	int i;

	i = 0;
	if (!(param->philo = malloc(sizeof(t_param) * param->nb_ph)))
		return (1);
	while (i < param->nb_ph)
	{
		param->philo->i = i;
		param->philo->l_fork = i;
		param->philo->r_fork = (i + 1) % param->nb_ph;
		param->philo->time[0] = param->t_die;
		param->philo->time[1] = param->t_eat;
		param->philo->time[2] = param->t_sleep;
		i++;
	}
	return (0);
}

int		init_forks(t_param *param)
{
	int i;

	i = 0;
	if (!(param->forks = malloc(sizeof(pthread_mutex_t) * param->nb_ph)))
		return (1);
	while (i < param->nb_ph)
		pthread_mutex_init(&param->forks[i++], NULL);
	return (0);
}

int		init_param(t_param *param, char **av)
{
	param->nb_ph = ft_atoi(av[1]);
	param->t_die = ft_atoi(av[2]);
	param->t_eat = ft_atoi(av[3]);
	param->t_sleep = ft_atoi(av[4]);
	param->nb_eat = ft_atoi(av[5]);
	if (param->nb_ph < 2 || param->t_die < 0 || param->t_eat < 0 \
		|| param->t_sleep < 0 || param->nb_eat < 0)
		return (1);
	if (init_philo(param))
		return (1);
	if (init_forks(param))
		return (1);
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

	//printf("nb_ph: %d   t_die: %d   t_eat: %d    t_sleep:%d    nb_eat: %d", param.nb_ph, param.t_die, param.t_eat, param.t_sleep, param.nb_eat);
	
	
	return (0);
}