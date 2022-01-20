#include "navy.h"

void	add_ship(char *** maps, char * buffer) {
	int len = buffer[0];
	int start_x = buffer[2] - 'A';
	int start_y = buffer[3] - '0' - 1;
	int	end_x = buffer[5] - 'A';
	int end_y = buffer[6] - '0' - 1;

	if (start_x != end_x && start_y != end_y)
		return ;
	if (start_x != end_x) {
		while (start_x != end_x) {
			(*maps)[PLAYER_1][start_y * 8 + start_x] = len;
			start_x++;
		}
		(*maps)[PLAYER_1][start_y * 8 + start_x] = len;
	}
	if (start_y != end_y) {
		while (start_y != end_y) {
			(*maps)[PLAYER_1][start_y * 8 + start_x] = len;
			start_y++;
		}
		(*maps)[PLAYER_1][start_y * 8 + start_x] = len;
	}
}

void	init_maps(char *** maps) {
	for (int i = 0; i < 64; i++)
		(*maps)[PLAYER_1][i] = '.';
	for (int i = 0; i < 64; i++)
		(*maps)[PLAYER_2][i] = '.';
}

void	fill_maps(char * file, char *** maps) {
	char *	buffer = NULL;
	size_t	buff_size = 0;
	ssize_t	line_size;

	FILE *	map_file = fopen(file, "r");
	*maps = malloc(sizeof(char *) * 2);
	(*maps)[PLAYER_1] = malloc(sizeof(char) * 64);
	(*maps)[PLAYER_2] = malloc(sizeof(char) * 64); 
	
	init_maps(maps);

	line_size = getline(&buffer, &buff_size, map_file);
	add_ship(maps, buffer);
	free(buffer);
	buffer = NULL;
	while (line_size >= 0) {
		line_size = getline(&buffer, &buff_size, map_file);
		add_ship(maps, buffer);
		free(buffer);
		buffer = NULL;
	}
	fclose(map_file);
}
