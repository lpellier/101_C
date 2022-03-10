#include <stdio.h>
#include <stdlib.h>

void ft_rev_int_tab(int * tab, int size);

int main() {
	int size = 5;
	int * tab = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
		tab[i] = i;

	for (int i = 0; i < size; i++)
		printf("%d ", tab[i]);
	printf("\n");
	ft_rev_int_tab(tab, size);
	for (int i = 0; i < size; i++)
		printf("%d ", tab[i]);
}
