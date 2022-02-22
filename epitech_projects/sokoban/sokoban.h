#pragma once

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <ncurses.h>
#include <time.h>

#ifndef bool
# define bool char
#endif

#ifndef true
# define true 1
#endif

#ifndef false
# define false 0
#endif

enum status_codes {
	SUCCESS,
	FAILURE
};

typedef struct		s_pos {
	size_t	x;
	size_t	y;
}					t_pos;

typedef struct		s_map {
	char **	map;
	t_pos	player;
	t_pos *	box_spots;
	size_t	box_nbr;
	size_t	rows;
	size_t	cols;

}					t_map;

typedef struct	s_game {
	char *		map_file;
	t_map *		map;
	int			boxes_left;
}				t_game;

void	init_curses();
bool	error_in_args(int ac, char ** av);
void	append_to_buf(char ** dest, char c);
int		get_map(int fd, t_game ** game);
int		init_game_struct(char ** av, t_game ** game);



