/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:16:00 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/12 19:04:37 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(void)
{
	struct timeval	time;
	long			res;

	res = 0;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

void	sleep_in_ms(long ms)
{
	long	start;

	start = time_now();
	while ((time_now() - start) < ms)
		usleep(500);
}

int	join_all(t_table *table)
{
	int	i;
	
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
	return (0);
}

int	print(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->printing);
	if (!is_finished(philo) || str[0] == 'd')
		printf("%ld %d %s\n", time_now() - philo->table->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->table->printing);
	return (0);
}

int	time_skip(t_philo *philo, long time_to_stop)
{
	long	start;

	start = time_now();
	while (time_now() - start < time_to_stop && !is_finished(philo))
		usleep(100);
	return (0);
}

int	destroy_mutexes(t_table *table)
{
	int	i;
	
	pthread_mutex_destroy(&table->printing);
	pthread_mutex_destroy(&table->eat_lock);
	pthread_mutex_destroy(&table->end_flag_lock);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_destroy(&table->fork_locks[i]);
	return (0);
}

int	is_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->end_flag_lock);
	if (philo->table->end_flag)
	{
		pthread_mutex_unlock(&philo->table->end_flag_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->end_flag_lock);
	return (0);
}

int	did_he_died_or_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eat_lock);
	if (time_now() - philo->last_ate >= philo->table->time_to_die)
	{
		print("died", philo);
		pthread_mutex_lock(&philo->table->end_flag_lock);
		philo->table->end_flag = 1;
		pthread_mutex_unlock(&philo->table->end_flag_lock);
		pthread_mutex_unlock(&philo->table->eat_lock);
		return (1);
	}
	else if (philo->times_ate >= philo->table->times_must_eat)
	{
		philo->table->philos_that_ate_enough++;
		if (philo->table->philos_that_ate_enough >= philo->table->philo_nbr)
		{
			pthread_mutex_lock(&philo->table->end_flag_lock);
			philo->table->end_flag = 1;
			pthread_mutex_unlock(&philo->table->end_flag_lock);
			pthread_mutex_unlock(&philo->table->eat_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->table->eat_lock);
	return (0);
}
