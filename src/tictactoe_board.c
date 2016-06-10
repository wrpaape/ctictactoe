#include "tictactoe_board.h"

void init_board(struct Board *board);
{
	return 42;
}

#define NAME_BUFFER ""
#define MAX_NAME_LENGTH 32ul

#define CELL_PAD " "

#define PAD_CELL(CELL) CELL_PAD CELL CELL_PAD

#define ANSI_WRAP(TEXT, SEQ) ANSI_ ## SEQ TEXT ANSI_RESET

#define CURSOR ANSI_WRAP(">", BLINK)

#define CELL(CHAR) PAD_CELL(ANSI_WRAP(CHAR, FAINT))

#define LINE_ROW_3(L, M, R) L "───" M "───" M "───" R "\n"
#define CELL_ROW_3(X, Y, Z) "│" CELL(X) "│" CELL(Y) "│" CELL(Z) "│\n"

static struct Board empty_3 = {
	.display = EMPTY_DISPLAY_3,
};



/* static ptrdiff_t move_map_3[] = { */
/* 	 44,  50,  56, */
/* 	105, 111, 117, */
/* 	166, 172, 178 */
/* } */
