/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:11:59 by ijaija            #+#    #+#             */
/*   Updated: 2024/01/25 12:32:10 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long	time_now(void)
{
	struct timeval	time;
	long			res;

	res = 0;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	res = (time.tv_sec * 1000) + (time.tv_sec / 10000);
	return (res);
}

void	sleep_in_ms(long ms)
{
	long	start;

	start = time_now();
	while ((time_now() - start) < ms)
		usleep(500);
}
