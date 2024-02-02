/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:11:59 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/01 11:50:15 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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

int	eating(t_philo *philo)
{
	t_table	*table;
	
	table = philo->table;
	// this if is just for order
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(table->fork_lock[philo->l_f]));
		pthread_mutex_lock(&(table->fork_lock[philo->r_f]));
	}
	else
	{
		pthread_mutex_lock(&(table->fork_lock[philo->r_f]));
		pthread_mutex_lock(&(table->fork_lock[philo->l_f]));
	}
	printf("%ld %d has taken a fork\n",
		time_now() - philo->table->start_time, philo->id);
	printf("%ld %d has taken a fork\n",
		time_now() - philo->table->start_time, philo->id);
	printf("%ld %d is eating\n",
		time_now() - philo->table->start_time, philo->id);
	sleep_in_ms(philo->table->time_to_eat);
	philo->times_ate++;
	philo->last_eat = time_now();
	pthread_mutex_unlock(&(table->fork_lock[philo->r_f]));
	pthread_mutex_unlock(&(table->fork_lock[philo->l_f]));
	return (0);
}

int sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n",
		time_now() - philo->table->start_time, philo->id);
	sleep_in_ms(philo->table->time_to_sleep);
	return (0);
}

int	thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n",
		time_now() - philo->table->start_time, philo->id);
	return (0);
}

int	dead_or_finished_eat(t_philo philo)
{
	if (philo.times_ate >= philo.table->time_to_eat ||
		time_now() - philo.last_eat >= philo.table->time_to_die)
	{
		philo.table->end_flag = 1;
		return (1);
	}
	return (0);
}

void	start_monitoring(t_table *table)
{
	int	i;
	int	flag;

	flag = 1;
	while (flag)
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (flag && dead_or_finished_eat(table->philos[i]))
				flag = 0;
			i++;
		}
		usleep(8);
	}
	// join_all(table);
	// destroy_mutexex(table);
}

int	join_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
