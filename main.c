/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:55:08 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/12 16:22:49 by ijaija           ###   ########.fr       */
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
int	gathering_around_table(t_memslots *slots, t_table *table)
{
	int		i;
	t_philo	*philos;

	table->philosophers = ultra_malloc(slots,
		table->philo_nbr * sizeof(t_table));
	if (!table->philosophers)
		return (-1);
	i = 0;
	philos = table->philosophers;
	table->start_time = time_now(); 
	while (i < table->philo_nbr)
	{
		if (pthread_create(&philos[i].thread, NULL, dinning, &philos[i]) != 0)
			return (-1);
		philos[i].id = i + 1;
		philos[i].left_fork_id = i;
		philos[i].right_fork_id = (i + 1) % table->philo_nbr;
		philos[i].times_ate = 0;
		philos[i].last_ate = table->start_time;
		philos[i].table = table;
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
		while (++i < table->philo_nbr)
		{
			if (did_he_died(&table->philosophers[i]))
			{
				loop_flag = 1;
				break;
			}
		}
		usleep(10);
	}
}

/*
* Initialising the following variables :
*	- fork locks mutexes
*	- end_flag_lock mutex
*	- end_flag = 0
*/
int	preparing_table(t_memslots *slots, t_table *table)
{
	int	i;

	table->fork_locks = ultra_malloc(slots,
		table->philo_nbr * sizeof(pthread_mutex_t));
	if (!table->fork_locks)
		return (end_session(&slots), -1);
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->fork_locks[i], NULL) != 0)
			return (end_session(&slots), -1);
		i++;
	}
	if (pthread_mutex_init(&table->end_flag_lock, NULL) != 0)
		return (end_session(&slots), -1);
	if (pthread_mutex_init(&table->printing, NULL) != 0)
		return (end_session(&slots), -1);
	if (pthread_mutex_init(&table->eat_lock, NULL) != 0)
		return (end_session(&slots), -1);
	if (pthread_mutex_init(&table->start_time_lock, NULL) != 0)
		return (end_session(&slots), -1);
	table->end_flag = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_memslots	*slots;
	t_table		table;

	if (!(argc == 5 || argc == 6))
		return (printf("Invalide number of arguments\n"), -1);

	slots = session_init();
	if (!slots)
		return (printf("Error!\n"), 1);
	if (args_parse(argc, argv, &table) == -1)
		return (printf("Error while parsing the arguments!\n"), 1);
	if (preparing_table(slots, &table) == -1)
		return (printf("Error while preparing the table"), 1);
	if (gathering_around_table(slots, &table))
		return (printf("Error while gathering philosphers arount table"), 1);
	
	monitoring(&table);
	join_all(&table);
	destroy_mutexes(&table);
	end_session(&slots);
}

