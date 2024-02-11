/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:51:21 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/10 20:46:26 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	table->end_flag = 0;
	return (0);
}
