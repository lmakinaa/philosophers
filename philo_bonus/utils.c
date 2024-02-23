/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:16:00 by ijaija            #+#    #+#             */
/*   Updated: 2024/02/23 20:34:08 by ijaija           ###   ########.fr       */
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

int	time_skip(t_philo *philo, long time_to_stop)
{
	long	start;

	start = time_now();
	while (time_now() - start < time_to_stop && !philo->table->end_flag)
		usleep(100);
	return (0);
}

int	init_semaphores(t_table *table)
{
	sem_unlink("printing_sem");
	sem_unlink("check_sem");
	sem_unlink("forks_sem");
	table->printing = sem_open("printing_sem", O_CREAT, 0644, 1);
	table->check = sem_open("check_sem", O_CREAT, 0644, 1);
	table->forks = sem_open("forks_sem", O_CREAT, 0644, table->philo_nbr);
	if (table->printing == SEM_FAILED
		|| table->check == SEM_FAILED || table->forks == SEM_FAILED)
	{
		write(2, "Error while opening semaphores\n", 31);
		exit(1);
	}
	return (0);
}

void	print(t_philo *philo, char *str)
{
	long	start;

	sem_wait(philo->table->printing);
	if (!philo->table->end_flag)
	{
		start = philo->table->start_time;
		printf("%ld %d %s\n", time_now() - start, philo->id, str);
	}
	if (str[0] != 'd')
		sem_post(philo->table->printing);
}
