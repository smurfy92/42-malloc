/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:21:07 by jtranchi          #+#    #+#             */
/*   Updated: 2017/01/18 14:21:05 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void				*realloc_sm(t_small *node, void *ptr, size_t size,
size_t m_range)
{
	int		i;

	i = -1;
	while (++i < 100)
	{
		if (node->tab[i] != 0)
		{
			if (((void *)node + ((i + 1) * m_range)) == ptr)
			{
				if (size <= TINY_M)
				{
					node->tab[i] = size;
					return (ptr);
				}
				else
				{
					node->tab[i] = 0;
					return (ft_memcpy(malloc(size), ptr, size));
				}
			}
		}
	}
	return (0);
}

void				*realloc_large(void *ptr, size_t size)
{
	void	*ret;
	t_large	*node;

	node = g_m.large_m;
	while (node)
	{
		if ((void *)node + sizeof(t_large) == ptr)
		{
			ret = malloc(size);
			ret = ft_memcpy(ret, ptr, size);
			free(ptr);
			return (ret);
		}
		node = node->next;
	}
	return (NULL);
}

void				*search_realloc(void *ptr, size_t size)
{
	void	*ret;
	t_small *node;

	node = g_m.tiny_m;
	while (node)
	{
		if ((ret = realloc_sm(node, ptr, size, TINY_M)))
			return (ret);
		node = node->next;
	}
	node = g_m.small_m;
	while (node)
	{
		if ((ret = realloc_sm(node, ptr, size, SMALL_M)))
			return (ret);
		node = node->next;
	}
	if ((ret = realloc_large(ptr, size)))
		return (ret);
	return (NULL);
}

void				*realloc(void *ptr, size_t size)
{
	if (size <= 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(size));
	else
		return (search_realloc(ptr, size));
	return (NULL);
}
