#include "maze.h"

// algrotihm used : https://www.youtube.com/watch?v=zRuVhq0Kgnw at 2:59
// iterative backtracker

int width;
int height;

void push(t_cell *element, t_cell *stack[], int *top, int stackSize) {
	if (*top == -1) {
		stack[stackSize - 1] = element;
		*top = stackSize - 1;
	}
	else if (*top == 0){
		printf("The stack is already full. \n");
	}
	else {
		stack[(*top) - 1] = element;
		(*top)--;
	}
}

void pop(int *top, int stackSize) {
	if (*top == -1) {
		printf("The stack is empty. \n");
	}
	else {
		// printf("Element popped: %c \n", stack[(*top)]);
		// If the element popped was the last element in the stack
		// then set top to -1 to show that the stack is empty
		if ((*top) == stackSize - 1)
			(*top) = -1;
		else
			(*top)++;
	}
}

t_cell	new_cell(int y, int x) {
	t_cell ret;

	for (int i = 0; i < 8; i++)
		ret.edges[i] = 1;
	if (y == 0) {
		ret.edges[NORTH] = -1;
		ret.edges[NO_WE] = -1;
		ret.edges[NO_EA] = -1;
	}
	if (x == 0) {
		ret.edges[WEST] = -1;
		ret.edges[NO_WE] = -1;
		ret.edges[SO_WE] = -1;
	}
	if (y == height - 1) {
		ret.edges[SOUTH] = -1;
		ret.edges[SO_WE] = -1;
		ret.edges[SO_EA] = -1;
	}
	if (x == width - 1) {
		ret.edges[EAST] = -1;
		ret.edges[NO_EA] = -1;
		ret.edges[SO_EA] = -1;
	}

	ret.visited = 0;

	ret.y = y;
	ret.x = x;
	return ret;
}

int	cell_has_neighbours(t_cell ** maze, t_cell * current_cell) {
	int y = current_cell->y;
	int x = current_cell->x;
	if ((y > 0 && maze[y - 1][x].visited == 0) ||
		(y < height - 1 && maze[y + 1][x].visited == 0) ||
		(x > 0 && maze[y][x - 1].visited == 0) ||
		(x < width - 1 && maze[y][x + 1].visited == 0))
		return (1);
	return (0);
}

t_cell *	random_neighbour(t_cell ** maze, t_cell * current_cell, int * direction) {
	int y = current_cell->y;
	int x = current_cell->x;
	int random = rand() % 4;
	
	if (random == 0 && (y > 0 && maze[y - 1][x].visited == 0)) {
		*direction = NORTH;
		return &(maze[y - 1][x]);
	}
	else if (random == 1 && (y < height - 1 && maze[y + 1][x].visited == 0)) {
		*direction = SOUTH;
		return &(maze[y + 1][x]);
	}
	else if (random == 2 && (x > 0 && maze[y][x - 1].visited == 0)) {
		*direction = WEST;
		return &(maze[y][x - 1]);
	}
	else if (random == 3 && (x < width - 1 && maze[y][x + 1].visited == 0)) {
		*direction = EAST;
		return &(maze[y][x + 1]);
	}
	return (random_neighbour(maze, current_cell, direction));	

}

void	display_maze(t_cell ** maze, int fill_width, int fill_height) {
	if (fill_height) {
		printf("*");
		if (fill_width)
			for (int i = 1; i < width * 2; i++)
				printf("X");
		else
			for (int i = 1; i < width * 2 - 1; i++)
				printf("X");
		printf("\n");
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (maze[y][x].edges[NO_WE] == 1)
				printf("X");
			else if (maze[y][x].edges[NO_WE] == 0)
				printf("*");
			if (maze[y][x].edges[NORTH] == 1)
				printf("X");
			else if (maze[y][x].edges[NORTH] == 0)
				printf("*");
		}
		if (y > 0) {
			if (fill_width)
				printf("X");
			printf("\n");
		}
		for (int x = 0; x < width; x++) {
			if (maze[y][x].edges[WEST] == 1)
				printf("X");
			else if (maze[y][x].edges[WEST] == 0)
				printf("*");
			printf("*");
		}
		if (fill_width && y == height - 1)
			printf("*");
		else if (fill_width)
			printf("X");
		if (y < height - 1)
			printf("\n");	
	}
}

int main(int ac, char ** av) {
	srand(time(NULL));

	int top = -1;
	int opposites[4] = {EAST, WEST, SOUTH, NORTH};



	// also should check that arguments passed are positive numbers
	if (ac != 3) {
		printf("./maze <width> <height>");
		exit(EXIT_FAILURE);
	}

	int fill_width = 0;
	int fill_height = 0;
	width = atoi(av[1]);
	if (width % 2 == 0) {
		width /= 2;
		fill_width = 1;
	}
	else
		width = width / 2 + 1;
	height = atoi(av[2]);
	if (height % 2 == 0) {
		height /= 2;
		fill_height = 1;
	}
	else
		height = height / 2 + 1;
	t_cell *stack[width * height];

	t_cell ** maze = malloc(sizeof(t_cell *) * height);
	for (int y = 0; y < height; y++) {
		maze[y] = malloc(sizeof(t_cell) * width);
		for (int x = 0; x < width; x++) {
			maze[y][x] = new_cell(y, x);
		}
	}

	maze[0][0].visited = 1;
	push(&maze[0][0], stack, &top, width * height);

	while (top != -1) {
		t_cell * current_cell = stack[top];
		pop(&top, width * height);
		if (cell_has_neighbours(maze, current_cell)) {
			// add current cell to stack
			push(current_cell, stack, &top, width * height);
			// randomly choose a neighbour
			int direction = -1;
			t_cell * chosen_neighbour = random_neighbour(maze, current_cell, &direction);
			// remove the edge between current cell and said neighbour
			current_cell->edges[direction] = 0;
			chosen_neighbour->edges[opposites[direction]] = 0;
			// mark said neighbour as visited
			chosen_neighbour->visited = 1;
			// add said neighbour to stack
			push(chosen_neighbour, stack, &top, width * height);
		}
	}

	display_maze(maze, fill_width, fill_height);
	exit(EXIT_SUCCESS);
}
