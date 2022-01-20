#include "navy.h"

void	display_maps(char ** maps) {	
	int count = 1;
	printf("my positions:\n");
	printf(" |A B C D E F G H\n");
	printf("-+---------------\n");
	for (int i = 0; i < 64; i++) {
		if (i != 0 && i % 8 == 0)
			printf("\n");
		if (i % 8 == 0) {
			printf("%d|", count);
			count++;
		}
		printf("%c ", maps[PLAYER_1][i]);
	}
	printf("\n\n");
	printf("enemy's positions:\n");
	printf(" |A B C D E F G H\n");
	printf("-+---------------\n");
	count = 1;
	for (int i = 0; i < 64; i++) {
		if (i != 0 && i % 8 == 0)
			printf("\n");
		if (i % 8 == 0) {
			printf("%d|", count);
			count++;
		}
		printf("%c ", maps[PLAYER_2][i]);
	}
	printf("\n\n");
}

int	is_ship(char c) {
	if (c >= '2' && c <= '5')
		return 1;
	return 0;
}
