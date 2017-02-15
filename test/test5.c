#include "../includes/malloc.h"

# define M (1024 * 1024)

void	print(char *s)
{
	write(1, s, strlen(s));
}

int	main()
{
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	show_alloc_mem();
}