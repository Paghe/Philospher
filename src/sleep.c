/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:11:02 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/27 21:57:56 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	goodnight(long long time, t_fork_fee *customer)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (check_death(customer))
			return ;
		else
			usleep(1000);
	}
}

void	time_to_rest(t_fork_fee *customer)
{
	pthread_mutex_lock(&customer->hall->print);
	if (!*customer->dead)
		printf("%d %d is sleeping\n", taco_time(customer), customer->id);
	pthread_mutex_unlock(&customer->hall->print);
	goodnight(customer->hall->time_sleep, customer);
}

void	time_think(t_fork_fee *customer)
{
	long long	time_left;

	pthread_mutex_lock(&customer->hall->print);
	if (!*customer->dead)
		printf("%d %d is thinking\n", taco_time(customer), customer->id);
	pthread_mutex_unlock(&customer->hall->print);
	time_left = customer->hall->time_death - \
		(taco_time(customer) - customer->time_phil_eat);
	if (time_left > 0)
		goodnight((time_left * 4) / 10, customer);
}
