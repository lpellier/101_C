#include <unistd.h>

void ft_putchar(int c) {
	write(1, &c, 1);
}

void ft_print_numbers(void) {
	for (int i = 0; i <= 9; i++)
		ft_putchar(i + 48);
}

