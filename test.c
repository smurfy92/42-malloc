#include "includes/malloc.h"

int		main(void)
{

	printf("\n\n--- mallocs ---\n\n");
	int total = 0;
	char *str = malloc(42);
	total += 42;
	free(str);
	char *str2 = malloc(42);
	total += 42;
	ft_print_mem();
	return (0);

	char *str5 = malloc(556);
	total += 556;
	char *str6 = malloc(5000);
	total += 5000;
	int i = -1;

	printf("\n\n--- debugging ---\n\n");
	while (++i < 42)
	{
		str[i] = (i % 26)+ 'a';
		str2[i] = ((i + 2) % 26)+ 'a';
		str5[i] = ((i + 2) % 26)+ 'a';
	}
	str[i] = '\0';
	str2[i] = '\0';
	printf("str -> %s\n", str);
	printf("str2 -> %s\n", str2);
	printf("str -> %s\n", str);

	int	y = 0;
	char *str3;


	printf("\n\n--- lots of malloc ---\n\n");
	while ((++y * 42) < 16000)
	{
		str3 = malloc(42);
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
	return (0);
}