/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 14:54:39 by jtranchi          #+#    #+#             */
/*   Updated: 2017/03/03 15:40:39 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static	int			ft_print_tiny(void)
{
	t_node			*nodes;
	t_block			*block;
	int				total;

	total = 0;
	block = g_m.tiny;
	while (block)
	{
		ft_putstr("TINY  : ");
		ft_print_addr((intmax_t)block, 1);
		nodes = block->nodes;
		while (nodes)
		{
			if (!nodes->last)
			{
				ft_print_node(nodes);
				total += nodes->size - sizeof(t_node);
			}
			nodes = nodes->next;
		}
		if (block->last)
			return (total);
		block = block->next;
	}
	return (total);
}

static	int			ft_print_small(void)
{
	t_node		*nodes;
	t_block		*block;
	int			total;

	total = 0;
	block = g_m.small;
	while (block)
	{
		ft_putstr("SMALL : ");
		ft_print_addr((intmax_t)block, 1);
		nodes = block->nodes;
		while (nodes)
		{
			if (!nodes->last)
			{
				ft_print_node(nodes);
				total += nodes->size - sizeof(t_node);
			}
			nodes = nodes->next;
		}
		if (block->last)
			return (total);
		block = block->next;
	}
	return (total);
}

static	int			ft_print_big(void)
{
	t_large		*block;
	int			total;

	block = g_m.large;
	total = 0;
	while (block)
	{
		ft_putstr("LARGE : ");
		ft_print_addr((intmax_t)block, 1);
		total += block->size;
		printf("%p - %p : %zu octets\n", (void*)block + sizeof(t_block*),
		(void*)block + sizeof(t_node*) + block->size, block->size);
		block = block->next;
	}
	return (total);
}

void				show_alloc_mem(void)
{
	int total;

	total = 0;
	total += ft_print_tiny();
	total += ft_print_small();
	total += ft_print_big();
	ft_putstr("total : ");
	ft_putnbr(total);
	ft_putstr("\n");
}
