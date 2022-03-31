#include "tetris.h"

void	init_curses() {
	initscr(); // start curses mode
	raw(); // disable line buffering
	keypad(stdscr, TRUE); // set fn keys
	noecho(); // prevent echo-ing while getch
	curs_set(0); // remove cursor
	timeout(0);
}

void	init_keys(t_keys * keys) {
	keys->left = KEY_LEFT;
	keys->right = KEY_RIGHT;
	keys->turn = KEY_UP;
	keys->drop = KEY_DOWN;
	keys->quit = 'q';
	keys->pause = ' ';
}

size_t	get_next_number(char * line, bool reset) {
	static int	i = 0;
	size_t		ret = 0;

	if (reset)
		i = 0;

	while (line[i] && line[i] == ' ')
		i++;
	
	while (line[i] && line[i] >= '0' && line[i] <= '9') {
		ret = ret * 10 + line[i] - 48;
		i++;
	}
	return (ret);
}

char *	concatenate(char * s1, char * s2) {
	char * ret = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	int	i = 0;

	while (*s1) {
		ret[i] = *s1;
		i++;
		s1++;
	}
	while (*s2) {
		ret[i] = *s2;
		i++;
		s2++;
	}
	ret[i] = '\0';
	return (ret);
}

t_tetrimino *	copy_tetrimino(t_tetrimino * src) {
	t_tetrimino *	ret = malloc(sizeof(t_tetrimino));

	ret->name = strdup(src->name);

	ret->width = src->width;
	ret->height = src->height;
	ret->shape = malloc(sizeof(char *) * ret->height);
	for (size_t i = 0; i < ret->height; i++) {
		ret->shape[i] = malloc(sizeof(char) * ret->width);
		for (size_t j = 0; j < ret->width; j++)
			ret->shape[i][j] = src->shape[i][j];
	}
	ret->color = src->color;
	
	ret->error = src->error;
	
	ret->next = NULL;
	
	return (ret);
}

void	rearrange_shape(t_tetrimino * src) {
	for (size_t i = 0; i < src->height; i++) {
		if (strlen(src->shape[i]) < src->width) {
			char * tmp = src->shape[i];
			src->shape[i] = malloc(sizeof(char) * src->width);
			strcpy(src->shape[i], tmp);
			for (size_t z = strlen(tmp); z < src->width; z++)
				src->shape[i][z] = ' ';
			secure_free((void **)&tmp);
		}
		for (size_t j = 0; j < src->width; j++) {
			if (src->shape[i][j] == ' ')
				src->shape[i][j] = VOID;
			else if (src->shape[i][j] == '*')
				src->shape[i][j] = src->color;
			else
				src->error = true;
		}
	}
}

t_tetrimino *	new_tetrimino(char * file_name, char * found) {
	t_tetrimino *	ret = malloc(sizeof(t_tetrimino));
	char *	full_file_name = concatenate("tetriminos/", file_name);
	FILE *	file = fopen(full_file_name, "r");
	ssize_t	read;
	size_t	len = 0;
	char *	line = NULL;
	
	secure_free((void **)&full_file_name);

	ret->name = strndup(file_name, (found - file_name));
	ret->error = false;
	ret->next  = NULL;

	read = getline(&line, &len, file);
	if (read == -1) {
		ret->error = true;
		fclose(file);
		return (ret);
	}
	ret->width = get_next_number(line, true);
	ret->height = get_next_number(line, false);
	ret->color = (int)get_next_number(line, false);
	secure_free((void **)&line);

	int	count = 0;
	ret->shape = malloc(sizeof(char *) * ret->height);
	while ((read = getline(&line, &len, file)) != -1) {
		ret->shape[count] = line[strlen(line) - 1] == '\n' ? strndup(line, strlen(line) - 1) : strdup(line);
		count++;
		secure_free((void **)&line);
	}

	fclose(file);

	rearrange_shape(ret);

	return (ret);
}

void	init_info(t_info * info) {
	info->map_width = 20;
	info->map_height = 10;

	info->pieces = NULL;
	info->keys = malloc(sizeof(t_keys));
	init_keys(info->keys);
	info->map = malloc(sizeof(char *) * info->map_height);
	for (size_t i = 0; i < info->map_height; i++) {
		info->map[i] = malloc(sizeof(char) * info->map_width);
		for (size_t j = 0; j < info->map_width; j++)
			info->map[i][j] = VOID;
	}

	info->next_pieces = NULL;
	info->time_for_next_piece = true;
	info->downward_faces = NULL;

	info->debug_mode = false;
	info->without_next = false;
	info->start_level = 1;
}

int		get_args(int ac, char ** av, t_info *info) {
	// init and check error
	// resize terminal message if needed
	int opt;

	// put ':' in the starting of the
	// string so that program can 
	//distinguish between '?' and ':' 
	while ((opt = getopt(ac, av, ":L:l:r:t:d:q:p:wD")) != -1) 
	{
		switch(opt)
		{
			case 'w':
				info->without_next = true;
				break;
			case 'D':
				info->debug_mode = true;
				break;
			case 'L':
				info->start_level = atoi(optarg);
				break;
			case 'l':
				info->keys->left = *optarg;
				break;
			case 'r':
				info->keys->right = *optarg;
				break;
			case 't':
				info->keys->turn = *optarg;
				break;
			case 'd':
				info->keys->drop = *optarg;
				break;
			case 'q':
				info->keys->quit = *optarg;
				break;
			case 'p':
				info->keys->pause = *optarg;
				break;
			case ':':
				printf("option needs a value\n"); 
				return (FAILURE);
			case '?':
				printf("unknown option: %c\n", optopt);
				return (FAILURE);
		} 
	}
	return (SUCCESS);
}
