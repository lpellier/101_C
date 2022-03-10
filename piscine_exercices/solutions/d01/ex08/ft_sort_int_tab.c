
void	ft_swap(int * a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_int_tab(int *tab, int size) {
	
	for (int i = 0; i < size; i++) {
		if (i + 1 < size && tab[i + 1] < tab[i])
			ft_swap(&tab[i + 1], &tab[i]);
	}
}

