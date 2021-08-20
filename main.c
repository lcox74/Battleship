#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u8;

/* Board Width */
static const u8 BOARDWIDTH = 10;
#define SQR(x) ((x) * (x))

/* Symbol Definition */
static const char BOAT_SYM = 'b';
static const char HIT_SYM = 'x';
static const char MISS_SYM = '0'
static const char WATER_SYM = '.';

/* Rendering */
void draw_screen(u8 *player, u8 *enemy);
void draw_seperator(u8 length);
void draw_board(u8 *buf);

/* Boad Setup */
void create_board(u8 *buf);

int main(int argc, char* argv[]) {
	/* Create and initialise player board */
	u8 player[SQR(BOARDWIDTH)];
	create_board(player);

	/* Create and initialise enemy board */
    u8 enemy[SQR(BOARDWIDTH)];
	create_board(enemy);
	
	/* Display game screen*/
	draw_screen(player, enemy);

	return 0;
}

/* Initialise a given board to be empty, full of water */
void create_board(u8 *buf) {
	memset(buf, WATER_SYM, SQR(BOARDWIDTH));
}

/* Abstraction for drawing both the players and enemies 
 * boards with a seperator. Enemy board is displayed first.
 */
void draw_screen(u8 *player, u8 *enemy) {
	draw_board(enemy);
	draw_seperator(BOARDWIDTH * 2 + 2);
	draw_board(player);
}

/* Draws a line of `=` of given length */
void draw_seperator(u8 length) {
	while ((length--) > 0) { printf("="); }
	printf("\n");
}

/* Draws a given board with the coordinates displayed
 * on top and on the sides, with letters for the vertical
 * axis.
 */
void draw_board(u8 *buf) {
	for (u8 y = 0; y < BOARDWIDTH; ++y) {
		/* Write verticle axis coordinates*/
		if (!y) printf("  ");
		else printf("%c ", 65 + (y - 1));

		/* Draw Row */
		for (u8 x = 0; x < BOARDWIDTH; ++x) {
			/* If top row, draw horizontal axis coordinates*/
			if (!y) printf("%d ", x + 1);
			else printf("%c ", buf[y * BOARDWIDTH + (x - 1)]);
		}
		printf("\n");
	}
}
