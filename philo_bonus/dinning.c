/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:09:07 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/23 20:33:45 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_if_died(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (1)
	{
		sem_wait(philo->table->check);
		if (time_now() - philo->last_ate > philo->table->time_to_die)
		{
			print(philo, "died");
			philo->table->end_flag = 1;
			exit(1);
		}
		sem_post(philo->table->check);
		if (philo->table->end_flag)
			break ;
		time_skip(philo, 1);
		if (philo->times_ate >= philo->table->times_must_eat
			&& philo->table->times_must_eat != -1)
			break ;
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
	philo->times_ate++;
	print(philo, "is eating");
	philo->last_ate = time_now();
	sem_post(philo->table->check);
	time_skip(philo, philo->table->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

int	dinning(t_philo *philo)
{
	philo->last_ate = philo->table->start_time;
	if (pthread_create(&philo->die_check, NULL, check_if_died, philo) == -1)
	{
		write(2, "Error while creating the verification thread\n", 45);
		exit(1);
	}
	if (philo->id % 2 == 0)
		time_skip(philo, 1);
	while (!philo->table->end_flag)
	{
		eating(philo);
		if (philo->times_ate >= philo->table->times_must_eat
			&& philo->table->times_must_eat != -1)
			break ;
		print(philo, "is sleeping");
		time_skip(philo, philo->table->time_to_sleep);
		print(philo, "is thinking");
	}
	pthread_join(philo->die_check, NULL);
	exit(0);
}
