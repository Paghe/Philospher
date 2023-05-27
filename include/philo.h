/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:31:28 by apaghera          #+#    #+#             */
/*   Updated: 2023/05/27 17:22:36 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork_fee	t_fork_fee;

typedef struct s_flag
{
}	t_flag;

typedef struct s_table
{
	int				philo;
	int				max;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	pthread_mutex_t	time_mut;
	pthread_mutex_t	mil_mut;
	int				*dead;
	t_fork_fee		*customer;
	pthread_mutex_t	flag_mutex;
	int				flag_death;
	pthread_mutex_t	print;
	pthread_mutex_t	max_eat;
	t_flag			check;
}	t_table;

typedef struct s_fork_fee
{
	int				id;
	int				count_meal;
	int				time_phil_eat;
	int				*dead;
	t_table			*hall;
	pthread_mutex_t	time_meal_mut;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	*fork_r;
}	t_fork_fee;

int			ft_atoi(char *s);
t_table		init_fiesta(char **argv);
int			parsing(t_table *table, char **argv);
void		*do_duties(void *data);
void		init_all(t_table *table);
void		print_message(t_fork_fee *customer, char *s);
void		message_error(t_fork_fee *customer);
void		grab_left(t_fork_fee *customer);
void		grab_right(t_fork_fee *customer);
void		let_forks(t_fork_fee *customer);
int			taco_time(t_fork_fee *customer);
void		*thread_necromancer(void *phil);
void		lock_purgatory(t_table *table);
long long	get_time(void);
void		goodnight(long long time, t_fork_fee *customer);
void		time_to_rest(t_fork_fee *customer);
void		time_think(t_fork_fee *customer);
int			check_death(t_fork_fee *customer);
void		do_fork(t_fork_fee *philo);
void		do_rest(t_fork_fee *philo);
void		grab_fork(t_fork_fee *customer);
void		lonely_dude(t_fork_fee *philo);
void		do_think(t_fork_fee *philo);
int			count_eat(t_fork_fee *philo, int max);
#endif
