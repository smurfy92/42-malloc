/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:37:35 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/12 19:03:46 by jtranchi         ###   ########.fr       */
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
		//printf("block %d\n", i++);
		nodes = block->nodes;
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
		if (node->size >= size + sizeof(t_node*) && node->used == 0)
		{
			node->used = 1;
			node->next = (void*)node + size + sizeof(t_node*);
			node->next->size = node->size - size - sizeof(t_node*);
			node->next->used = 0;
			node->next->next = NULL;
			node->size = size;
			pthread_mutex_unlock(&mutex);
			return (node + sizeof(t_node*));
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
		g_m.tiny = mmap(0, PAGE,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		printf("block address -> %p blocksize -> %lu\n", g_m.tiny, sizeof(t_block*));
		g_m.tiny->next = NULL;
		g_m.tiny->nodes = (void*)g_m.tiny + sizeof(t_block*);
		printf("node address -> %p nodesize -> %lu\n" , g_m.tiny->nodes, sizeof(t_node*));
		g_m.tiny->nodes->size = PAGE - sizeof(t_block*) - sizeof(t_node*) - 400;
		g_m.tiny->nodes->used = 0;
		g_m.tiny->nodes->next = NULL;
		return (find_alloc(g_m.tiny->nodes, size));
	}
	tmp = g_m.tiny;
	while (tmp != NULL)
	{
		printf("tmp\n");
		if ((ret = find_alloc(tmp->nodes, size)))
			return (ret);
		printf("la\n");
		tmp = tmp->next;
	}
	printf("la2\n");
	tmp->next = (void*)mmap(0, PAGE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
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
	printf("size -> %zu\n",size);
	pthread_mutex_lock(&mutex);
	if (size <= TINY)
		return (tiny_malloc(size));
	else if (size <= PAGE)
		return (small_malloc(size));
	else
		return (large_malloc(size));
}
