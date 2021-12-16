#include <unistd.h>
void ft_putchar(int c) {
	write(1, &c, 1);
}

void ft_print_reverse_alphabet(void) {
	for (int letter = 'z'; letter >= 'a'; letter--)
		ft_putchar(letter);
}
