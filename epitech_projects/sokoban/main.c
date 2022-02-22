#include "sokoban.h"

void	free_game_struct(t_game * game) {
	if (game) {
		if (game->map_file)
			free(game->map_file);
		if (game->map) {
			if (game->map->map) {
				for (size_t i = 0; i < game->map->rows; i++)
					free(game->map->map[i]);
				free(game->map->map);	
			}
			free(game->map);
		}
	}
}

bool	is_box_spot(t_game * game, size_t x, size_t y) {
	for (size_t i = 0; i < game->map->box_nbr; i++) {
		if (x == game->map->box_spots[i].x && y == game->map->box_spots[i].y)
			return true;
	}
	return false;
}

bool	game_over(t_game * game) {
	size_t count = 0;
	for (size_t i = 0; i < game->map->box_nbr; i++) {
		if (game->map->map[game->map->box_spots[i].x][game->map->box_spots[i].y] == 'X')
			count++;
	}
	if (count == game->map->box_nbr)
		return true;
	return false;
}

int		draw_map(t_game * game) {
	int	max_row, max_col;

	getmaxyx(stdscr, max_row, max_col);
	if (game_over(game)) {
		clear();
		mvprintw(max_row / 2 - 5, max_col / 2, "Well played\n");
		getch();
		return SUCCESS;
	}
	// check if term is too small for output
	for (size_t i = 0; i < game->map->rows; i++) {
		for (size_t j = 0; j < game->map->cols; j++) {
			if (game->map->map[i][j] == ' ' && is_box_spot(game, i, j))
				mvprintw(max_row / 2 - game->map->rows / 2 + i, max_col / 2 - game->map->cols / 2 + j, "%c", 'O');
			else
				mvprintw(max_row / 2 - game->map->rows / 2 + i, max_col / 2 - game->map->cols / 2 + j, "%c", (game->map->map)[i][j]);
		}
	}
	refresh(); // print on screen
	return FAILURE;
}

void	get_player_xy(t_game * game, size_t * x, size_t * y) {
	for (size_t i = 0; i < game->map->rows; i++) {
		for (size_t j = 0; j < game->map->cols; j++) {
			if (game->map->map[i][j] == 'P') {
				*x = i;
				*y = j;
				return ;
			}
		}
	}
}

void	modify_map(size_t direction_x, size_t direction_y, size_t x, size_t y, t_game ** game) {
	if ((*game)->map->map[x][y] == 'X') {
		if ((*game)->map->map[x + direction_x][y + direction_y] != '#' && (*game)->map->map[x + direction_x][y + direction_y] != 'X') { 
			(*game)->map->map[x][y] = ' ';
			(*game)->map->map[x + direction_x][y + direction_y] = 'X';
		}
	}
	if ((*game)->map->map[x][y] != '#' && (*game)->map->map[x][y] != 'X') {
		(*game)->map->map[x][y] = 'P';
		(*game)->map->map[x - direction_x][y - direction_y] = ' ';
	}
}

int	get_input(t_game * game) {
	int ch = getch();
	int x, y;

	get_player_xy(game, &game->map->player.x, &game->map->player.y);
	x = game->map->player.x;
	y = game->map->player.y;
	if (ch == KEY_DOWN) {
		modify_map(1, 0, x + 1, y, &game);
	}
	else if (ch == KEY_LEFT) {
		modify_map(0, -1, x, y - 1, &game);
	}
	else if (ch == KEY_RIGHT) {
		modify_map(0, 1, x, y + 1, &game);
	}
	else if (ch == KEY_UP) {
		modify_map(-1, 0, x - 1, y, &game);
	}
	else if (ch == KEY_F(2))
		return (FAILURE);
	return (SUCCESS);
}

int		main(int ac, char ** av) {
	t_game 	* game = NULL;

	if (error_in_args(ac, av)) {
		printf("./sokoban <map_file>\n");
		exit(EXIT_FAILURE);
	}
	init_game_struct(av, &game);
	
	init_curses();
	while (42) {
		// get input (arrow keys)
		if (!draw_map(game) || get_input(game))
			break;
	}
	endwin();
	free_game_struct(game);
	exit(EXIT_SUCCESS);
}