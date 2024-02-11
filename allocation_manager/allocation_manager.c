/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:17:00 by ijaija            #+#    #+#             */
/*   Updated: 2024/01/20 13:43:04 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./allocation_manager.h"

t_memslots	*session_init(void)
{
	t_memslots	*result;

	result = malloc(sizeof(t_memslots));
	if (!result)
		return (NULL);
	result->start = NULL;
	result->allocations = 0;
	result->end = NULL;
	return (result);
}

void	*ultra_malloc(t_memslots *slots, size_t size)
{
	t_memslot	*allocation;

	allocation = malloc(sizeof(t_memslot));
	if (!allocation)
		return (NULL);
	allocation->addr = malloc(size);
	if (!(allocation->addr))
		return (NULL);
	allocation->next = NULL;
	if (!slots->start)
	{
		slots->start = allocation;
		slots->end = NULL;
	}
	if (!slots->end)
		slots->end = allocation;
	else
	{
		slots->end->next = allocation;
		slots->end = allocation;
	}
	slots->allocations = slots->allocations + 1;
	return (allocation->addr);
}

void	end_session(t_memslots **slots)
{
	t_memslot	*start;
	t_memslot	*temp;

	start = (*slots)->start;
	while (start)
	{
		temp = start;
		free(temp->addr);
		free(temp);
		start = start->next;
	}
	free(*slots);
}
