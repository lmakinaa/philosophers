/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:07:55 by ijaija            #+#    #+#             */
/*   Updated: 2024/01/25 12:29:20 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static long	part2(int i, int sign, const char *str, int passed)
{
	int		newi;
	long	res;
	long	max;

	newi = i;
	max = INT_MAX;
	res = 0;
	while (str[newi] && ft_isdigit(str[newi]))
	{
		res = res * 10 + (str[newi] - '0');
		if ((res > max && sign != -1) || (res > max + 1 && sign == -1))
			return (9999999999999);
		newi++;
	}
	if (str[newi] && !ft_isdigit(str[newi]))
		return (9999999999999);
	if (passed == 1 && res == 0)
		return (0);
	if (sign == 0)
		return (res);
	if (sign != 0 && res == 0)
		return (9999999999999);
	return (res * sign);
}

long	custom_atoi(const char *str)
{
	int	i;
	int	sign;
	int	passed;

	i = 0;
	sign = 0;
	passed = 0;
	while (str[i] && (str[i] == ' '))
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i] == '-')
			sign = -1;
		else if (str[i] == '+')
			sign = 1;
		if (ft_isdigit(str[i + 1]))
			passed = 1;
		i++;
	}
	return (part2(i, sign, str, passed));
}

int	args_parsing(int argc, char ***raw_argv, t_table *table)
{
	int		i;
	char	**argv;
	long	n;

	i = 1;
	argv = *raw_argv;
	while (i < argc)
	{
		n = custom_atoi(argv[i]);
		if (n == 9999999999999 || (n < 1 && i < 5) || (n < 0 && i == 5))
			return (-1);
		if (n > 200 && i == 1)
			return (-1);
		i++;
	}
	table->philo_nbr = custom_atoi(argv[1]);
	table->time_to_die = custom_atoi(argv[2]);
	table->time_to_eat = custom_atoi(argv[3]);
	table->time_to_sleep = custom_atoi(argv[4]);
	if (argc == 5)
		table->times_must_eat = -1;
	else if (argc == 6)
		table->times_must_eat = custom_atoi(argv[5]);
	table->start_time = time_now();
	return (0);
}
