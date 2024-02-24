/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:55:08 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/24 12:13:36 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
* It waits for any child process (-1) to change status (end execution)
* then it kill all other processes then it will close semaphores. 
*/
void	destroying_and_exiting(t_table *table)
{
	int	i;
	int	state;

	i = -1;
	while (++i < table->philo_nbr)
	{
		waitpid(-1, &state, 0);
		if (WEXITSTATUS(state) == 1)
		{
			i = -1;
			while (++i < table->philo_nbr)
				kill(table->philosophers[i].pid, SIGTERM);
			break ;
		}
	}
	sem_close(table->printing);
	sem_close(table->check);
	sem_close(table->forks);
	sem_unlink("printing_sem");
	sem_unlink("check_sem");
	sem_unlink("forks_sem");
}

int	main(int argc, char **argv)
{
	t_table		table;
	int			i;

	if (!(argc == 5 || argc == 6))
		return (write(2, "Invalide number of arguments\n", 29), -1);
	if (args_parse(argc, argv, &table) == -1)
		return (write(2, "Error in parsing!\n", 18), 1);
	i = -1;
	table.start_time = time_now();
	while (++i < table.philo_nbr)
	{
		table.philosophers[i].pid = fork();
		if (table.philosophers[i].pid == -1)
		{
			write(2, "Error while creating processes\n", 31);
			exit(1);
		}
		if (table.philosophers[i].pid == 0)
			dinning(&table.philosophers[i]);
	}
	destroying_and_exiting(&table);
	free(table.philosophers);
	return (0);
}
