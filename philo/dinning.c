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
	{
		print("is thinking", philo);
		philo->printed = 0;
		time_skip(philo, 1);
	}
	while (1)
	{
		if (philo->table->philo_nbr == 1)
		{
			one_philo_dinner(philo);
			return (0);
		}
		if (is_finished(philo))
			return (0);
		print("is thinking", philo);
		eating(philo);
		print("is sleeping", philo);
		time_skip(philo, philo->table->time_to_sleep);
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
	pthread_mutex_lock(&philo->table->fork_locks[philo->right_fork_id]);
	print("has taken a fork", philo);
	pthread_mutex_lock(&philo->table->fork_locks[philo->left_fork_id]);
	print("has taken a fork", philo);
	print("is eating", philo);
	pthread_mutex_lock(&philo->table->eat_lock);
	philo->times_ate++;
	philo->last_ate = time_now();
	pthread_mutex_unlock(&philo->table->eat_lock);
	time_skip(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->right_fork_id]);
	return (0);
}

int	one_philo_dinner(t_philo *philo)
{
	print("has taken a fork", philo);
	time_skip(philo, philo->table->time_to_die);
	return (0);
}
