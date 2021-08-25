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
static const char MISS_SYM = '0';
static const char WATER_SYM = '.';


/* Rendering */
void draw_screen(u8 *player, u8 *enemy);
void draw_seperator(u8 length);
void draw_board(u8 *buf);
void clear_screen();

#define TABLE_ALL			(0xFF)
#define TABLE_CARRIER 		(0x1 << 0)
#define TABLE_BATTLESHIP 	(0x1 << 1)
#define TABLE_CRUISER 		(0x1 << 2)
#define TABLE_SUBMARINE 	(0x1 << 3)
#define TABLE_DESTROYER 	(0x1 << 4)
void draw_boat_table(u8 ships);

/* Boad Setup */
void create_board(u8 *buf);
void pick_positions(u8 *buf);
int place_boat(u8 *buf, u8 id, char row, u8 col, char dir);

int main(int argc, char* argv[]) {
	/* Create and initialise player board */
	u8 player[SQR(BOARDWIDTH)];
	create_board(player);

	/* Create and initialise enemy board */
    u8 enemy[SQR(BOARDWIDTH)];
	create_board(enemy);
	
	/* Display game screen*/
	draw_screen(player, enemy);

	/* Select positions */
	pick_positions(player);

	return 0;
}

/* Initialise a given board to be empty, full of water */
void create_board(u8 *buf) {
	memset(buf, WATER_SYM, SQR(BOARDWIDTH));
}

void pick_positions(u8 *buf) {
	u8 picking_positions = TABLE_ALL;
	while (picking_positions) {
		//clear_screen();
		draw_board(buf);
		draw_boat_table(picking_positions);
		printf("Please input a position to place a boat in the format of \
<id><coordinate><direction> e.g. 1A3D for a Carrier \
starting at A3 facing downward.\n> ");
			
		char row, dir;
		u8 id, col;
		scanf("%hhd%c%hhd%c", &id, &row, &col, &dir);

		/* Place boat */	
        place_boat(buf, id, row, col, dir);
    }
}

/* Abstraction for drawing both the players and enemies 
 * boards with a seperator. Enemy board is displayed first.
 */
void draw_screen(u8 *player, u8 *enemy) {
	clear_screen();
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
	for (u8 y = 0; y <= BOARDWIDTH; ++y) {
		/* Write verticle axis coordinates*/
		if (!y) printf("  ");
		else printf("%c ", 65 + (y - 1));

		/* Draw Row */
		for (u8 x = 0; x < BOARDWIDTH; ++x) {
			/* If top row, draw horizontal axis coordinates*/
			if (!y) printf("%d ", x + 1);
			else printf("%c ", buf[(y - 1) * BOARDWIDTH + x]);
		}
		printf("\n");
	}
}

void draw_boat_table(u8 ships) {
	
	printf("| Number | Boat       | Size |\n");
	printf("| ------ | ---------- | ---- |\n");
	
	/* Print Carrier State*/
	if (ships | TABLE_CARRIER)
		printf("| 1      | Carrier    | 5    |\n");
	else
		printf("| 1      | \e[9mCarrier\e[0m    | 5    |\n");
			
	/* Print Battleship State*/
	if (ships | TABLE_BATTLESHIP)
		printf("| 2      | Battleship | 4    |\n");
	else
		printf("| 2      | \e[9mBattleship\e[9m | 4    |\n");
	
	/* Print Cruiser State*/
	if (ships | TABLE_CRUISER)
		printf("| 3      | Cruiser    | 3    |\n");
	else
		printf("| 3      | \e[9mCruiser\e[0m    | 3    |\n");

	/* Print Submarine State*/
	if (ships | TABLE_SUBMARINE)
		printf("| 4      | Submarine  | 3    |\n");
	else
		printf("| 4      | \e[9mSubmarine\e[0m  | 3    |\n");
	
	/* Print Destroyer State*/
	if (ships | TABLE_DESTROYER)
		printf("| 5      | Destroyer  | 2    |\n");
	else
		printf("| 5      | \e[9mDestroyer\e[0m  | 2    |\n");
}

void clear_screen() {
	printf("\e[1;1H\e[2J");
}

int place_boat(u8 *buf, u8 id, char row, u8 col, char dir) {
	if (id == 0 || id > 5) return 1; /* Invalid Boat */
	if (row - 65 < 0 || row - 65 >= BOARDWIDTH) return 1; /* Invalid Row */
	if (col > BOARDWIDTH >= BOARDWIDTH) return 1; /* Invalid Col */
	if (dir != 'D' && dir != 'R') return 1; /* Invalid Direction*/

    const u8 lengths[] = { 5, 4, 3, 3, 2 };
    u8 len = lengths[id - 1];
    u8 x = col - 1, y = row - 65;
    
    if (dir == 'D' && y + len >= BOARDWIDTH) return 1; /* Out of bounds */ 
    if (dir == 'R' && x + len >= BOARDWIDTH) return 1; /* Out of bounds */ 

    /* Draw downwards or right */
    u8 index = 0;
    for (u8 i = 0; i < len; ++i) {
        index = (dir == 'D') ? (y + i) * BOARDWIDTH + x : 
                                y * BOARDWIDTH + (x + i);
        buf[index] = BOAT_SYM;
    }

	return 0;
}
