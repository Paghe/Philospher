/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:39:01 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/27 22:01:02 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_death(t_fork_fee *customer)
{
	int		terminator;

	terminator = customer->hall->time_death;
	pthread_mutex_lock(&customer->time_meal_mut);
	if (taco_time(customer) - customer->time_phil_eat >= terminator)
	{
		pthread_mutex_unlock(&customer->time_meal_mut);
		message_error(customer);
		return (1);
	}
	pthread_mutex_unlock(&customer->time_meal_mut);
	return (0);
}

void	lock_mutex_flag(t_table *table)
{
	pthread_mutex_lock(&table->flag_mutex);
	table->flag_death = 1;
	pthread_mutex_unlock(&table->flag_mutex);
}

void	set_flag(t_table *table)
{
	pthread_mutex_lock(&table->flag_mutex);
	*table->dead = 1;
	pthread_mutex_unlock(&table->flag_mutex);
}

void	print_dead(t_table *table, int i)
{
	if (table->must_eat == 0)
	{
		pthread_mutex_lock(&table->print);
		printf("%d %d died\n", taco_time(table->customer), \
			table->customer[i].id);
		pthread_mutex_unlock(&table->print);
		set_flag(table);
	}
}

void	*thread_necromancer(void *phil)
{
	int		i;
	int		terminator;
	t_table	*table;

	table = (t_table *)phil;
	terminator = table->time_death;
	while (1)
	{
		i = 0;
		while (i < table->philo)
		{
			pthread_mutex_lock(&table->customer[i].time_meal_mut);
			if (taco_time(table->customer) \
				- table->customer[i].time_phil_eat >= terminator)
			{
				pthread_mutex_unlock(&table->customer[i].time_meal_mut);
				print_dead(table, i);
				return (NULL);
			}
			pthread_mutex_unlock(&table->customer[i].time_meal_mut);
			i++;
			usleep(50);
		}
	}
	return (NULL);
}
