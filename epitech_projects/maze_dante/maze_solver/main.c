#include "maze.h"

// algrotihm used : https://en.wikipedia.org/wiki/Maze-solving_algorithm
// recursive algo

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
		*dest = malloc(sizeof(char) * len + 2);
		for (; i < len; i++)
			(*dest)[i] = tmp[i];
		(*dest)[i] = c;
		(*dest)[i + 1] = '\0';
		free(tmp);
		tmp = NULL;
	}
}

int		get_map(t_map * map, char * map_file) {
	char	tmp = 0;
	size_t	rows = 1;
	size_t	cols = 0;
	size_t	index = 0;
	// get number of columns and rows

	int fd = open(map_file, O_RDONLY);
	
	while (read(fd, &tmp, 1) > 0) {
		if (tmp == '\n') {
			cols = index;
			index = 0;
			rows++;
		}
		else
			index++;
	}
	close(fd);
	map->rows = rows;
	map->cols = cols;
	map->map = malloc(sizeof(char *) * rows);

	int		i = 0;
	char *	buf = NULL;

	// read map file from start to actually store map
	fd = open(map_file, O_RDONLY);
	while (read(fd, &tmp, 1) > 0) {
		if (tmp == '\n' && buf) {
			map->map[i] = strdup(buf);
			free(buf);
			buf = NULL;
			i++;
		}
		else
			append_to_buf(&buf, tmp);
	}
	map->map[i] = strdup(buf);
	free(buf);
	buf = NULL;
	close(fd);
	return (SUCCESS);
}

void	init_array(bool *** array, size_t rows, size_t cols) {
	(*array) = malloc(sizeof(bool *) * rows);
	for (size_t i = 0; i < rows; i++) {
		(*array)[i] = malloc(sizeof(bool) * cols);
		for (size_t j = 0; j < cols; j++) {
			(*array)[i][j] = false;
		}
	}
}

void	init_info(t_info ** info, t_map * map) {
	init_array(&((*info)->was_here), map->rows, map->cols);

	(*info)->map = map;

	(*info)->start_x = 0;
	(*info)->start_y = 0;

	(*info)->end_x = map->cols - 1;
	(*info)->end_y = map->rows - 1;
}

bool	recursive_solve(size_t x, size_t y, t_info * info) {
	if (x == info->end_x && y == info->end_y)
		return true;
	if (info->map->map[y][x] == WALL || info->was_here[y][x])
		return false;
	info->was_here[y][x] = true;
	if (x > 0 && recursive_solve(x - 1, y, info)) {
		info->map->map[y][x] = SOLU;
		return true;
	}
	if (x < info->map->cols - 1 && recursive_solve(x + 1, y, info)) {
		info->map->map[y][x] = SOLU;
		return true;
	}
	if (y > 0 && recursive_solve(x, y - 1, info)) {
		info->map->map[y][x] = SOLU;
		return true;
	}
	if (y < info->map->rows - 1 && recursive_solve(x, y + 1, info)) {
		info->map->map[y][x] = SOLU;
		return true;
	}
	return false;
}

int main(int ac, char ** av) {

	t_map * map = malloc(sizeof(t_map));

	// also should check that arguments passed are positive numbers
	if (ac != 2 || !get_map(map, av[1])) {
		printf("./maze <file_path>");
		exit(EXIT_FAILURE);
	}

	t_info * info = malloc(sizeof(t_info));
	init_info(&info, map);
	bool b = recursive_solve(info->start_x, info->start_y, info);

	if (b == true)
		info->map->map[map->rows - 1][map->cols - 1] = SOLU;

	printf("%s\n", b ? "true" : "false");

	for (size_t y = 0; y < map->rows; y++) {
		for (size_t x = 0; x < map->cols; x++) {
			printf("%c", map->map[y][x]);
		}
		free(map->map[y]);
		printf("\n");
	}
	free(map->map);

	exit(EXIT_SUCCESS);
}
