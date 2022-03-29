#include "tetris.h"

void	print_keys(t_keys * keys) {
	printf("Key left: %d (%d)\n", keys->left, keys->left);
	printf("Key right: %d (%d)\n", keys->right, keys->right);
	printf("Key turn: %d (%d)\n", keys->turn, keys->turn);
	printf("Key drop: %d (%d)\n", keys->drop, keys->drop);
	printf("Key quit: %d (%d)\n", keys->quit, keys->quit);
	printf("Key pause: %d (%d)\n", keys->pause, keys->pause);
}

size_t	list_length(t_tetrimino * list) {
	size_t	count = 0;

	while (list) {
		list = list->next;
		count++;
	}
	return (count);
}

void	print_tetriminos(t_tetrimino * pieces) {
	while (pieces) {
		if (pieces->error)
			printf("Tetriminos '%s': error\n", pieces->name);
		else {
			printf("Tetriminos '%s': size %zu*%zu, color %d\n", pieces->name, pieces->width, pieces->height, pieces->color);
			if (pieces->shape) {
				for (size_t i = 0; i < pieces->height; i++)
					printf("%s\n", pieces->shape[i]);
			}
		}
		pieces = pieces->next;
	}
}

void	print_debug(t_info * info) {
	print_keys(info->keys);
	printf("Next: %s\n", (info->without_next ? "Yes" : "No"));
	printf("Level: %zu\n", info->start_level);
	printf("Size: %zu*%zu\n\n", info->map_height, info->map_width);

	printf("Number of tetriminos: %zu\n", list_length(info->pieces));
	print_tetriminos(info->pieces);
}

void	add_tetrimino(t_tetrimino ** pieces, t_tetrimino * new) {
	if (!(*pieces)) {
		(*pieces) = new;
	}
	else {
		t_tetrimino * current = *pieces;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

int		get_tetriminos(t_info * info) {
	DIR *			directory;
	struct dirent *	dirp;
	char *			found;

	directory = opendir("tetriminos");
	if (!directory)
		return (FAILURE);

	while ((dirp = readdir(directory))) {
		if ((found = strstr(dirp->d_name, ".tetrimino"))) {
			add_tetrimino(&info->pieces, new_tetrimino(dirp->d_name, found));
		}
	}
	closedir(directory);
	return (SUCCESS);
}

void	remove_tet_errors(t_tetrimino * pieces) {
	t_tetrimino *	tmp;

	while (pieces && pieces->next) {
		if (pieces->next->error == true) {
			tmp = pieces->next;
			pieces->next = pieces->next->next;
			secure_free((void **)&(tmp->name));
			secure_free_array((void ***)&(tmp->shape), tmp->height);
			secure_free((void **)&tmp);
		}
		pieces = pieces->next;
	}
}

t_tetrimino *	random_tetrimino(t_tetrimino * pieces) {
	int	i = 0;
	int	random = rand() % list_length(pieces);

	while (pieces && pieces->next && i < random) {
		pieces = pieces->next;
		i++;
	}
	return (pieces);
}

int		main(int ac, char ** av) {
	t_info * info = malloc(sizeof(t_info));

	srand(time(NULL) * getpid());
	init_info(info);
	if (get_args(ac, av, info) || get_tetriminos(info)) {
		free_info(&info);
		exit(EXIT_FAILURE);
	}

	if (info->debug_mode)
		print_debug(info);
	remove_tet_errors(info->pieces);
	add_tetrimino(&info->next_piece, copy_tetrimino(random_tetrimino(info->pieces)));
	print_tetriminos(info->next_piece);
	
	// init_curses();

	// loop
	// endwin();
	free_info(&info);
	exit(EXIT_SUCCESS);
}