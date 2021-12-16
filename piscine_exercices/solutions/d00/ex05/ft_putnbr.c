#include <unistd.h>

void ft_putchar(int c) {
	write(1, &c, 1);
}

void ft_putnbr(int nbr) {
	unsigned int n;

	if (nbr < 0) {
		ft_putchar('-');
		n = -nbr;
	}
	else
		n = nbr;
	if (n > 9) {
		ft_putnbr(n / 10);
		n %= 10;
	}
	ft_putchar(n + 48);
}
