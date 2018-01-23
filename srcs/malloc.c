/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:40:32 by jtranchi          #+#    #+#             */
/*   Updated: 2017/03/03 15:41:59 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static	t_block		*ft_create_block(size_t type)
{
	t_block			*tmp;

	tmp = (t_block *)mmap(0, type * 100, PROT_READ | PROT_WRITE,
	MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->last = 1;
	tmp->nodes = (void*)tmp + sizeof(t_block);
	tmp->nodes->size = (type * 100) - sizeof(t_block) - sizeof(t_node);
	tmp->nodes->used = 0;
	tmp->nodes->last = 1;
	tmp->nodes->ptr = NULL;
	tmp->nodes->next = NULL;
	tmp->next = NULL;
	return (tmp);
}

static	void		*large_malloc(size_t size)
{
	t_large			*tmp;

	if (!g_m.large)
	{
		g_m.large = mmap(0, size + sizeof(t_large),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_m.large->next = NULL;
		g_m.large->prev = NULL;
		g_m.large->size = size;
		pthread_mutex_unlock(&g_lock);
		return (g_m.large + 1);
	}
	else
	{
		tmp = g_m.large;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mmap(0, size + sizeof(t_large),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		tmp->next->prev = tmp;
		tmp->next->next = NULL;
		tmp->next->size = size;
		pthread_mutex_unlock(&g_lock);
		return (tmp->next + 1);
	}
}

static	void		*tiny_malloc(size_t size)
{
	t_block			*tmp;
	void			*ret;

	tmp = NULL;
	if (!g_m.tiny)
	{
		g_m.tiny = ft_create_block(TINY);
		return (find_alloc(g_m.tiny->nodes, size));
	}
	tmp = g_m.tiny;
	while (tmp)
	{
		if ((ret = find_alloc(tmp->nodes, size)))
			return (ret);
		if (tmp->last)
			break ;
		tmp = tmp->next;
	}
	tmp->next = ft_create_block(TINY);
	tmp->last = 0;
	return (find_alloc(tmp->next->nodes, size));
}

static	void		*small_malloc(size_t size)
{
	t_block			*tmp;
	void			*ret;

	tmp = NULL;
	if (!g_m.small)
	{
		g_m.small = ft_create_block(PAGE);
		return (find_alloc(g_m.small->nodes, size));
	}
	tmp = g_m.small;
	while (tmp)
	{
		if ((ret = find_alloc(tmp->nodes, size)))
			return (ret);
		if (tmp->last)
			break ;
		tmp = tmp->next;
	}
	tmp->next = ft_create_block(PAGE);
	tmp->last = 0;
	return (find_alloc(tmp->next->nodes, size));
}

void				*malloc(size_t size)
{
	static int		flag = 0;

	if (size <= 0)
		return (NULL);
	if (flag == 0)
	{
		if (pthread_mutex_init(&g_lock, NULL) != 0)
		{
			write(2, "mutex init failed\n", sizeof("mutex init failed\n"));
			return (NULL);
		}
		g_m.tiny = NULL;
		g_m.small = NULL;
		g_m.large = NULL;
		flag = 1;
	}
	pthread_mutex_lock(&g_lock);
	if (size < (size_t)TINY)
		return (tiny_malloc(size));
	else if (size < (size_t)PAGE)
		return (small_malloc(size));
	else
		return (large_malloc(size));
}
