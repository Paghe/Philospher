/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:34:10 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/27 21:54:59 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *s)
{
	int	res;

	res = 0;
	if (*s >= 0 && *s <= 32)
		s++;
	if (*s == '-')
		return (-1);
	if (*s == '+')
		s++;
	if (*s == '0')
		return (-1);
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	if (*s >= 9)
		return (-1);
	return (res);
}

t_table	init_fiesta(char **argv)
{
	t_table	table;

	table.philo = ft_atoi(argv[1]);
	table.time_death = ft_atoi(argv[2]);
	table.time_eat = ft_atoi(argv[3]);
	table.time_sleep = ft_atoi(argv[4]);
	table.max = 0;
	if (argv[5])
		table.must_eat = ft_atoi(argv[5]);
	else
			table.must_eat = 0;
	return (table);
}

int	check_format(t_table table)
{
	if (table.philo == -1 || table.time_death == -1 || table.time_eat == -1 \
	|| table.time_sleep == -1)
	{
		write(2, "Invalid input\n", 15);
		return (0);
	}
	return (1);
}

int	parsing(t_table *table, char **argv)
{
	*table = init_fiesta(argv);
	if (!check_format(*table))
		return (1);
	return (0);
}

void	print_message(t_fork_fee *customer, char *s)
{
	pthread_mutex_lock(&customer->hall->print);
	if (!*customer->dead)
		printf("%d %d %s\n", taco_time(customer), customer->id, s);
	pthread_mutex_unlock(&customer->hall->print);
}
