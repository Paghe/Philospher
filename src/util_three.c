/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:25:36 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/27 17:28:41 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	do_fork(t_fork_fee *philo)
{
	if (!*philo->dead)
	{
		pthread_mutex_unlock(&philo->hall->flag_mutex);
		grab_fork(philo);
		pthread_mutex_lock(&philo->hall->flag_mutex);
	}
}

void	do_rest(t_fork_fee *philo)
{
	if (!*philo->dead)
	{
		pthread_mutex_unlock(&philo->hall->flag_mutex);
		time_to_rest(philo);
		pthread_mutex_lock(&philo->hall->flag_mutex);
	}
}

void	lonely_dude(t_fork_fee *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	print_message(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->fork_l);
}

void	do_think(t_fork_fee *philo)
{
	pthread_mutex_unlock(&philo->hall->flag_mutex);
	time_think(philo);
	pthread_mutex_lock(&philo->hall->flag_mutex);
}

int	count_eat(t_fork_fee *philo, int max)
{
	if (philo->hall->must_eat != 0)
	{
		if (max >= philo->hall->must_eat + 1)
		{
			pthread_mutex_unlock(&philo->hall->flag_mutex);
			return (0);
		}
	}
	return (max);
}
