/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:40:32 by jtranchi          #+#    #+#             */
/*   Updated: 2017/01/17 19:41:22 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void				init_mem(t_small *node)
{
	int i;

	i = -1;
	while (++i < 100)
		node->tab[i] = 0;
}


void				*ft_malloc(size_t size)
{
	static int 		flag = 0;

	if (size <= 0)
		return (NULL);
	if (flag == 0)
	{
		m.tiny_m = NULL;
		m.small_m = NULL;
		m.large_m = NULL;
		flag = 1;
	}
	if (size <= TINY_M)
		return (tiny_malloc(size));
	else if (size <= SMALL_M)
		return (small_malloc(size));
	else
		return (large_malloc(size));
}

void				*tiny_malloc(size_t size)
{
	t_small 		*tmp;
	void			*ret;

	if (!m.tiny_m)
	{

		m.tiny_m = (t_small*)mmap(0, TINY_M * 101 + sizeof(t_small), PROT_READ | PROT_WRITE , MAP_ANON | MAP_PRIVATE, -1 , 0);
		init_mem(m.tiny_m);
		m.tiny_m->next = NULL;
		if ((ret = find_alloc(m.tiny_m, size , TINY_M)))
			return (ret);
	}
	tmp = m.tiny_m;
	while (tmp)
	{
		if ((ret = find_alloc(m.tiny_m, size , TINY_M)))
			return (ret);
		tmp = tmp->next;
	}
	tmp->next = (t_small*)mmap(0, TINY_M * 101 + sizeof(t_small), PROT_READ | PROT_WRITE , MAP_ANON | MAP_PRIVATE, -1 , 0);
	init_mem(tmp->next);
	return (find_alloc(tmp->next, size , TINY_M));
}


void				*small_malloc(size_t size)
{
	t_small 		*tmp;
	void			*ret;

	if (!m.small_m)
	{

		m.small_m = (t_small*)mmap(0, SMALL_M * 101 + sizeof(t_small), PROT_READ | PROT_WRITE , MAP_ANON | MAP_PRIVATE, -1 , 0);
		init_mem(m.small_m);
		m.small_m->next = NULL;
		if ((ret = find_alloc(m.small_m, size , SMALL_M)))
			return (ret);
	}
	tmp = m.small_m;
	while (tmp)
	{
		if ((ret = find_alloc(m.small_m, size , SMALL_M)))
			return (ret);
		tmp = tmp->next;
	}
	tmp->next = (t_small*)mmap(0, SMALL_M * 101 + sizeof(t_small), PROT_READ | PROT_WRITE , MAP_ANON | MAP_PRIVATE, -1 , 0);
	init_mem(tmp->next);
	return (find_alloc(tmp->next, size , SMALL_M));
}

void				*large_malloc(size_t size)
{
	t_large 		*tmp;

	if (!m.large_m)
	{
		m.large_m = (t_large*)mmap(0, size + sizeof(t_large), PROT_READ | PROT_WRITE , MAP_ANON | MAP_PRIVATE, -1 , 0);
		m.large_m->next = NULL;
		m.large_m->prev = NULL;
		m.large_m->size = size;
		return ((void *)m.large_m + sizeof(t_large));
	}
	else
	{
		tmp = m.large_m;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_large*)mmap(0, size + sizeof(t_large), PROT_READ | PROT_WRITE , MAP_ANON | MAP_PRIVATE, -1 , 0);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->next = NULL;
		tmp->size = size;
		return ((void *)tmp + sizeof(t_large));
	}
}