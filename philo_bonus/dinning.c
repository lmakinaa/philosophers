/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:09:07 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/05 15:12:02 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (1)
	{
		sem_wait(philo->table->check);
		if (time_now() - philo->last_ate > philo->table->time_to_die)
		{
			print(philo, "died");
			exit(1);
		}
		sem_post(philo->table->check);
		usleep(1000);
	}
	return (0);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print(philo, "has taken a fork");
	sem_wait(philo->table->forks);
	print(philo, "has taken a fork");
	sem_wait(philo->table->check);
	print(philo, "is eating");
	philo->last_ate = time_now();
	philo->times_ate++;
	sem_post(philo->table->check);
	time_skip(philo->table->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

int	dinning(t_philo *philo)
{
	philo->last_ate = philo->table->start_time;
	if (pthread_create(&philo->die_check, NULL, monitoring, philo) == -1)
	{
		write(2, "Error while creating the verification thread\n", 45);
		exit(1);
	}
	if (pthread_detach(philo->die_check) != 0)
	{
		write(2, "Error while detaching the verification thread\n", 46);
		exit(1);
	}
	print(philo, "is thinking");
	while (1)
	{
		eating(philo);
		if (philo->times_ate >= philo->table->times_must_eat
			&& philo->table->times_must_eat != -1)
			break ;
		print(philo, "is sleeping");
		time_skip(philo->table->time_to_sleep);
		print(philo, "is thinking");
	}
	exit(0);
}
