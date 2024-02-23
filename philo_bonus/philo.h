/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:33:49 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/23 20:33:58 by ijaija           ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>

typedef struct s_philosopher
{
	int						id;
	pid_t					pid;
	long					last_ate;
	int						times_ate;
	pthread_t				die_check;
	struct s_philosopher	*next_p;
	struct s_philosopher	*prev_p;
	struct s_table			*table;
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
	sem_t			*printing;
	sem_t			*check;
	sem_t			*forks;
	t_philo			*philosophers;

}				t_table;

int		args_parse(int argc, char **argv, t_table *table);
int		dinning(t_philo *philo);

// Some utils

long	time_now(void);
int		time_skip(t_philo *philo, long time_to_stop);
int		init_semaphores(t_table *table);
void	print(t_philo *philo, char *str);

#endif
