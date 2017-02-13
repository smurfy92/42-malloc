/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 14:54:39 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/13 15:39:13 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

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
			printf("%p - %p : %zu octets", (void*)nodes + sizeof(t_node*), (void*)nodes + sizeof(t_node*) + nodes->size, nodes->size);
			printf(" used -> %d\n", nodes->used);
			nodes = nodes->next;
		}
		if (block->last)
			break;
		block = block->next;
	}
}

void				ft_print_small()
{
	t_node *nodes;
	t_block *block;
	block = g_m.small;

	int i = 0;
	while (block)
	{
		printf("\n\n\n\nSMALL [%d]: -> %p \n", i++, block);
		nodes = block->nodes;
		while (nodes)
		{
			printf("%p - %p : %zu octets", (void*)nodes + sizeof(t_node*), (void*)nodes + sizeof(t_node*) + nodes->size, nodes->size);
			printf(" used -> %d\n", nodes->used);
			nodes = nodes->next;
		}
		if (block->last)
			break;
		block = block->next;
	}
}

void				ft_print_big()
{
	t_node *nodes;
	t_large *block;
	block = g_m.large;

	int i = 0;
	while (block)
	{
		printf("\n\n\n\nLARGE [%d]: -> %p \n", i++, block);
		printf("%p - %p : %zu octets\n", (void*)block + sizeof(t_block*), (void*)block + sizeof(t_node*) + block->size, block->size);
		block = block->next;
	}
}


void				ft_print_mem()
{
		ft_print_tiny();
		ft_print_small();
		ft_print_big();
}