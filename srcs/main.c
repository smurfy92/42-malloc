/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:37:35 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/13 12:44:54 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void				ft_print_tiny()
{
	t_node *nodes;
	t_block *block;
	block = g_m.tiny;

	int i = 0;
	while (block)
	{
		printf("\n\n\n\nTINY [%d]: -> %p \n", i++, block);
		nodes = block->nodes;
		while (nodes)
		{
			printf("%p - %p : %zu octets\n", (void*)nodes + sizeof(t_node*), (void*)nodes + sizeof(t_node*) + nodes->size, nodes->size);
			nodes = nodes->next;
		}
		if (block->last)
			break;
		block = block->next;
	}
}


void				ft_print_mem()
{
		ft_print_tiny();
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
		if (node->size >= size + sizeof(t_node*) && node->used == 0)
		{
			printf("before -> %zu",g_m.tiny->nodes->size);
			node->used = 1;
			node->next = (void*)node + size + sizeof(t_node*);
			node->next->size = node->size - size - sizeof(t_node*);
			node->next->used = 0;
			node->next->next = NULL;
			node->size = size;
			pthread_mutex_unlock(&mutex);
			printf("sizeafter -> %zu",g_m.tiny->nodes->size);
			return (node + sizeof(t_node*));
		}
		node = node->next;
	}
	printf("la3\n");
	return (NULL);
}

void				*tiny_malloc(size_t size)
{
	t_block			*tmp;
	void			*ret;
	t_node 			*node;

	tmp = NULL;
	if (!g_m.tiny)
	{
		g_m.tiny = mmap(0, PAGE,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		printf("block address -> %p blocksize -> %lu\n", g_m.tiny, sizeof(t_block*));
		g_m.tiny->next = NULL;
		g_m.tiny->last = 1;
		g_m.tiny->nodes = (void*)g_m.tiny + sizeof(t_block*);
		printf("node address -> %p nodesize -> %lu\n" , g_m.tiny->nodes, sizeof(t_node*));
		g_m.tiny->nodes->size = PAGE - sizeof(t_block*) - sizeof(t_node*) - 400;
		g_m.tiny->nodes->used = 0;
		g_m.tiny->nodes->next = NULL;
		return (find_alloc(g_m.tiny->nodes, size));
		printf("iciicitoto\n");
	}
	tmp = g_m.tiny;
	printf("before before size -> %zu\n",g_m.tiny->nodes->size);
	while (tmp)
	{
		printf("tmp -> %p\n", tmp);
		if ((ret = find_alloc(tmp->nodes, size)))
			return (ret);
		if (tmp->last)
			break;
		tmp = tmp->next;
	}
	tmp->last = 0;
	printf("la2\n");
	tmp->next = (void*)mmap(0, PAGE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->next->last = 1;
	tmp->next->nodes = (void*)tmp->next + sizeof(t_block*);
	tmp->next->nodes->size = PAGE - sizeof(t_block*) - sizeof(t_node*) - 400;
	tmp->next->nodes->used = 0;
	tmp->next->nodes->next = NULL;
	tmp->next->next = NULL;
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
	//printf("size -> %zu\n",size);
	pthread_mutex_lock(&mutex);
	if (size <= TINY)
		return (tiny_malloc(size));
	else if (size <= PAGE)
		return (small_malloc(size));
	else
		return (large_malloc(size));
}
