/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gathering_around_table.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:45:25 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/01 11:49:43 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include "limits.h"

void	*dinning(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (philo->table->philos_created != 1)
		usleep(3);
	if (philo->id % 2 == 0)
		sleep_in_ms(philo->table->time_to_eat);
	while (1)
	{
		if (philo->table->end_flag)
			return (0);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}

int	gathering_around_table(t_table *table, t_memslots *slots)
{
	int			i;
	t_philo		*philosophers;

	table->philos = ultra_malloc(slots, table->philo_nbr * sizeof(t_philo));
	if (!table->philos)
		return (printf("Error while gathering the philosophers.\n"), -1);
	i = 0;
	philosophers = table->philos;
	while (i + 1 <= table->philo_nbr)
	{
		philosophers[i].id = i + 1;
		philosophers[i].r_f = (i + 1) % table->philo_nbr;
		philosophers[i].l_f = i ;
		philosophers[i].table = table;
		philosophers[i].last_eat = -1;
		philosophers[i].times_ate = 0;
		if (pthread_create(&(philosophers[i].thread), NULL, dinning,
				&philosophers[i]) == -1)
			return (printf("Error while gathering the philosophers.\n"), -1);
		i++;
	}
	table->start_time = time_now();
	table->philos_created = 1;
	return (0);
}
