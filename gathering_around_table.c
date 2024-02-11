/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gathering_around_table.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:51:10 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/11 18:09:41 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
* It creates the philosophers and initialise the following variable :
*	- id
*	- left fork id
*	- right fork id
*	- times ate = 0
*	- last time ate = -1
*	- table
*	- start_time = time_now()
*	- philos_created_flag = 0 then $ = 1
*/
int	gathering_around_table(t_memslots *slots, t_table *table)
{
	int		i;
	t_philo	*philos;

	table->philosophers = ultra_malloc(slots,
		table->philo_nbr * sizeof(t_table));
	if (!table->philosophers)
		return (-1);
	table->philos_created_flag = 0;
	i = 0;
	philos = table->philosophers;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&philos[i].thread, NULL, dinning, &philos[i]) != 0)
			return (-1);
		philos[i].id = i + 1;
		philos[i].left_fork_id = i;
		philos[i].right_fork_id = (i + 1) % table->philo_nbr;
		philos[i].times_ate = 0;
		philos[i].last_ate = -1;
		philos[i].table = table;
		i++;
	}
	table->start_time = time_now();
	table->philos_created_flag = 1;
	return (0);
}
