/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/24 17:26:18 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
* Every philosopher will pass throught this function
* It has the routine : eat - sleep - think
*/
void	*dinning(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	print("is thinking", philo);
	if (philo->id % 2 == 0)
		time_skip(philo->table, 1);
	while (!philo->table->end_flag)
	{
		if (philo->table->philo_nbr == 1)
		{
			one_philo_dinner(philo);
			return (0);
		}
		eating(philo);
		print("is sleeping", philo);
		time_skip(philo->table, philo->table->time_to_sleep);
		print("is thinking", philo);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->right_fork_id]);
	print("has taken a fork", philo);
	pthread_mutex_lock(&philo->table->fork_locks[philo->left_fork_id]);
	print("has taken a fork", philo);
	pthread_mutex_lock(&philo->table->checking);
	philo->times_ate++;
	print("is eating", philo);
	philo->last_ate = time_now();
	pthread_mutex_unlock(&philo->table->checking);
	time_skip(philo->table, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->right_fork_id]);
	return (0);
}

int	one_philo_dinner(t_philo *philo)
{
	print("has taken a fork", philo);
	time_skip(philo->table, philo->table->time_to_die);
	return (0);
}
