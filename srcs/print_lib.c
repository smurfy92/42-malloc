#include "../includes/malloc.h"

static size_t		ft_nbrlen(unsigned long long n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

void				ft_print_addr(unsigned long long n, int endl)
{
	char				str[ft_nbrlen(n)];
	size_t				len;

	len = ft_nbrlen(n) - 1;
	if (n == 0)
		str[len] = '0';
	str[len + 1] = '\0';
	while (n)
	{
		str[len] = (16 > 10 && n % 16 > 9) ?
			(n % 16) + ('a' - 10) : (n % 16) + 48;
		n /= 16;
		len--;
	}
	ft_putstr("0x");
	if (endl)
		ft_putendl(str);
	else
		ft_putstr(str);
}

void				ft_print_node(t_node *ptr)
{
	void	*tmp;

	tmp = ptr + 1;
	ft_print_addr((intmax_t)tmp, 0);
	ft_putstr(" - ");
	ft_print_addr((intmax_t)tmp + 1 + ptr->size - sizeof(t_node) - 1, 0);
	ft_putstr(" : ");
	ft_putnbr(ptr->size - sizeof(t_node));
	ft_putendl(" octets");
}