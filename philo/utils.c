/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:16:00 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/24 17:25:51 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(void)
{
	struct timeval	time;
	long			res;

	res = 0;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

int	join_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
	return (0);
}

void	print(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->printing);
	if (!philo->table->end_flag || str[0] == 'd')
	{
		printf("%ld %d %s\n",
			time_now() - philo->table->start_time, philo->id, str);
	}
	if (str[0] != 'd')
		pthread_mutex_unlock(&philo->table->printing);
}

int	time_skip(t_table *table, long time_to_stop)
{
	long	start;

	start = time_now();
	while (time_now() - start < time_to_stop && !table->end_flag)
		usleep(50);
	return (0);
}
