#include <unistd.h>

void	ft_putchar(int c) {
	write(1, &c, 1);
}

void	ft_putstr(char * str) {
	if (!str)
		return ;
	for (int i = 0; str[i]; i++)
		ft_putchar(str[i]);
}
