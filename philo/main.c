/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:55:08 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/24 12:11:54 by ijaija           ###   ########.fr       */
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
		philos[i].think_print_flag = 1;
		philos[i].left_fork_id = i;
		philos[i].right_fork_id = (i + 1) % table->philo_nbr;
		philos[i].times_ate = 0;
		philos[i].last_ate = table->start_time;
		philos[i].table = table;
		if (pthread_create(&philos[i].thread, NULL, dinning, &philos[i]) != 0)
			return (free(table->fork_locks), free(table->philosophers), -1);
		i++;
	}
	return (0);
}

/*
* Infinite loop that checks if a philosopher died to send an end flag
*/
void	monitoring(t_table *table)
{
	int	i;
	int	loop_flag;

	loop_flag = 0;
	while (!loop_flag)
	{
		i = -1;
		table->philos_that_ate_enough = 0;
		while (++i < table->philo_nbr)
		{
			if (did_he_died_or_finished(&table->philosophers[i]))
			{
				loop_flag = 1;
				break ;
			}
		}
		usleep(100);
	}
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
	if (pthread_mutex_init(&table->end_flag_lock, NULL) != 0)
		return (free(table->fork_locks), -1);
	if (pthread_mutex_init(&table->printing, NULL) != 0)
		return (free(table->fork_locks), -1);
	if (pthread_mutex_init(&table->eat_lock, NULL) != 0)
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
		return (write(2, "Error while preparing the table", 31), 1);
	if (gathering_around_table(&table) == -1)
		return (write(2, "Error while gathering philosphers arount table", 46), 1);
	monitoring(&table);
	destroy_mutexes(&table);
}
