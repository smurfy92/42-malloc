#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define TINY_M 512-
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
	struct s_sm		*next;
}					t_small;

typedef struct		s_malloc
{
	t_small		*tiny_m;
	t_small		*small_m;
	t_large		*large_m;
}					t_malloc;


t_malloc			ms;


void	*malloc(size_t size)
{
	static int flag = 0;

	if (size <= 0)
		return (NULL);
	if (flag == 0)
	{
		ms.tiny_m = NULL;
		ms.small_m = NULL;
		ms.large_m = NULL;
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

int 	main(void)
{
	return (0);
}