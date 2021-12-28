#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"
#include <fcntl.h>

typedef struct s_point {
	int	x;
	int	y;
} t_point;

typedef struct s_ship {
	int	x;
	int	y;
	int	endx;
	int	endy;
	int	length;
} t_ship;

enum players {
	PLAYER_1,
	PLAYER_2
};

enum expectedResponses {
	_void,
	connect,
	attack,
	success,
	endgame
};

typedef struct s_info {
	pid_t	pid;
	pid_t	other_pid;
	t_point	att_point;
	int		hit;
	int		response;
	int		game_state;
} t_info;

t_info global;

void    init_usr_signal(void);
void    handle_signal(int signal, siginfo_t *si, void *context);

void	init_global();
void	wait_for_connection();
void	connect_to_server(char * pid);

void	add_ship(char *** maps, char * buffer);
void	init_maps(char *** maps);
void	fill_maps(char * file, char *** maps);

void	display_maps(char ** maps);
int		is_ship(char c);
