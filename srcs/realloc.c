/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:13:46 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/17 18:41:32 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static	void		*find_tiny(void *ptr)
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

static	void		*find_small(void *ptr)
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

static	void		*find_large(void *ptr)
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

void				*check_large(void *ptr, size_t size)
{
	t_large		*large;
	t_large		*large2;

	if ((large = find_large(ptr)))
	{
		if (large->size - sizeof(t_large) >= size)
			return (large);
		else
		{
			large2 = ft_strcpy(malloc(size),
			(char *)large + sizeof(t_large), large->size, size);
			free(large);
			return (large2);
		}
	}
	return (NULL);
}

void				*realloc(void *ptr, size_t size)
{
	t_node		*ret;
	t_node		*ret2;

	if (size <= 0)
		return (NULL);
	if ((ret = (!find_tiny(ptr) ? find_small(ptr) : 0)))
	{
		if (ret->size - sizeof(t_node) >= size)
			return (ret);
		else
		{
			ret2 = ft_strcpy(malloc(size),
			ret->ptr, ret->size - sizeof(t_node), size);
			free(ret);
			return (ret2);
		}
	}
	else
		return (check_large(ptr, size));
}
