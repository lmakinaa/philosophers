/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:02:19 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/13 13:35:38 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (time_now() - philo->last_ate >= philo->table->time_to_die && !philo->eating)
	{
		print("died", philo);
		pthread_mutex_lock(&philo->table->end_flag_lock);
		philo->table->end_flag = 1;
		pthread_mutex_unlock(&philo->table->end_flag_lock);
		pthread_mutex_unlock(&philo->table->eat_lock);
		return (1);
	}
	else if (philo->times_ate >= philo->table->times_must_eat
		&& philo->table->times_must_eat != -1)
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
