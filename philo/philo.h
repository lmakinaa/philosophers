/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:33:49 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/29 13:22:59 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	int				right_fork_id;
	int				left_fork_id;
	long			last_ate;
	int				times_ate;
	struct s_table	*table;
}				t_philo;

typedef struct s_table
{
	int				philo_nbr;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				times_must_eat;
	int				end_flag;
	int				philos_that_ate_enough;
	t_philo			*philosophers;
	pthread_mutex_t	checking;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	printing;
}				t_table;

int		args_parse(int argc, char **argv, t_table *table);
int		gathering_around_table(t_table *table);
int		preparing_table(t_table *table);
void	*dinning(void *ptr);
void	monitoring(t_table *table);
int		destroy_mutexes(t_table *table);
int		join_all(t_table *table);
int		eating(t_philo *philo);
void	safe_exit(t_table *table);

// Some utils

long	time_now(void);
void	print(char *str, t_philo *philo);
int		time_skip(t_table *table, long time_to_stop);
int		is_finished(t_table *table);
int		one_philo_dinner(t_philo *philo);
int		check_if_a_philo_died(t_table *table);
int		custom_usleep(long time_to_stop);

#endif
