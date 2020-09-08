/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 13:46:21 by rofernan          #+#    #+#             */
/*   Updated: 2020/09/07 13:46:30 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_philo
{
	int				i;
	int				l_fork;
	int				r_fork;
	int				time[3];
}					t_philo;

typedef struct		s_param
{
	int				nb_ph;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}					t_param;

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
int					print_error(char *s);
void				ft_putnbr_fd(int n, int fd);
int					ft_atoi(const char *str);

#endif
