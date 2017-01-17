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


void				init_mem(t_small *node)
{
	int i;

	i = -1;
	while (++i < 100)
		node->tab[i] = 0;
}

void				*find_alloc(t_small *node, size_t size, int m_range)
{
	int i;

	i = -1;

	while (++i < 100)
	{
		if (node->tab[i] == 0)
		{
			node->tab[i] = size;
			return ((void *)node + ((i + 1) * m_range));
		}
	}
	return (NULL);
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
		printf("tiny malloc");
	else if (size <= SMALL_M)
		printf("small malloc");
	else
		printf("big malloc");
	return (NULL);
}

void				check_large(void *ptr)
{
	t_large *tmp;


	tmp = m.large_m;
	while (tmp)
	{
		if (((void *)tmp + sizeof(t_large)) == ptr)
		{
			if (!tmp->prev && !tmp->next)
				m.large_m = NULL;
			else if (!tmp->prev)
			{
				tmp->next->prev = NULL;
				m.large_m = tmp->next;
			}
			else if (!tmp->next)
				tmp->prev->next= NULL;
			else
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			munmap(tmp , tmp->size + sizeof(t_large));
		}
		tmp = tmp->next;
	}
}

void				ft_free(void *ptr)
{
	check_large(ptr);
}

int 				main(void)
{
	char *str;
	char *str2;
	int i;
	str = large_malloc(42);
	i = -1;
	while (++i < 42)
		str[i] = 'a' + i % 26;
	return (0);
}