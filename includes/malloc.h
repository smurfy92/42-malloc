/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:36:42 by jtranchi          #+#    #+#             */
/*   Updated: 2017/01/21 02:28:57 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define TINY 512
# define PAGE 4096

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>

typedef struct		s_large
{
	struct s_large	*next;
	struct s_large	*prev;
	size_t			size;
}					t_large;

typedef struct		s_node
{
	size_t			size;
	struct s_node	*next;
}					t_node;

typedef struct		s_malloc
{
	t_node		*tiny;
	t_node		*small;
	t_large		*large;
}					t_malloc;

t_malloc			g_m;

void				*ft_memcpy(void *s1, const void *s2, size_t n);
void				free(void *ptr);

void				*find_alloc(t_node *node, size_t size, int m_range);
int					search_alloc(void *ptr, t_node *node, size_t m_range);
int					is_tiny(void *ptr);
int					is_small(void *ptr);
void				is_large(void *ptr);

void				init_mem(t_node *node);
void				*malloc(size_t size);
void				*tiny_malloc(size_t size);
void				*small_malloc(size_t size);
void				*large_malloc(size_t size);

void				*realloc_sm(t_node *node, void *ptr, size_t size,
	size_t m_range);
void				*realloc_large(void *ptr, size_t size);
void				*search_realloc(void *ptr, size_t size);
void				*realloc(void *ptr, size_t size);

#endif
