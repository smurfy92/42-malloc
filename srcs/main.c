/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:37:35 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/11 13:26:58 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void				ft_print_mem()
{
	t_node *nodes;
	t_block *block;
	block = g_m.tiny;
	printf("\n\n\n\nblockaddress -> %p \n", block);
	int i = 0;
	while (block)
	{
		//printf("block %d\n", i++);
		nodes = block->nodes;
		while (nodes)
		{
			printf("node -> %p , size -> %zu\n", nodes, nodes->size);
			nodes = nodes->next;
		}
		block = block->next;
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
	t_node *tmp;
	while (node)
	{
		if (node->size >= size && node->used == 0)
		{
			node->used = 1;
			node->next = (void *)node + size;
			tmp = (t_node*)node->next;
			tmp->size = node->size - size;
			tmp->used = 0;
			tmp->next = NULL;
			node->size = size;
			pthread_mutex_unlock(&mutex);
			return (node + sizeof(node));
		}
		node = node->next;
	}
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
		tmp = (void*)mmap(0, PAGE,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		printf("block address -> %p blocksize -> %lu\n", tmp, sizeof(t_block*));
		g_m.tiny = (t_block*)tmp;
		g_m.tiny->nodes = (void*)g_m.tiny + ((sizeof(g_m.tiny) / 16) + 1) * 16;
		node = (t_node*)g_m.tiny->nodes;
		printf("node address -> %p nodesize -> %lu\n" , g_m.tiny->nodes, sizeof(g_m.tiny->nodes));
		node->size = PAGE - ((sizeof(g_m.tiny) / 16) + 1) * 16;
		node->used = 0;
		node->next = NULL;
		g_m.tiny->next = NULL;
		return (find_alloc(g_m.tiny->nodes, size));
	}
	tmp = g_m.tiny;
	while (tmp)
	{
		printf("ici\n");
		if ((ret = find_alloc(tmp->nodes, size)))
			return (ret);
		tmp = tmp->next;
	}
	printf("icilalala\n");
	tmp->next->nodes = (void*)mmap(0, PAGE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->next->nodes->size = PAGE - (sizeof(tmp->next) *2);
	tmp->next->nodes->used = 0;
	tmp->next->nodes->next = NULL;
	tmp->next->next = NULL;
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
	size = (((size + sizeof(t_node)) / 16) + 1) * 16;
	pthread_mutex_lock(&mutex);
	if (size <= TINY)
		return (tiny_malloc(size));
	else if (size <= PAGE)
		return (small_malloc(size));
	else
		return (large_malloc(size));
}
