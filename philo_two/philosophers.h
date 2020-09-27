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
# include <fcntl.h>
# include <semaphore.h>

typedef struct		s_philo
{
	int				i;
	int				is_alive;
	int				is_eating;
	int				last_eaten;
	int				eat_count;
	sem_t			*p_eat;
	//sem_t			*sem_eat_count;
	struct s_param	*param;
}					t_philo;

typedef struct		s_param
{
	int				nb_ph;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
	int				init_time;
	int				stop;
	t_philo			*philo;
	pthread_t		thd;
	sem_t			*forks;
	sem_t			*disp;
	sem_t			*order;
	//pthread_mutex_t	disp2;
}					t_param;

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
int					ft_strlen(char const *s);
void				ft_putnbr_fd(int n, int fd);
int					ft_atoi(const char *str);
int					gettime(void);
int					timestamp(int init_time);
void				display(t_philo *philo, int n);
int					init_param(t_param *param, char **av);
void				take_fork(t_philo *ph);
void				eat(t_philo *ph);
void				leave_fork(t_philo *ph);
void				sleeping(t_philo *ph);
void				free_all(t_param *param);
int					print_error(char *s, t_param *param);
char				*sem_n(char *str, int j);
int					create_sem(t_philo *philo, int i);

#endif
