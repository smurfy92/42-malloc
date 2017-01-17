/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:36:42 by jtranchi          #+#    #+#             */
/*   Updated: 2017/01/17 19:52:23 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define TINY_M 512
#define SMALL_M 4096

typedef struct		s_large
{
	struct s_large	*next;
	struct s_large	*prev;
	size_t			size;
}					t_large;

typedef struct		s_small
{
	int				tab[100];
	struct s_small	*next;
}					t_small;

typedef struct		s_malloc
{
	t_small		*tiny_m;
	t_small		*small_m;
	t_large		*large_m;
}					t_malloc;

t_malloc			m;


void				*find_alloc(t_small *node, size_t size, int m_range);
int					search_alloc(void *ptr, t_small *node, size_t m_range);
int					is_tiny(void *ptr);
int					is_small(void *ptr);
void				is_large(void *ptr);

void				init_mem(t_small *node);
void				*ft_malloc(size_t size);
void				*tiny_malloc(size_t size);
void				*small_malloc(size_t size);
void				*large_malloc(size_t size);