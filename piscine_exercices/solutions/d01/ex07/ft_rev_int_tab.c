
void	ft_rev_int_tab(int * tab, int size) {
	int tmp;
	int end_index = size - 1;
	for (int i = 0; i < size / 2; i++) {
		tmp = tab[i];
		tab[i] = tab[end_index];
		tab[end_index] = tmp;
		end_index--;
	}
}

