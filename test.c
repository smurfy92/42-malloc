#include "includes/malloc.h"

int		main(void)
{

	printf("\n\n--- mallocs ---\n\n");
	int total = 0;
	char *str = ft_malloc(42);
	total += 42;
	char *str2 = ft_malloc(42);
	total += 42;
	int i = -1;

	printf("\n\n--- debugging ---\n\n");
	while (++i < 42)
	{
		str[i] = (i % 26)+ 'a';
		str2[i] = ((i + 2) % 26)+ 'a';
	}
	str[i] = '\0';
	str2[i] = '\0';
	printf("str -> %s\n", str);
	printf("str2 -> %s\n", str2);
	//ft_print_mem();

	int	y = 0;
	char *str3;
	//ft_print_mem();
	printf("\n\n--- lots of malloc ---\n\n");
	while ((++y * 42) < 4000)
	{
		str3 = ft_malloc(42);
		total += 42;
		ft_print_mem();
		printf("total -> %d\n", total);
		i = -1;
		while (++i < 42)
			str3[i] = (i * y  % 26)+ 'a';
		str3[i] = '\0';
		printf("str3 -> %s total -> %d\n", str3, total);
	}
	printf("end\n");
	// ft_print_mem();
	return (0);
}