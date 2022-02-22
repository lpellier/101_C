#include "sokoban.h"

void	init_curses() {
	initscr(); // start curses mode
	raw(); // disable line buffering
	keypad(stdscr, TRUE); // set fn keys
	noecho(); // prevent echo-ing while getch
	curs_set(0); // remove cursor

}

bool	error_in_args(int ac, char ** av) {
	if (ac != 2 || !av || !av[1])
		return (true);
	return (false);
}

void	append_to_buf(char ** dest, char c) {
	char *	tmp;
	size_t	len = 0;
	
	if (!(*dest)) {
		len = 1;
		*dest = malloc(sizeof(char) * len + 1);		
		**dest = c;
		*(*(dest) + 1) = '\0';
	}
	else {
		size_t i = 0;
		tmp = *dest;
		len = strlen(*dest);
		*dest = malloc(sizeof(char) * len + 1);
		for (; i < len; i++)
			(*dest)[i] = tmp[i];
		(*dest)[i] = c;
		(*dest)[i + 1] = '\0';
		free(tmp);
		tmp = NULL;
	}
}

int		get_map(int fd, t_game ** game) {
	char	tmp = 0;
	size_t	rows = 1;
	size_t	cols = 0;
	size_t	index = 0;
	// get number of columns and rows

	(*game)->map = malloc(sizeof(t_map));
	while (read(fd, &tmp, 1) > 0) {
		if (tmp == '\n') {
			if (rows > 1 && cols != index) {
				printf("Unenven number of cols in map\n");
				printf("%zu %zu %zu\n", rows, cols, index);
				return (FAILURE);
			}
			cols = index;
			index = 0;
			rows++;
		}
		else
			index++;
	}
	close(fd);
	(*game)->map->rows = rows;
	(*game)->map->cols = cols;
	(*game)->map->map = malloc(sizeof(char *) * rows);

	int		i = 0;
	char *	buf = NULL;

	// read map file from start to actually store map
	fd = open((*game)->map_file, O_RDONLY);
	while (read(fd, &tmp, 1) > 0) {
		if (tmp == '\n' && buf) {
			(*game)->map->map[i] = strdup(buf);
			free(buf);
			buf = NULL;
			i++;
		}
		else
			append_to_buf(&buf, tmp);
	}
	(*game)->map->map[i] = strdup(buf);
	free(buf);
	buf = NULL;
	close(fd);
	return (SUCCESS);
}

int		init_game_struct(char ** av, t_game ** game) {
	int		fd = -1;

	if ((fd = open(av[1], O_RDONLY)) == -1) {
		printf("Could not open/read map file\n");
		return (FAILURE);
	}
	
	*game = malloc(sizeof(t_game));
	(*game)->map_file = strdup(av[1]);

	get_map(fd, game);
	// MAP ERRRORS
	// NOT SURROUNDED BY WALLS
	// DIFF NUMBER OF BOXES AND NUMBER OF SPOTS
	// UNKNOWN CHAR 

	int	box_spots = 0;

	for (size_t i = 0; i < (*game)->map->rows; i++) {
		for (size_t j = 0; j < (*game)->map->cols; j++) {
			if ((*game)->map->map[i][j] == 'O')
				box_spots++;
		}
	}
	(*game)->map->box_nbr = box_spots;
	(*game)->map->box_spots = malloc(sizeof(t_pos) * box_spots);
	box_spots = 0;
	for (size_t i = 0; i < (*game)->map->rows; i++) {
		for (size_t j = 0; j < (*game)->map->cols; j++) {
			if ((*game)->map->map[i][j] == 'O') {
				(*game)->map->box_spots[box_spots].x = i;
				(*game)->map->box_spots[box_spots].y = j;
				box_spots++;
			}
		}
	}
	
	return (SUCCESS);
}
