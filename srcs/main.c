/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:37:35 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/10 14:40:02 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"


void				ft_print_mem()
{
	t_node *nodes;
	nodes = g_m.tiny->nodes;
	while (nodes)
	{
		printf("node -> %p , size -> %zu\n", nodes, nodes->size);
		nodes = nodes->next;
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
		if (node->size >= (size + sizeof(node)) && node->used == 0)
		{
			node->used = 1;
			node->next = (t_node *)node - sizeof(node) - node->size;
			node->next->size = node->size - sizeof(node) - size;
			node->next->used = 0;
			node->size = size;
			return (node - sizeof(node));
		}
		node = node->next;
	}
	return (NULL);
}

void				*tiny_malloc(size_t size)
{
	t_block			*tmp;
	void			*ret;

	tmp = NULL;
	if (!g_m.tiny)
	{
		g_m.tiny = (t_block*)mmap(0, PAGE,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_m.tiny->nodes = (t_node*)g_m.tiny - sizeof(g_m.tiny);
		g_m.tiny->nodes->size = PAGE - sizeof(g_m.tiny);
		g_m.tiny->nodes->used = 0;
		g_m.tiny->nodes->next = NULL;
		g_m.tiny->next = NULL;
		return (find_alloc(g_m.tiny->nodes, size));
	}
	tmp = g_m.tiny;
	while (tmp)
	{
		if ((ret = find_alloc(tmp->nodes, size)))
			return (ret);
		tmp = tmp->next;
	}
	tmp->next = (t_block*)mmap(0, PAGE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->next->nodes = NULL;
	//init_mem(tmp->next);
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
