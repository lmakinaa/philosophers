/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:02:19 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/26 17:44:27 by ijaija           ###   ########.fr       */
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
	max = max + (max / 20);
	while (time_now() - start < max)
		usleep(50);
}

int	destroy_mutexes(t_table *table)
{
	int	i;

	safe_exit(table);
	pthread_mutex_destroy(&table->printing);
	pthread_mutex_destroy(&table->checking);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_destroy(&table->fork_locks[i]);
	free(table->fork_locks);
	free(table->philosophers);
	return (0);
}

int	is_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->checking);
	if (philo->table->end_flag)
	{
		pthread_mutex_unlock(&philo->table->checking);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->checking);
	return (0);
}
