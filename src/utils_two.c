/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:10:17 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/27 22:00:16 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	flag_death(t_fork_fee *customer)
{
	pthread_mutex_lock(&customer->hall->flag_mutex);
	*customer->dead = 1;
	pthread_mutex_unlock(&customer->hall->flag_mutex);
}

void	message_error(t_fork_fee *customer)
{
	pthread_mutex_lock(&customer->hall->flag_mutex);
	if (*customer->dead != 1)
	{
		(*customer->dead) = 1;
		pthread_mutex_unlock(&customer->hall->flag_mutex);
	}
	pthread_mutex_unlock(&customer->hall->flag_mutex);
}

void	grab_left(t_fork_fee *customer)
{
	pthread_mutex_lock(&customer->fork_l);
	pthread_mutex_lock(&customer->hall->flag_mutex);
	if (!*customer->dead)
		print_message(customer, "has taken a fork");
	pthread_mutex_unlock(&customer->hall->flag_mutex);
}

void	grab_right(t_fork_fee *customer)
{
	pthread_mutex_lock(customer->fork_r);
	pthread_mutex_lock(&customer->hall->flag_mutex);
	if (!*customer->dead)
		print_message(customer, "has taken a fork");
	pthread_mutex_unlock(&customer->hall->flag_mutex);
}

void	let_forks(t_fork_fee *customer)
{
	pthread_mutex_unlock(&customer->fork_l);
	pthread_mutex_unlock(customer->fork_r);
}
