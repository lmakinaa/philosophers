/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:47:10 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/08 13:45:26 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	atoi_part2(int i, int sign, char *str, int *buffer)
{
	long	res;
	long	max;

	res = 0;
	max = INT_MAX;
	if (str[i] && ft_isdigit(str[i]))
	{
		while (str[i] && ft_isdigit(str[i]))
		{
			res = res * 10 + (str[i] - '0');
			if ((res > max && sign == 1) || (res > max + 1 && sign == -1))
				return (-1);
			i++;
		}
	}
	else
		return (-1);
	if (!ft_isdigit(str[i]) && str[i] != '\0')
		return (-1);
	*buffer = res * sign;
	return (0);
}

int	custom_atoi(char *str, int *buffer)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if ((str[i] && str[i] == ' ') || ft_isdigit(str[i])
		|| str[i] == '-' || str[i] == '+')
		while (str[i] && str[i] == ' ')
			i++;
	else
		return (-1);
	if (str[i] && ((str[i] == '-' || str[i] == '+') || ft_isdigit(str[i])))
	{
		if (str[i] == '-')
			sign = -1;
		else if (str[i] == '+')
			sign = 1;
		if (str[i] == '-' || str[i] == '+')
			i++;
	}
	else
		return (-1);
	return (atoi_part2(i, sign, str, buffer));
}

int	args_parse(int argc, char **argv, t_table *table)
{
	int		i;
	int		n;
	int		error;

	i = 1;
	while (i < argc)
	{
		error = custom_atoi(argv[i], &n);
		if (error == -1 || (n < 1 && i < 5) || (n < 0 && i == 5))
			return (-1);
		if (n > 200 && i == 1)
			return (-1);
		i++;
	}
	custom_atoi(argv[1], &table->philo_nbr);
	custom_atoi(argv[2], &table->time_to_die);
	custom_atoi(argv[3], &table->time_to_eat);
	custom_atoi(argv[4], &table->time_to_sleep);
	if (argc == 5)
		table->times_must_eat = -1;
	else if (argc == 6)
		custom_atoi(argv[5], &table->times_must_eat);
	if (argc == 6 && table->times_must_eat == 0)
		return (-2);
	return (0);
}
