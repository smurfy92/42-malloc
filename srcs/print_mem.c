/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 14:54:39 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/17 18:45:52 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		ft_pow(int nb, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

char	*ft_itoa_base(int value, int base)
{
	int		i;
	char	*nbr;
	int		neg;

	i = 1;
	neg = 0;
	if (value < 0)
	{
		if (base == 10)
			neg = 1;
		value *= -1;
	}
	while (ft_pow(base, i) - 1 < value)
		i++;
	nbr = (char*)malloc(sizeof(nbr) * i);
	nbr[i + neg] = '\0';
	while (i-- > 0)
	{
		nbr[i + neg] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	if (neg)
		nbr[0] = '-';
	return (nbr);
}

void				ft_print_addr(void *ptr, int endl)
{
	char *str;

	str = ft_itoa_base((int)ptr, 16);
	ft_putstr("0x10");
	if (endl)
		ft_putendl(str);
	else
		ft_putstr(str);
}

void				ft_print_tiny()
{
	t_node			*nodes;
	t_block			*block;
	int				total;

	block = g_m.tiny;
	total = 0;
	while (block)
	{
		ft_putstr("TINY : ");
		ft_print_addr((void *)block, 1);
		nodes = block->nodes;
		total += sizeof(t_block);
		while (nodes)
		{
			printf("%p - %p : %zu octets\n", nodes + 1, nodes + 1 + nodes->size - sizeof(t_node), nodes->size - sizeof(t_node));
			total += nodes->size;
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
	int total;
	total = 0;
	while (block)
	{
		total = 0;
		printf("\nSMALL [%d]: -> %p \n", i++, block);
		nodes = block->nodes;
		total += sizeof(t_block) - 1;
		while (nodes)
		{
			printf("node -> %p", nodes);
			printf("%p - %p : %zu octets", nodes->ptr, nodes->ptr + nodes->size, nodes->size);
			printf(" used -> %d\n", nodes->used);
			total += nodes->size + 1;
			total += sizeof(t_node);
			nodes = nodes->next;
		}
		printf("total -> %d\n",total);
		if (block->last)
			break;
		block = block->next;
	}
}

void				ft_print_big()
{
	t_large *block;
	block = g_m.large;

	int i = 0;
	while (block)
	{
		printf("\nLARGE [%d]: -> %p \n", i++, block);
		printf("%p - %p : %zu octets\n", (void*)block + sizeof(t_block*), (void*)block + sizeof(t_node*) + block->size, block->size);
		block = block->next;
	}
}


void				show_alloc_mem()
{
		ft_print_tiny();
		ft_print_small();
		ft_print_big();
}
