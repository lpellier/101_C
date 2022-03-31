#pragma once

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <ncurses.h>
#include <time.h>
#include <dirent.h>

# define BLACK		0
# define RED		1
# define GREEN		2
# define YELLOW		3
# define BLUE		4
# define MAGENTA	5
# define CYAN		6
# define WHITE		7
# define VOID		8

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

typedef struct	s_tetrimino {
	char *	name;
	
	size_t	width;
	size_t	height;
	char **	shape;
	int		color;

	bool	error;
 
	struct s_tetrimino *	next;
}				t_tetrimino;

typedef struct	s_cur_piece {
	size_t	pos_x;
	size_t	pos_y;

	size_t	width;
	size_t	height;

	char **	shape;
}				t_cur_piece;


typedef struct	s_keys {
	int	left;
	int	right;
	int	turn;
	int	drop;
	int	quit;
	int	pause;
}				t_keys;

typedef struct	s_list {
	size_t	y;
	size_t	x;

	struct s_list *	next;
}				t_list;

typedef struct	s_info {
	size_t	map_width;
	size_t	map_height;

	t_tetrimino *	pieces;
	t_keys *		keys;
	char **			map;

	t_tetrimino *	next_pieces;

	bool			time_for_next_piece;
	t_cur_piece		current_piece;
	t_list *		downward_faces;

	/* 		**** OPTIONS ****	   */
	bool			debug_mode;
	bool			without_next;
	size_t			start_level;
}				t_info;

void	init_curses();
void	init_info(t_info * info);
void	init_keys(t_keys * keys);
t_tetrimino *	new_tetrimino();
t_tetrimino *	copy_tetrimino(t_tetrimino * src);
int		get_args(int ac, char ** av, t_info *info);

/* **** free **** */
void	secure_free(void ** ptr);
void	secure_free_array(void *** ptr, size_t height);
void	secure_free_tet_list(void ** ptr);
void	free_info(t_info ** info);

