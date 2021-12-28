#include "navy.h"

// fill both maps
// player map is filled with map file -> check characters
// -> 4:C2:C5 : vertical ship of len 4
// -> 3:D3:B3 : horizontal ship of len 3
// -> 2:D3:C4 : impossible ship because both letters and numbers changed (no diagonals)
// Must use 4 ships with lengths 2, 3, 4, 5 and no duplicates
// Should check if ships overlap or not

// ennemy map is filled with what we know, at start -> nothing
// meaning that when we hit a ship, we know there is a ship there but we don't know its length nor full coordinates

// play the game
// hit a spot (if wrong location try again)
// if miss, then send miss to the other player
// if hit, send hit to other player and add that to ennemy map info and check if that's a win or not
// to check whether it's actually hit, we'll need to send coordinates of attack to other player
// We could send the same signal multiple times to indicate a specific spot on the map
// -> B6 would be SIGUSR1 twice then SIGUSR2 6 times
// Once the info is sent, the other player sends back information on whether a boat has been hit or not
// The game goes on until one player quits or looses
// How to check whether a player still has every boat ? After every hit, check on map if there are still any numbers (they make up the ships)
// If there are none, send info to other player and quit program
// Otherwise, proceed with game

void	check_game_state(char * map) {
	int	count = 0;
	for (int i = 0; i < 64; i++) {
		if (is_ship(map[i]))
			count++;
	}
	if (count == 0) {
		kill(global.other_pid, SIGUSR1);
		global.game_state = 0;
	}
	else
		kill(global.other_pid, SIGUSR2);
}

void	start_attack() {
	char	*buf = NULL;

	while (42) {
		printf("attack: \e[3m");
		fflush(stdout);
		get_next_line(0, &buf);
		printf("\e[0m");
		if (buf[0] >= 'A' && buf[0] <= 'H' && buf[1] >= '1' && buf[1] <= '8' && strlen(buf) == 2)
			break;
		free(buf);
		buf = NULL;
		printf("wrong position\n");
	}
	global.att_point.x = buf[0] - 'A';
	global.att_point.y = buf[1] - '0' - 1;
	for (int i = 0; i < global.att_point.x; i++) {
		kill(global.other_pid, SIGUSR1);
		usleep(100);
	}
	kill(global.other_pid, SIGUSR2);
	usleep(100);
	for (int i = 0; i < global.att_point.y; i++) {
		kill(global.other_pid, SIGUSR1);
		usleep(100);
	}
	kill(global.other_pid, SIGUSR2);
}

void	start_game_p1(char *** maps) {
	while (42) {
		display_maps(*maps);
		// first attack
		start_attack();

		// then check attack success
		global.response = success;
		while (global.response == success)
			usleep(100);
		if (global.hit) {
			printf("%c%d: hit\n", global.att_point.x + 'A', global.att_point.y + 1);
			(*maps)[PLAYER_2][global.att_point.y * 8 + global.att_point.x] = 'x';
		}
		else {
			printf("%c%d: missed\n", global.att_point.x + 'A', global.att_point.y + 1);
			(*maps)[PLAYER_2][global.att_point.y * 8 + global.att_point.x] = 'o';
		}
		global.response = endgame;
		while (global.response == endgame)
			usleep(100);
		printf("\n");
		printf("waiting for enemy's attack...\n");
		while (global.response == attack)
			usleep(100);
		// first check opponent attack
		if (is_ship((*maps)[PLAYER_1][global.att_point.y * 8 + global.att_point.x])) {
			printf("%c%d: hit\n", global.att_point.x + 'A', global.att_point.y + 1);
			(*maps)[PLAYER_1][global.att_point.y * 8 + global.att_point.x] = 'x';
			kill(global.other_pid, SIGUSR1);
		}
		else {
			printf("%c%d: missed\n", global.att_point.x + 'A', global.att_point.y + 1);
			(*maps)[PLAYER_1][global.att_point.y * 8 + global.att_point.x] = 'o';
			kill(global.other_pid, SIGUSR2);
		}
		usleep(100);
		check_game_state((*maps)[PLAYER_1]);
		if (global.game_state == 0)
			break ;
	}
}

void	start_game_p2(char *** maps) {
	while (42) {
		display_maps(*maps);
		printf("waiting for enemy's attack...\n");
		global.response = attack;
		while (global.response == attack)
			usleep(100);
		// first check opponent attack
		if (is_ship((*maps)[PLAYER_1][global.att_point.y * 8 + global.att_point.x])) {
			printf("%c%d: hit\n", global.att_point.x + 'A', global.att_point.y + 1);
			(*maps)[PLAYER_1][global.att_point.y * 8 + global.att_point.x] = 'x';
			kill(global.other_pid, SIGUSR1);
		}
		else {
			printf("%c%d: missed\n", global.att_point.x + 'A', global.att_point.y + 1);
			(*maps)[PLAYER_1][global.att_point.y * 8 + global.att_point.x] = 'o';
			kill(global.other_pid, SIGUSR2);
		}
		usleep(100);
		check_game_state((*maps)[PLAYER_1]);
		if (global.game_state == 0)
			break ;
		// update maps accordingly

		// first attack
		start_attack();

		// then check attack success
		global.response = success;
		while (global.response == success)
			usleep(100);
		if (global.hit) {
			printf("%c%d: hit\n", global.att_point.x + 'A', global.att_point.y + 1);
			(*maps)[PLAYER_2][global.att_point.y * 8 + global.att_point.x] = 'x';
		}
		else {
			printf("%c%d: missed\n", global.att_point.x + 'A', global.att_point.y + 1);
			(*maps)[PLAYER_2][global.att_point.y * 8 + global.att_point.x] = 'o';
		}
		global.response = endgame;
		while (global.response == endgame)
			usleep(100);
		printf("\n");
	}
}


int	main(int ac, char ** av) {
	char **	maps = NULL;
	init_usr_signal();
	init_global();
	if (ac == 2) {
		printf("pid : %d\n", global.pid);
		wait_for_connection();
		fill_maps(av[1], &maps);
		start_game_p1(&maps);
	}
	else if (ac == 3) {
		connect_to_server(av[1]);
		fill_maps(av[2], &maps);
		start_game_p2(&maps);
	}
	free(maps[PLAYER_1]);
	free(maps[PLAYER_2]);
	free(maps);

}
