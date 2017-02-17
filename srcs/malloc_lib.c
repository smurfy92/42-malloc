/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:40:44 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/17 18:43:37 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*find_alloc(t_node *node, size_t size)
{
	while (node)
	{
		if (node->size >= size + sizeof(t_node) && node->used == 0)
		{
			node->used = 1;
			if (node->last)
			{
				node->ptr = node + 1;
				node->next = node->ptr + size + 1;
				node->next->size = node->size - sizeof(t_node) - size - 1;
				node->next->used = 0;
				node->last = 0;
				node->next->last = 1;
				node->next->next = NULL;
				node->size = size + sizeof(t_node);
			}
			pthread_mutex_unlock(&lock);
			return (node->ptr);
		}
		node = node->next;
	}
	return (NULL);
}
