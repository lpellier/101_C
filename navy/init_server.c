#include "navy.h"

void	init_global() {
	global.pid = getpid();
	global.other_pid = 0;
	global.att_point.x = -1;
	global.att_point.y = -1;
	global.hit = 0;
	global.response = connect;
	global.game_state = 1;
}

void wait_for_connection() {
	while (global.response != _void)
		usleep(100);
	printf("connected\n");
	if (kill(global.other_pid, SIGUSR1) == -1) {
		printf("Couldn't connect\n");
		exit(EXIT_FAILURE);
	}
}

void	connect_to_server(char * pid) {
	if (kill(atoi(pid), SIGUSR1) == -1) {
		printf("Couldn't connect\n");
		exit(EXIT_FAILURE);
	}
	while (global.response != _void)
		usleep(100);
	printf("successfully connected\n");

}
