/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/23 23:59:13 by ijaija           ###   ########.fr       */
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
	if (philo->id % 2 == 0)+
		time_skip(philo, 1);
	while (!is_finished(philo))
	{
		if (philo->table->philo_nbr == 1)
		{
			one_philo_dinner(philo);
			return (0);
		}
		eating(philo);
		print("is sleeping", philo);
		time_skip(philo, philo->table->time_to_sleep);
		print("is thinking", philo);
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
	philo->eating = 1;
	print("is eating", philo);
	pthread_mutex_lock(&philo->table->eat_lock);
	philo->last_ate = time_now();
	philo->times_ate++;
	pthread_mutex_unlock(&philo->table->eat_lock);
	time_skip(philo, philo->table->time_to_eat);
	philo->eating = 0;
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
