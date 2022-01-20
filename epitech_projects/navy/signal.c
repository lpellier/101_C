#include "navy.h"

void    handle_signal(int signal, siginfo_t *si, void *context)
{
	static int coord_x = 0;
	static int coord_y = 0;
	static int first = 0;
	(void)context;
	if (signal == SIGUSR1 && global.response == connect) {
		global.response = _void;
		global.other_pid = si->si_pid;
	}
	else if (global.response == attack) {
		if (signal == SIGUSR1 && first == 0)
			coord_x++;
		else if (signal == SIGUSR1 && first == 1)
			coord_y++;
		else if (signal == SIGUSR2 && first == 0)
			first++;
		else if (signal == SIGUSR2 && first == 1) {
			global.response = _void;
			kill(global.pid, SIGUSR1);
			
		}
	}
	else if (global.response == _void && signal == SIGUSR1) {
		global.att_point.x = coord_x;
		global.att_point.y = coord_y;
		coord_x = 0;
		coord_y = 0;
		first = 0;
	}
	else if (global.response == success) {
		if (signal == SIGUSR1)
			global.hit = 1;
		else if (signal == SIGUSR2)
			global.hit = 0;
		global.response = _void;
	}
	else if (global.response == endgame) {
		if (signal == SIGUSR1)
			global.game_state = 0;
		else if (signal == SIGUSR2)
			global.response = attack;
	}
}

void    init_usr_signal(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		printf("Error: cannot handle SIGUSR1\n");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		printf("Error: cannot handle SIGUSR2\n");
}

// sigaction