/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:33:49 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/12 18:54:25 by ijaija           ###   ########.fr       */
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
# include "./allocation_manager/allocation_manager.h"

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	int				right_fork_id;
	int				left_fork_id;
	long			last_ate;
	int				times_ate;
	int				think_print_flag;
	int				eating;
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
	pthread_mutex_t	end_flag_lock;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	printing;
	pthread_mutex_t	eat_lock;
}				t_table;

int		args_parse(int argc, char **argv, t_table *table);
int		gathering_around_table(t_memslots *slots, t_table *table);
int		preparing_table(t_memslots *slots, t_table *table);
void	*dinning(void *ptr);
void	monitoring(t_table *table);
int		destroy_mutexes(t_table *table);
int		join_all(t_table *table);
int		eating(t_philo *philo);

// Some utils

long	time_now(void);
void	sleep_in_ms(long ms);
int		print(char *str, t_philo *philo);
int		time_skip(t_philo *philo, long time_to_stop);
int		is_finished(t_philo *philo);
int		did_he_died_or_finished(t_philo *philo);
int		one_philo_dinner(t_philo *philo);

#endif
