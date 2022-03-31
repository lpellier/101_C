#include "tetris.h"

void	secure_free(void ** ptr) {
	if (*ptr) {
		free(*ptr);
		*ptr = NULL;
	}
}

void	secure_free_array(void *** ptr, size_t height) {
	if (*ptr) {
		for (size_t i = 0; i < height; i++) {
			secure_free((void **)&(*ptr)[i]);
		}
		secure_free((void **)*ptr);
	}
}

void	secure_free_tet_list(void ** ptr) {
	if (*ptr) {
		t_tetrimino * current = *ptr;
		t_tetrimino * tmp;
		while (current->next) {
			tmp = current;
			current = current->next;
			secure_free((void **)&(tmp->name));
			secure_free_array((void ***)&(tmp->shape), tmp->height);
			secure_free((void **)&tmp);
		}
	}
}

void	free_info(t_info ** info) {
	if (*info) {
		secure_free((void **)&((*info)->keys));
		secure_free_array((void ***)&((*info)->map), (*info)->map_height);
		secure_free_tet_list((void **)&((*info)->pieces));
		secure_free_tet_list((void **)&((*info)->next_pieces));
	}
}
