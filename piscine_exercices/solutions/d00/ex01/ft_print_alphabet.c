#include <unistd.h>

void ft_putchar(int c) {
	write(1, &c, 1);
}

void ft_print_alphabet(void) {
	int	letter = 97; // 97 = 'a'
	while (letter <= 'z') { // 'z' = 122
		ft_putchar(letter);
		letter++;	
	}
}
