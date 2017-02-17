/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:40:32 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/17 13:20:47 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static	void		*find_alloc(t_node *node, size_t size)
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
			return (node->ptr);
		}
		if (node->size < size + sizeof(t_node))
			break ;
		node = node->next;
	}
	return (NULL);
}

static	t_block		*ft_create_block(size_t type)
{
	t_block			*tmp;

	tmp = (t_block *)mmap(0, type * 100, PROT_READ | PROT_WRITE,
	MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->last = 1;
	tmp->nodes = (void*)tmp + sizeof(t_block);
	tmp->nodes->size = (type * 100) - sizeof(t_block) - sizeof(t_node);
	tmp->nodes->used = 0;
	tmp->nodes->last = 1;
	tmp->nodes->ptr = NULL;
	tmp->nodes->next = NULL;
	tmp->next = NULL;
	return (tmp);
}

void				*large_malloc(size_t size)
{
	t_large			*tmp;

	if (!g_m.large)
	{
		g_m.large = mmap(0, size + sizeof(t_large),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_m.large->next = NULL;
		g_m.large->prev = NULL;
		g_m.large->size = size;
		return (g_m.large + 1);
	}
	else
	{
		tmp = g_m.large;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mmap(0, size + sizeof(t_large),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->next = NULL;
		tmp->size = size;
		return (tmp + 1);
	}
}

void				*tiny_malloc(size_t size)
{
	t_block			*tmp;
	void			*ret;

	tmp = NULL;
	if (!g_m.tiny)
	{
		g_m.tiny = ft_create_block(TINY);
		return (find_alloc(g_m.tiny->nodes, size));
	}
	tmp = g_m.tiny;
	while (tmp)
	{
		if ((ret = find_alloc(tmp->nodes, size)))
			return (ret);
		if (tmp->last)
			break ;
		tmp = tmp->next;
	}
	tmp->next = ft_create_block(TINY);
	tmp->last = 0;
	return (find_alloc(tmp->next->nodes, size));
}

void				*small_malloc(size_t size)
{
	t_block			*tmp;
	void			*ret;

	tmp = NULL;
	if (!g_m.small)
	{
		g_m.small = ft_create_block(PAGE);
		return (find_alloc(g_m.small->nodes, size));
	}
	tmp = g_m.small;
	while (tmp)
	{
		if ((ret = find_alloc(tmp->nodes, size)))
			return (ret);
		if (tmp->last)
			break ;
		tmp = tmp->next;
	}
	tmp->next = ft_create_block(PAGE);
	tmp->last = 0;
	return (find_alloc(tmp->next->nodes, size));
}
