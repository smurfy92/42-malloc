#include "includes/malloc.h"

int		main(void)
{

	printf("mallocs ---\n");
	char *str = ft_malloc(42);
	char *str2 = ft_malloc(42);
	int i = -1;

	printf("debugging ---\n");
	while (++i < 42)
	{
		str[i] = (i % 26)+ 'a';
		str2[i] = (i % 26)+ 'a';
	}
	str[i] = '\0';
	str2[i] = '\0';
	printf("str -> %s\n", str);
	printf("str -> %s\n", str2);
	ft_print_mem();
	return (0);
}