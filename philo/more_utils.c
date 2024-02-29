/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:02:19 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/29 13:52:57 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_exit(t_table *table)
{
	long	max;
	long	start;

	start = time_now();
	if (table->time_to_eat > table->time_to_sleep)
		max = table->time_to_eat;
	else
		max = table->time_to_sleep;
	max *= 2;
	while (time_now() - start < max)
		usleep(500);
}

int	destroy_mutexes(t_table *table)
{
	int	i;

	safe_exit(table);
	pthread_mutex_destroy(&table->printing);
	pthread_mutex_destroy(&table->checking);
	pthread_mutex_destroy(&table->end_lock);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_destroy(&table->fork_locks[i]);
	free(table->fork_locks);
	free(table->philosophers);
	return (0);
}

int	is_finished(t_table *table)
{
	pthread_mutex_lock(&table->end_lock);
	if (table->end_flag)
	{
		pthread_mutex_unlock(&table->end_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->end_lock);
	return (0);
}

int	check_if_a_philo_died(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr && !is_finished(table))
	{
		pthread_mutex_lock(&table->checking);
		if (time_now() - table->philosophers[i].last_ate
			> table->time_to_die)
		{
			print("died", &table->philosophers[i]);
			pthread_mutex_lock(&table->end_lock);
			table->end_flag = 1;
			pthread_mutex_unlock(&table->end_lock);
			return (1);
		}
		pthread_mutex_unlock(&table->checking);
	}
	return (0);
}
