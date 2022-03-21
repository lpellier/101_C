#pragma once

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

enum directions {
	WEST,
	EAST,
	NORTH,
	SOUTH,
	NO_WE,
	NO_EA,
	SO_WE,
	SO_EA
};

typedef struct s_cell {
	int	edges[8]; // 0 is west, 1 is east, 2 is north, 3 is south
	int visited;

	int y;
	int x;
} t_cell;


