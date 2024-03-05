/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:55:08 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/05 12:43:12 by ijaija           ###   ########.fr       */
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
*/
int	gathering_around_table(t_table *table)
{
	int		i;
	t_philo	*philos;

	table->philosophers = malloc(table->philo_nbr * sizeof(t_table));
	if (!table->philosophers)
		return (free(table->fork_locks), -1);
	i = 0;
	philos = table->philosophers;
	table->start_time = time_now();
	while (i < table->philo_nbr)
	{
		philos[i].id = i + 1;
		philos[i].left_fork_id = i;
		philos[i].right_fork_id = (i + 1) % table->philo_nbr;
		philos[i].times_ate = 0;
		philos[i].last_ate = table->start_time;
		philos[i].table = table;
		if (pthread_create(&philos[i].thread, NULL, dinning, &philos[i]) != 0)
			return (free(table->fork_locks), free(table->philosophers), -1);
		if (pthread_detach(philos[i].thread) != 0)
			return (free(table->fork_locks), free(table->philosophers), -1);
		i++;
	}
	return (0);
}

/*
* Initialising the following variables :
*	- fork locks mutexes
*	- end_flag_lock mutex
*	- end_flag = 0
*/
int	preparing_table(t_table *table)
{
	int	i;

	table->fork_locks = malloc(table->philo_nbr * sizeof(pthread_mutex_t));
	if (!table->fork_locks)
		return (-1);
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->fork_locks[i], NULL) != 0)
			return (free(table->fork_locks), -1);
		i++;
	}
	if (pthread_mutex_init(&table->printing, NULL) != 0)
		return (free(table->fork_locks), -1);
	if (pthread_mutex_init(&table->checking, NULL) != 0)
		return (free(table->fork_locks), -1);
	if (pthread_mutex_init(&table->end_lock, NULL) != 0)
		return (free(table->fork_locks), -1);
	table->end_flag = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (!(argc == 5 || argc == 6))
		return (write(2, "Invalide number of arguments\n", 29), -1);
	if (args_parse(argc, argv, &table) == -1)
		return (write(2, "Error in parsing!\n", 18), 1);
	else if (args_parse(argc, argv, &table) == -2)
		return (0);
	if (preparing_table(&table) == -1)
		return (write(2, "Error while preparing the table\n", 32), 1);
	if (gathering_around_table(&table) == -1)
		return (write(2, "Error while gathering philosphers\n", 35), 1);
	monitoring(&table);
	destroy_mutexes(&table);
	return (0);
}

int	did_they_ate_enough(t_table *table)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->checking);
		if (table->philosophers[i].times_ate >= table->times_must_eat
			&& table->times_must_eat != -1)
			n++;
		pthread_mutex_unlock(&table->checking);
		i++;
	}
	return (n);
}

void	monitoring(t_table *table)
{
	int	i;

	while (!is_finished(table))
	{
		if (check_if_a_philo_died(table))
			return ;
		usleep(100);
		if (table->times_must_eat != -1)
		{
			i = did_they_ate_enough(table);
			if (table->philo_nbr == i)
			{
				pthread_mutex_lock(&table->end_lock);
				table->end_flag = 1;
				pthread_mutex_unlock(&table->end_lock);
				return ;
			}
		}
	}
}
