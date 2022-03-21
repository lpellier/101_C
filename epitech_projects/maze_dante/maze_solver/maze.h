#pragma once

#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

# define WALL 'X'
# define PATH '*'
# define SOLU 'o'

# define bool char
# define false 0
# define true 1

enum {
	FAILURE,
	SUCCESS
};

enum directions {
	WEST,
	EAST,
	NORTH,
	SOUTH
};

typedef struct s_map {
	char ** map;
	
	size_t rows;
	size_t cols;
} t_map;

typedef struct s_info {
	bool ** was_here;

	t_map * map;

	size_t start_x;
	size_t start_y;
	size_t end_x;
	size_t end_y;
} t_info;
