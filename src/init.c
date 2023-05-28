/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:10:33 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/28 14:51:38 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	table->customer = malloc(sizeof(t_fork_fee) * table->philo);
	pthread_mutex_init(&table->flag_mutex, NULL);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->time_mut, NULL);
	pthread_mutex_init(&table->mil_mut, NULL);
	pthread_mutex_init(&table->max_eat, NULL);
	while (i < table->philo)
	{
		pthread_mutex_init(&table->customer[i].fork_l, NULL);
		pthread_mutex_init(&table->customer[i].time_meal_mut, NULL);
		if (i != 0)
			table->customer[i].fork_r = &table->customer[i - 1].fork_l;
		i++;
	}
	table->customer[0].fork_r = &table->customer[i - 1].fork_l;
}

void	init_philo(t_fork_fee *customer, t_table *table)
{
	int	i;

	i = 0;
	table->dead = malloc(sizeof(int));
	*table->dead = 0;
	while (i < table->philo)
	{
		customer[i].dead = table->dead;
		customer[i].id = i;
		customer[i].count_meal = 0;
		customer[i].time_phil_eat = 0;
		customer[i].hall = table;
		i++;
	}
	table->flag_death = 0;
}

void	pthread_init(t_table *table)
{
	int			i;
	pthread_t	*t;

	i = 0;
	t = malloc(sizeof(pthread_t) * table->philo);
	while (i < table->philo)
	{
		pthread_create(&t[i], NULL, &do_duties, &table->customer[i]);
		i++;
	}
	i = 0;
	lock_purgatory(table);
	while (i < table->philo)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	free(t);
}

void	lock_purgatory(t_table *table)
{
	pthread_t	t;

	pthread_create(&t, NULL, &thread_necromancer, table);
	pthread_join(t, NULL);
}

void	init_all(t_table *table)
{
	int	i;

	i = 0;
	init_mutex(table);
	init_philo(table->customer, table);
	pthread_init(table);
	while (i < table->philo)
	{
		pthread_mutex_destroy(&table->customer[i].fork_l);
		pthread_mutex_destroy(&table->customer[i].time_meal_mut);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->flag_mutex);
	pthread_mutex_destroy(&table->time_mut);
	pthread_mutex_destroy(&table->mil_mut);
	pthread_mutex_destroy(&table->max_eat);
	free(table->customer);
	free(table->dead);
}
