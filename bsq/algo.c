#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// x and y are coordinates of upper left corner of square
// size is width of square
int check_obstacle(char **map, int y, int x)
{
	int size = 1;
	// map[y][x] starting point
	int cur_y;
	int cur_x;
	// check for 'o' in range map[y][x] <-> map[y + size][x + size]
	while (map[y + size] && map[y + size][x + size])
	{
		cur_y = y;
		while (map[cur_y] && cur_y < (y + size))
		{
			cur_x = x;
			while (map[cur_y][cur_x] && cur_x < (x + size))
			{
				// if 'o' return size - 1
				if (map[cur_y][cur_x] == 'o')
				{
					// printf("found | start : y %d, x %d | obs : y %d, x %d at size %d\n", y, x, cur_y, cur_x, size - 1);
					return size - 1;
				}
				cur_x++;
			}
			cur_y++;
		}
		// if no 'o', size += 1 and start over
		size++;
	}

	// if no 'o' found at all, size = smaller length of map
	if (cur_x > cur_y)
	{
		// printf("ended | start : y %d, x %d at size %d -> %d\n", y, x, size, cur_y - 1);
		if (size > cur_y)
			return size - 1;
		return cur_y - 1;
	}
	else
	{
		printf("ended | start : y %d, x %d at size %d -> %d\n", y, x, size, cur_x - 1);
		if (size > cur_x)
			return size - 1;
		return cur_x - 1;
	}
}

typedef struct bsq
{
	int x;
	int y;
	int size;
} bsq;

char *ft_strdup(char *src)
{
	char *new;
	int i;
	int size;

	size = 0;
	while (src[size])
		++size;
	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int main(int ac, char **av)
{
	char **map;
	bsq biggest;
	(void)ac;

	int fd = open(av[1], O_RDONLY);
	char buf[1];
	int lines = 0;
	int stop = 0;
	int len = 0;
	while (read(fd, buf, 1))
	{
		if (*buf == '\n')
		{
			stop = 1;
			lines++;
		}
		if (!stop)
			len++;
	}

	map = malloc(sizeof(char *) * (lines + 1));
	for (int i = 0; i < lines; i++) {
		map[i] = malloc(sizeof(char) * len + 1);
	}
	
	int line_index = 0;
	close(fd);
	fd = open(av[1], O_RDONLY);
	while (read(fd, map[line_index], len))
	{
		map[line_index][len] = '\0';
		line_index++;
		read(fd, buf, 1); // for \n
	}
	close(fd);
	map[line_index] = NULL;

	int size = 0;
	biggest.x = 0;
	biggest.y = 0;
	biggest.size = 0;
	for (int height = 0; map[height]; height++)
	{
		for (int width = 0; map[height][width]; width++)
		{
			size = check_obstacle(map, height, width);
			if (size > biggest.size)
			{
				biggest.x = width;
				biggest.y = height;
				biggest.size = size;
			}
		}
	}
	printf("bsq : y -> %d  x -> %d  size -> %d", biggest.y, biggest.x, biggest.size);
	printf("\n\n");
	for (int height = biggest.y; map[height] && height < biggest.size + biggest.y; height++)
	{
		for (int width = biggest.x; map[height][width] && width < biggest.size + biggest.x; width++)
		{
			if (map[height][width] != 'o')
				map[height][width] = 'x';
		}
	}
	for (int height = 0; map[height]; height++)
	{
		for (int width = 0; map[height][width]; width++)
		{
			printf("%c ", map[height][width]);
		}
		printf("\n");
	}
}


/*
..... 00000
..o.. 000111
...o. 000122
..... 00122
o.... 11233
*/
