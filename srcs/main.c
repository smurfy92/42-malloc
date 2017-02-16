/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:37:35 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/16 17:23:40 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void			*find_tiny(void *ptr)
{
	t_block		*block;
	t_node		*node;

	block = g_m.tiny;
	while (block)
	{
		node = block->nodes;
		while (node)
		{
			if (node->ptr == ptr)
				return (node->ptr);
			node = node->next;
		}
		if (block->last)
			break ;
		block = block->next;
	}
	return (NULL);
}

void			*find_small(void *ptr)
{
	t_block		*block;
	t_node		*node;

	block = g_m.small;
	while (block)
	{
		node = block->nodes;
		while (node)
		{
			if (node->ptr == ptr)
				return (node->ptr);
			node = node->next;
		}
		if (block->last)
			break ;
		block = block->next;
	}
	return (NULL);
}

void			*find_large(void *ptr)
{
	t_large		*block;

	block = g_m.large;
	while (block)
	{
		if ((void*)block + sizeof(t_large) == ptr)
			return (block);
		block = block->next;
	}
	return (NULL);
}

void			*find_alloc(void *ptr)
{
	void *ret;

	if ((ret = find_tiny(ptr)))
		return (ret);
	if ((ret = find_small(ptr)))
		return (ret);
	if ((ret = find_large(ptr)))
		return (ret);
	return (NULL);
}

char	*ft_strcpy(char *dst, const char *src, int size,  int size2)
{
	int i;

	i = -1;
	while (++i < size2 && i < size)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}


void 			*realloc(void *ptr, size_t size)
{
	t_node		*ret;

	if (size <= 0)
		return (NULL);
	if ((ret = find_alloc(ptr)))
	{
		if (ret->size - sizeof(t_node) >= size)
			return (ret);
		else
			return (ft_strcpy(malloc(size), ret->ptr, ret->size - sizeof(t_node), size));
	}
	else
		return (NULL);
	return (NULL);
}

void			*malloc(size_t size)
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
	if (size <= (size_t)TINY)
		return (tiny_malloc(size));
	else if (size <= (size_t)PAGE)
		return (small_malloc(size));
	else
		return (large_malloc(size));
}
