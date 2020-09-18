/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:50:25 by rofernan          #+#    #+#             */
/*   Updated: 2020/09/10 17:50:27 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	display_action(int n)
{
	if (n == 1)
		ft_putstr_fd(" has taken a fork\n", 1);
	else if (n == 2)
		ft_putstr_fd(" is eating\n", 1);
	else if (n == 3)
		ft_putstr_fd(" is sleeping\n", 1);
	else if (n == 4)
		ft_putstr_fd(" is thinking\n", 1);
	else if (n == 5)
		ft_putstr_fd(" has died\n", 1);
	else if (n == 6)
		ft_putstr_fd("\tnumber of meals reached\n", 1);
}


/*static char	*display_action(int n)
{
	if (n == 1)
		return (" has taken a fork\n");
	else if (n == 2)
		return (" is eating\n");
	else if (n == 3)
		return (" is sleeping\n");
	else if (n == 4)
		return (" is thinking\n");
	else if (n == 5)
		return (" has died\n");
	else if (n == 6)
		return ("\tnumber of meals reached\n");
	return (NULL);
}
*/
void		display(t_philo *philo, int n)
{
	pthread_mutex_lock(&philo->param->disp);
	if (!philo->param->stop)
	{
		ft_putnbr_fd(timestamp(philo->param->init_time), 1);
		//ft_putnbr_fd(gettime() - philo->param->init_time, 1);
		if (n != 6)
		{
			//write(1, "\tphilo. ", 8);
			ft_putstr_fd("\tphilo. ", 1);
			ft_putnbr_fd(philo->i + 1, 1);
		}
		display_action(n);
		//write(1, display_action(n), ft_strlen(display_action(n)));
		if (n == 5 || n == 6)
			philo->param->stop = 1;
	}
	pthread_mutex_unlock(&philo->param->disp);
}
