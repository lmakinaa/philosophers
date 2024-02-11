/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:55:08 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/11 18:49:42 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_table *table)
{
	int	i;
	int	flag;

	flag = 0;
	while (!flag)
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (time_now() - table->philosophers[i].last_ate >= table->time_to_die
				&& table->philosophers[i].last_ate != -1)
			{
				table->end_flag = 1;
				printf("%ld-->someone died\n", time_now() - table->philosophers[i].last_ate);
				flag = 1;
				break;
			}
			i++;
		}
	}
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
	end_session(&slots);
}
