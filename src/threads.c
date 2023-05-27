/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:19:18 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/27 21:43:49 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_fork_fee *customer)
{
	pthread_mutex_lock(&customer->hall->print);
	printf("%d %d is eating\n", taco_time(customer), customer->id);
	pthread_mutex_unlock(&customer->hall->print);
	customer->count_meal++;
	pthread_mutex_lock(&customer->time_meal_mut);
	customer->time_phil_eat = taco_time(customer);
	pthread_mutex_unlock(&customer->time_meal_mut);
}

void	fork_scenario(t_fork_fee *customer)
{
	grab_left(customer);
	grab_right(customer);
	pthread_mutex_lock(&customer->hall->flag_mutex);
	if (!*customer->dead)
		eating(customer);
	pthread_mutex_unlock(&customer->hall->flag_mutex);
	goodnight(customer->hall->time_eat, customer);
	let_forks(customer);
}

void	grab_fork(t_fork_fee *customer)
{
	if (customer == NULL)
	{
		pthread_mutex_lock(&customer->hall->print);
		printf("Invalid customer data\n");
		pthread_mutex_unlock(&customer->hall->print);
		return ;
	}
	pthread_mutex_lock(&customer->hall->flag_mutex);
	if (!*customer->dead)
	{
		pthread_mutex_unlock(&customer->hall->flag_mutex);
		fork_scenario(customer);
	}
	else
		pthread_mutex_unlock(&customer->hall->flag_mutex);
}

void	philo_even(t_fork_fee *philo)
{
	if (philo->id % 2 == 0)
		usleep(20000);
}

void	*do_duties(void *data)
{
	t_fork_fee	*philo;
	int			max;

	max = 1;
	philo = (t_fork_fee *)data;
	if (philo->hall->philo == 1)
	{
		lonely_dude(philo);
		return (NULL);
	}
	philo_even(philo);
	pthread_mutex_lock(&philo->hall->flag_mutex);
	while (1 && count_eat(philo, max++) != 0)
	{
		do_fork(philo);
		do_rest(philo);
		if (!*philo->dead)
			do_think(philo);
		else
		{
			pthread_mutex_unlock(&philo->hall->flag_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
