/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:36:42 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/15 14:34:34 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define TINY 1024
# define PAGE getpagesize()

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <pthread.h>

typedef struct		s_large
{
	struct s_large	*next;
	struct s_large	*prev;
	size_t			size;
}					t_large;

typedef struct		s_node
{
	size_t			size;
	int				used;
	void			*ptr;
	struct s_node	*next;
}					t_node;

typedef struct		s_block
{
	struct s_block	*next;
	int				last;
	struct s_node	*nodes;
}					t_block;

typedef struct		s_malloc
{
	t_block		*tiny;
	t_block		*small;
	t_large		*large;
}					t_malloc;

t_malloc			g_m;

void				ft_print_mem();

void				free(void *ptr);

void				*find_alloc(t_node *node, size_t size);
void				*ft_malloc(size_t size);
void				*tiny_malloc(size_t size);
void				*small_malloc(size_t size);
void				*large_malloc(size_t size);

#endif
