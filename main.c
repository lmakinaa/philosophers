/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:37:52 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/01 11:50:18 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	f()
{
	system("leaks philo");
}

int preparing_table(int argc, char **argv, t_memslots *slots, t_table *table)
{
	int	i;

	if (!(argc == 5 || argc == 6))
		return (printf("Invalide number of arguments\n"), -1);
	if (args_parsing(argc, &argv, table) == -1)
		return (printf("Error\n"), -1);
	table->fork_lock = ultra_malloc(slots,
		(table->philo_nbr + 1) * sizeof(pthread_mutex_t));
	if (!table->fork_lock)
		return (-1);
	i = 1;
	while (i <= table->philo_nbr)
	{
		if (pthread_mutex_init(&table->fork_lock[i], NULL) == -1)
			return (printf("Error\n"), -1);
		i++;
	}
	if (pthread_mutex_init(&table->printing_lock, NULL) == -1)
		return (printf("Error\n"), -1);
	table->end_flag = 0;
	table->start_time = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_memslots	*slots;

	// atexit(f);
	slots = session_init();

	if (preparing_table(argc, argv, slots, &table) == -1)
		return (end_session(&slots), 1);
	if (gathering_around_table(&table, slots) == -1)
		return (end_session(&slots), 1);
	join_all(&table);
	start_monitoring(&table);
	end_session(&slots);
	return (0);
}
