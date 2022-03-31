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
				for (size_t i = 0; i < pieces->height; i++) {
					for (size_t j = 0; j < pieces->width; j++)
						printf("%c", pieces->shape[i][j] == VOID ? 'X' : '*');
					printf("\n");
				}
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

void	print_map(t_info * info) {
	int	max_row, max_col;

	getmaxyx(stdscr, max_row, max_col);
	// check if term is too small for output
	mvprintw(max_row / 2 - info->map_height / 2 + 1, max_col / 2 - info->map_width / 2, "+");
	for (size_t i = 0; i < info->map_width; i++)
		mvprintw(max_row / 2 - info->map_height / 2 + 1, max_col / 2 - info->map_width / 2 + 1 + i, "-");
	mvprintw(max_row / 2 - info->map_height / 2 + 1, max_col / 2 - info->map_width / 2 + 1 + info->map_width, "+");
	for (size_t i = 0; i < info->map_height; i++) {
		mvprintw(max_row / 2 - info->map_height / 2 + i + 2, max_col / 2 - info->map_width / 2, "|");
		for (size_t j = 0; j < info->map_width; j++) {
			// print_color(info->map[i][j]);
			if (info->map[i][j] >= BLACK && info->map[i][j] <= WHITE)
				mvprintw(max_row / 2 - info->map_height / 2 + i + 2, max_col / 2 - info->map_width / 2 + j + 1, "*");
			else if (info->map[i][j] == VOID)
				mvprintw(max_row / 2 - info->map_height / 2 + i + 2, max_col / 2 - info->map_width / 2 + j + 1, " ");
		}
		mvprintw(max_row / 2 - info->map_height / 2 + i + 2, max_col / 2 - info->map_width / 2 + info->map_width + 1, "|");
	}
	mvprintw(max_row / 2 - info->map_height / 2 + 2 + info->map_height, max_col / 2 - info->map_width / 2, "+");
	for (size_t i = 0; i < info->map_width; i++)
		mvprintw(max_row / 2 - info->map_height / 2 + 2 + info->map_height, max_col / 2 - info->map_width / 2 + 1 + i, "-");
	mvprintw(max_row / 2 - info->map_height / 2 + 2 + info->map_height, max_col / 2 - info->map_width / 2 + 1 + info->map_width, "+");
	refresh(); // print on screen
}

int	get_input(t_info * info) {
	int ch = getch();
	
	(void)info;

	if (ch == 27)
		return (FAILURE);
	return (SUCCESS);
}

bool	is_downward_facing(char ** shape, size_t i, size_t j, size_t height) {
	if (i == height - 1 || (i < height - 1 && shape[i + 1][j] == VOID))
		return true;
	return false;
}


bool	can_move_down(char ** shape, size_t i, size_t j, size_t height) {
	if (i < height - 1 && shape[i + 1][j] == VOID)
		return true;
	return false;
}

void	add_next_piece_to_map(t_info * info) {
	for (size_t i = 0; i < info->next_pieces->height; i++) {
		for (size_t j = 0; j < info->next_pieces->width; j++) {
			info->map[i][(info->map_width - info->next_pieces->width) / 2 + j] = info->next_pieces->shape[i][j];
		}
	}
	info->current_piece.pos_x = (info->map_width - info->next_pieces->width) / 2;
	info->current_piece.pos_y = 0;
	info->current_piece.shape = info->next_pieces->shape;
	info->current_piece.width = info->next_pieces->width;
	info->current_piece.height = info->next_pieces->height;
	info->next_pieces = info->next_pieces->next;
	info->time_for_next_piece = false;
}

void	add_downward_face(t_info * info, size_t y, size_t x) {
	if (!info->downward_faces) {
		info->downward_faces = malloc(sizeof(t_list));
		info->downward_faces->x = x;
		info->downward_faces->y = y;
		info->downward_faces->next = NULL;
	}
	else {
		t_list *	current = info->downward_faces;

		while (current && current->next)
			current = current->next;
		current->next = malloc(sizeof(t_list));
		current->next->x = x;
		current->next->y = y;
		current->next->next = NULL;
	}
}

// need to check all downward faces of current tetrimino
void	move_down(t_info * info) {
	size_t	nbr_faces = 0;
	size_t	faces_able_to_move = 0;

	// mvprintw(1, 1, "ALO 0");
	// refresh();

	// first, find downward faces of shape
	for (size_t i = 0; i < info->current_piece.height; i++) {
		for (size_t j = 0; j < info->current_piece.width; j++) {
			if (is_downward_facing(info->current_piece.shape, i, j, info->current_piece.height)) {
				add_downward_face(info, i, j);
				nbr_faces++;
			}
		}
	}
	mvprintw(1, 1, "ALO 1");
	refresh();	

	// loop on downward faces and check for collisions
	t_list *	tmp;
	while (info->downward_faces) {
		tmp = info->downward_faces;
		info->downward_faces = info->downward_faces->next;
		if (can_move_down(info->map, tmp->y, tmp->x, info->map_height))
			faces_able_to_move++;
		secure_free((void **)&tmp);
	}

	mvprintw(1, 1, "hieght : %d %d", faces_able_to_move, nbr_faces);
	refresh();

	if (faces_able_to_move == nbr_faces) {
		for (size_t i = info->current_piece.height - 1; i > 0; i--) {
			for (size_t j = 0; j < info->current_piece.width; j++) {
				if (info->current_piece.shape[i][j] != VOID) {
					info->map[i + info->current_piece.pos_y + 1][j + info->current_piece.pos_x] = info->map[i + info->current_piece.pos_y][j + info->current_piece.pos_x];
					info->map[i + info->current_piece.pos_y][j + info->current_piece.pos_x] = VOID;
				}
			}	
		}
		for (size_t j = 0; j < info->current_piece.width; j++) {
			if (info->current_piece.shape[0][j] != VOID) {
				info->map[0 + info->current_piece.pos_y + 1][j + info->current_piece.pos_x] = info->map[0 + info->current_piece.pos_y][j + info->current_piece.pos_x];
				info->map[0 + info->current_piece.pos_y][j + info->current_piece.pos_x] = VOID;
			}
		}	
		info->current_piece.pos_y++;
	}
	mvprintw(1, 1, "ALO 1");
	refresh();
}

int		main(int ac, char ** av) {
	t_info * info = malloc(sizeof(t_info));

	srand(time(NULL) * getpid());
	init_info(info);
	if (get_args(ac, av, info) || get_tetriminos(info)) {
		free_info(&info);
		exit(EXIT_FAILURE);
	}

	
	init_curses();

	if (info->debug_mode)
		print_debug(info);
	remove_tet_errors(info->pieces);
	add_tetrimino(&info->next_pieces, copy_tetrimino(random_tetrimino(info->pieces)));
	// print_tetriminos(info->next_piece);
	clock_t	begin = clock();
	clock_t	end;
	unsigned long time_diff;
	unsigned long time_old = 0;
	
	
	print_map(info);
	while (42) {
		// frames handling
		end = clock();
		time_diff = (end - begin) * 1000 / CLOCKS_PER_SEC;
		if (time_diff != time_old && time_diff % 1000 == 0) {
			// move down
			if (info->time_for_next_piece)
				add_next_piece_to_map(info);
			else
				move_down(info);
			// printf("time : %lu\n", time_diff / 1000);
			time_old = time_diff;
		}
		// read input
		if (get_input(info))
			break;
		// clear screen
		// print map
		print_map(info);
	}
	endwin();
	free_info(&info);
	exit(EXIT_SUCCESS);
}