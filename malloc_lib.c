/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:38:50 by jtranchi          #+#    #+#             */
/*   Updated: 2017/01/17 19:52:16 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void				*find_alloc(t_small *node, size_t size, int m_range)
{
	int i;

	i = -1;

	while (++i < 100)
	{
		if (node->tab[i] == 0)
		{
			node->tab[i] = size;
			return ((void *)node + ((i + 1) * m_range));
		}
	}
	return (NULL);
}

int					search_alloc(void *ptr, t_small *node, size_t m_range)
{
	int		i;

	i = 0;
	while (i < 100)
	{
		if (node->tab[i] != 0)
		{
			if (((void *)node + ((i + 1) * m_range)) == ptr)
			{
				node->tab[i] = 0;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int					is_tiny(void *ptr)
{
	t_small *node;

	node = m.tiny_m;
	while (node)
	{
		if (search_alloc(ptr, node, TINY_M))
			return (1);
		node = node->next;
	}
	return (0);
}

int					is_small(void *ptr)
{
	t_small *node;

	node = m.small_m;
	while (node)
	{
		if (search_alloc(ptr, node, SMALL_M))
			return (1);
		node = node->next;
	}
	return (0);
}

void				is_large(void *ptr)
{
	t_large *tmp;

	tmp = m.large_m;
	while (tmp)
	{
		if (((void *)tmp + sizeof(t_large)) == ptr)
		{
			if (!tmp->prev && !tmp->next)
				m.large_m = NULL;
			else if (!tmp->prev)
			{
				tmp->next->prev = NULL;
				m.large_m = tmp->next;
			}
			else if (!tmp->next)
				tmp->prev->next= NULL;
			else
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			munmap(tmp , tmp->size + sizeof(t_large));
		}
		tmp = tmp->next;
	}
}