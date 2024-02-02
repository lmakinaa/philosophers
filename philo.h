/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:33:49 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/01 14:29:48 by ijaija           ###   ########.fr       */
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
	int				r_f;
	int				l_f;
	int				times_ate;
	long long		last_eat;
	struct s_table	*table;
	pthread_t		thread;
}				t_philo;

typedef struct s_table
{
	long			start_time;
	int				philos_created;
	int				end_flag;
	int				philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				times_must_eat;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	printing_lock;
	t_philo			*philos;
}				t_table;

int		args_parsing(int argc, char ***argv, t_table *table);
int		gathering_around_table(t_table *table, t_memslots *slots);
long	time_now(void);
void	sleep_in_ms(long ms);
int		eating(t_philo *philo);
int 	sleeping(t_philo *philo);
int		thinking(t_philo *philo);
int		join_all(t_table *table);
void	start_monitoring(t_table *table);

#endif