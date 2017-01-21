/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:40:32 by jtranchi          #+#    #+#             */
/*   Updated: 2017/01/21 02:34:09 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void				*find_alloc(t_node *node, size_t size, int m_range)
{
	if (node && size && m_range)
		return (NULL);
	else
		return (NULL);
}

void				*malloc(size_t size)
{
	static int		flag = 0;

	if (size <= 0)
		return (NULL);
	if (flag == 0)
	{
		g_m.tiny = NULL;
		g_m.small = NULL;
		g_m.large = NULL;
		flag = 1;
	}
	if (size <= TINY)
		return (tiny_malloc(size));
	else if (size <= PAGE)
		return (small_malloc(size));
	else
		return (large_malloc(size));
}

void				*tiny_malloc(size_t size)
{
	t_node			*tmp;
	void			*ret;

	tmp = NULL;
	if (!g_m.tiny)
	{
		g_m.tiny = (t_node*)mmap(0, PAGE,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		init_mem(g_m.tiny);
		g_m.tiny->next = NULL;
		return (find_alloc(g_m.tiny, size, PAGE));
	}
	tmp = g_m.tiny;
	while (tmp)
	{
		if ((ret = find_alloc(tmp, size, PAGE)))
			return (ret);
		tmp = tmp->next;
	}
	tmp->next = (t_node*)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	init_mem(tmp->next);
	return (find_alloc(tmp->next, size, PAGE));
}

void				*small_malloc(size_t size)
{
	if (size)
		return (NULL);
	return (NULL);
}

void				*large_malloc(size_t size)
{
	t_large			*tmp;

	if (!g_m.large)
	{
		g_m.large = (t_large*)mmap(0, size + sizeof(t_large),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_m.large->next = NULL;
		g_m.large->prev = NULL;
		g_m.large->size = size;
		return ((void *)g_m.large + sizeof(t_large));
	}
	else
	{
		tmp = g_m.large;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_large*)mmap(0, size + sizeof(t_large),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->next = NULL;
		tmp->size = size;
		return ((void *)tmp + sizeof(t_large));
	}
}
