/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:37:35 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/15 14:21:29 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

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
		return ((void *)g_m.large + sizeof(t_large*));
	}
	else
	{
		tmp = g_m.large;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = mmap(0, size + sizeof(t_large),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->next = NULL;
		tmp->size = size;
		return ((void *)tmp + sizeof(t_large*));
	}
}

void				free(void *ptr)
{
	if (ptr)
		return ;
	return ;
}

void				*find_alloc(t_node *node, size_t size)
{
	while (node)
	{
		if (node->size >= size + sizeof(t_node) && node->used == 0)
		{
			node->used = 1;
			node->ptr = node + 1;
			node->next = node->ptr + size + 1;
			node->next->size = node->size - sizeof(t_node) - size - 1;
			node->next->used = 0;
			node->next->next = NULL;
			node->size = size + sizeof(t_node);
			return (node->ptr);
		}
		node = node->next;
	}
	return (NULL);
}

t_block 			*ft_create_block()
{
	t_block *tmp;


	tmp = (t_block *)mmap(0, PAGE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->last = 1;
	tmp->nodes = (void*)tmp + sizeof(t_block);
	tmp->nodes->size = PAGE - sizeof(t_block) - sizeof(t_node);
	tmp->nodes->used = 0;
	tmp->nodes->ptr = NULL;
	tmp->nodes->next = NULL;
	tmp->next = NULL;
	return (tmp);
}

void				*tiny_malloc(size_t size)
{
	t_block			*tmp;
	void			*ret;
	t_node 			*node;

	tmp = NULL;
	if (!g_m.tiny)
	{
		g_m.tiny = ft_create_block();
		return (find_alloc(g_m.tiny->nodes, size));
	}
	tmp = g_m.tiny;
	while (tmp)
	{
		if ((ret = find_alloc(tmp->nodes, size)))
			return (ret);
		if (tmp->last)
			break;
		tmp = tmp->next;
	}
	tmp->next = ft_create_block();
	tmp->last = 0;
	return (find_alloc(tmp->next->nodes, size));
}

void				*small_malloc(size_t size)
{
	t_block			*tmp;
	void			*ret;
	t_node 			*node;

	tmp = NULL;
	if (!g_m.small)
	{
		g_m.small = ft_create_block();
		return (find_alloc(g_m.small->nodes, size));
	}
	tmp = g_m.small;
	while (tmp)
	{
		if ((ret = find_alloc(tmp->nodes, size)))
			return (ret);
		if (tmp->last)
			break;
		tmp = tmp->next;
	}
	tmp->next = ft_create_block();
	tmp->last = 0;
	return (find_alloc(tmp->next->nodes, size));
}

void				*ft_malloc(size_t size)
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
