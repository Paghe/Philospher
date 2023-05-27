/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:43:01 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/25 18:27:22 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval			tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	taco_time(t_fork_fee *customer)
{
	static long long		mil = 0;
	int						res;

	pthread_mutex_lock(&customer->hall->mil_mut);
	if (mil == 0)
	{
		mil = get_time();
		pthread_mutex_unlock(&customer->hall->mil_mut);
		return (0);
	}
	pthread_mutex_unlock(&customer->hall->mil_mut);
	pthread_mutex_lock(&customer->hall->time_mut);
	res = (int)(get_time() - mil);
	pthread_mutex_unlock(&customer->hall->time_mut);
	return (res);
}
