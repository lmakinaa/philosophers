/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/12 19:59:48 by ijaija           ###   ########.fr       */
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
	if (philo->id % 2 == 0)
		sleep_in_ms(philo->table->time_to_eat);
	while (1)
	{
		if (is_finished(philo))
			return (0);
		eating(philo);
		print("is sleeping", philo);
		time_skip(philo, philo->table->time_to_sleep);
		print("is thinking", philo);
		if (philo->table->philo_nbr % 2 != 0)
			time_skip(philo, philo->table->time_to_eat);
	}
	return (0);
}

/*
* This if statement is to avoid deadlocks like in this situation :
* Philosopher 1 (odd) locks the right fork and waits for the left fork.
* Philosopher 2 (even) locks the left fork and waits for the right fork.
*/
int	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork_locks[philo->left_fork_id]);
		pthread_mutex_lock(&philo->table->fork_locks[philo->right_fork_id]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork_locks[philo->right_fork_id]);
		pthread_mutex_lock(&philo->table->fork_locks[philo->left_fork_id]);
	}
	print("has taken a fork", philo);
	print("has taken a fork", philo);
	print("is eating", philo);
	time_skip(philo, philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->eat_lock);
	philo->times_ate++;
	philo->last_ate = time_now();
	pthread_mutex_unlock(&philo->table->eat_lock);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->left_fork_id]);
	return (0);
}
