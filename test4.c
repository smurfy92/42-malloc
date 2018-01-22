#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
# include <fcntl.h>

void print(char *s)
{
  write(1, s, strlen(s));
}

void		ft_out(char *str)
{
	int fd = open("/dev/ttys002", O_WRONLY|O_NONBLOCK|O_NOCTTY);
	write(fd, str, strlen(str));
}

int main()
{
  char *addr;

  print("Bonjours\n");
  addr = malloc(16);
  ft_out("Free null\n");
  free(NULL);
  ft_out("Free bad address\n");
  free((void *)addr + 5);
  ft_out("Free good\n");
  if (realloc((void *)addr + 5, 10) == NULL)
    print("Bonjours\n");
}