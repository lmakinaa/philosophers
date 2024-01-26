/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gathering_around_table.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:45:25 by ijaija            #+#    #+#             */
/*   Updated: 2024/01/26 11:42:49 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include "limits.h"

	// i = 0;
	// while (i + 1 < table->philo_nbr)
	// {
	// 	pthread_join(philosophers[i].thread, NULL);
	// 	i++;
	// }

int	eating(t_philo *philo)
{
	printf("%ld %d is eating\n",
		philo->table->start_time - time_now(), philo->id);
	sleep_in_ms(philo->table->time_to_eat);
}

void	*dinning(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	
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
		philosophers[i].l_f = i + 1;
		philosophers[i].table = table;
		if (pthread_create(&(philosophers[i].thread), NULL, dinning,
				&philosophers[i]) == -1)
			return (printf("Error while gathering the philosophers.\n"), -1);
		i++;
	}
	return (0);
}
