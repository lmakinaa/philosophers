/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_manager.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:48:03 by ijaija            #+#    #+#             */
/*   Updated: 2024/01/20 18:47:57 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATION_MANAGER_H
# define ALLOCATION_MANAGER_H

# include <stdlib.h>

typedef struct s_memslots
{
	int				allocations;
	struct s_slot	*start;
	struct s_slot	*end;
}				t_memslots;

typedef struct s_slot
{
	void				*addr;
	struct s_slot		*next;
}				t_memslot;

t_memslots	*session_init(void);
void		*ultra_malloc(t_memslots *slots, size_t size);
void		end_session(t_memslots **slots);

#endif