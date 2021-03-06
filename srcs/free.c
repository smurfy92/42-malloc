/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:52:51 by jtranchi          #+#    #+#             */
/*   Updated: 2018/01/29 12:55:33 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void				*ft_mystrcpy(char *dst, const char *src, int size,
int size2)
{
	int i;

	i = -1;
	while (++i < size2 && i < size)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

static	int			free_tiny(void *ptr)
{
	t_block			*block;
	t_node			*node;

	block = g_m.tiny;
	while (block)
	{
		node = block->nodes;
		while (node)
		{
			if (node->ptr == ptr)
			{
				node->used = 0;
				return (1);
			}
			node = node->next;
		}
		if (block->last)
			break ;
	}
	return (0);
}

static	int			free_small(void *ptr)
{
	t_block			*block;
	t_node			*node;

	block = g_m.small;
	while (block)
	{
		node = block->nodes;
		while (node)
		{
			if (node->ptr == ptr)
			{
				node->used = 0;
				return (1);
			}
			node = node->next;
		}
		if (block->last)
			break ;
	}
	return (0);
}

static	int			free_large(void *ptr)
{
	t_large			*node;

	node = g_m.large;
	while (node)
	{
		if ((void*)node + sizeof(t_large) == ptr)
		{
			if (!node->prev)
			{
				if (node->next)
					g_m.large = node->next;
				else
					g_m.large = NULL;
			}
			else
			{
				node->prev->next = node->next;
				(node->next) ? (node->next->prev = node->prev) : 0;
			}
			munmap(node, node->size + sizeof(t_large));
			return (1);
		}
		node = node->next;
	}
	return (0);
}

void				free(void *ptr)
{
	if (ptr == NULL)
		return ;
	if (free_tiny(ptr))
		return ;
	if (free_small(ptr))
		return ;
	if (free_large(ptr))
		return ;
}
