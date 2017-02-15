/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:36:42 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/15 17:59:16 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define TINY getpagesize() / 4
# define PAGE getpagesize()

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <pthread.h>
# include <string.h>

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
	int				last;
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

void				show_alloc_mem();
void				free(void *ptr);
void				*malloc(size_t size);
void				*tiny_malloc(size_t size);
void				*small_malloc(size_t size);
void				*large_malloc(size_t size);

#endif
