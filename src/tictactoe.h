#ifndef TICTACTOE_H_
#define TICTACTOE_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include <stdbool.h>	/* bool */
#include <sys/types.h>	/* read */
#include <sys/uio.h>	/* read */
#include <unistd.h>	/* read, write */
#include <stdio.h>	/* perror */
#include <stdlib.h>	/* exit */

/* macro helpers
 * ────────────────────────────────────────────────────────────────────────── */
#define LIKELY(BOOL)   __builtin_expect(BOOL, true)
#define UNLIKELY(BOOL) __builtin_expect(BOOL, false)

#define PRINT_LITERAL(LITERAL) write_stdout(LITERAL, sizeof(LITERAL) - 1lu)

/* 0..9 → '0'..'9' */
#define DIGIT_TO_ASCII(DIGIT)	(((unsigned int) (DIGIT)) | 48u)
/* '0'..'9' → 0..9 */
#define ASCII_TO_DIGIT(ASCII)	(((unsigned int) (ASCII)) & 15u)

/* ┌───┬───┬───┐
 * │ 0 │ 1 │ 2 │
 * ├───┼───┼───┤
 * │ 3 │ 4 │ 5 │
 * ├───┼───┼───┤
 * │ 6 │ 7 │ 8 │
 * └───┴───┴───┘
 */

#define MOVE(CELL) (1u << (CELL))

#define WIN_0 (MOVE(0) | MOVE(1) | MOVE(2))
#define WIN_1 (MOVE(6) | MOVE(7) | MOVE(8))
#define WIN_2 (MOVE(0) | MOVE(3) | MOVE(6))
#define WIN_3 (MOVE(2) | MOVE(5) | MOVE(8))
#define WIN_4 (MOVE(3) | MOVE(4) | MOVE(5))
#define WIN_5 (MOVE(1) | MOVE(4) | MOVE(7))
#define WIN_6 (MOVE(0) | MOVE(4) | MOVE(8))
#define WIN_7 (MOVE(6) | MOVE(4) | MOVE(2))

#define CATS_GAME (MOVE(9) - 1u)

/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
struct MoveNode {
	const unsigned int move;
	const unsigned int cell;
	struct MoveNode *restrict prev;
	struct MoveNode *restrict next;
};


/* global variables
 * ────────────────────────────────────────────────────────────────────────── */

struct MoveNode moves[9] = {
	{ .move = MOVE(0), .cell = 0u, .prev = NULL,	  .next = &moves[1] },
	{ .move = MOVE(1), .cell = 1u, .prev = &moves[0], .next = &moves[2] },
	{ .move = MOVE(2), .cell = 2u, .prev = &moves[1], .next = &moves[3] },
	{ .move = MOVE(3), .cell = 3u, .prev = &moves[2], .next = &moves[4] },
	{ .move = MOVE(4), .cell = 4u, .prev = &moves[3], .next = &moves[5] },
	{ .move = MOVE(5), .cell = 5u, .prev = &moves[4], .next = &moves[6] },
	{ .move = MOVE(6), .cell = 6u, .prev = &moves[5], .next = &moves[7] },
	{ .move = MOVE(7), .cell = 7u, .prev = &moves[6], .next = &moves[8] },
	{ .move = MOVE(8), .cell = 8u, .prev = &moves[7], .next = NULL	    }
};

struct MoveNode *rem_moves = &moves[0];

/* struct MoveNode move0 = { .move = MOVE(0), .cell = 0u }; */
/* struct MoveNode move1 = { .move = MOVE(1), .cell = 1u }; */
/* struct MoveNode move2 */
/* struct MoveNode move3 */
/* struct MoveNode move4 */
/* struct MoveNode move5 */
/* struct MoveNode move6 */
/* struct MoveNode move6 */




unsigned int board_moveset    = 0u;
unsigned int player_moveset   = 0u;
unsigned int computer_moveset = 0u;

const char player_token	  = 'X';
const char computer_token = 'O';

char display[] = "┌───┬───┬───┐\n"
	         "│ 0 │ 1 │ 2 │\n"
	         "├───┼───┼───┤\n"
	         "│ 3 │ 4 │ 5 │\n"
	         "├───┼───┼───┤\n"
	         "│ 6 │ 7 │ 8 │\n"
	         "└───┴───┴───┘\n";

char *const restrict display_map[9] = {
	[0] = &display[44],
	[1] = &display[50],
	[2] = &display[56],
	[3] = &display[106],
	[4] = &display[112],
	[5] = &display[118],
	[6] = &display[168],
	[7] = &display[174],
	[8] = &display[180]
};




static inline bool
is_winner(const unsigned int moveset);

static inline void
update_display(const unsigned int cell,
	       const char token);

static inline void
remove_move(struct MoveNode *const restrict move);
static inline void
insert_move(struct MoveNode *const restrict move);

static inline void
update_moves(const unsigned int cell);

static inline void
read_stdin(char *const restrict buffer,
	   const size_t size);

static inline void
read_size_stdin(size_t *const restrict size_read,
		char *const restrict buffer,
		const size_t size);

static inline void
flush_stdin(void);

static inline void
write_stdout(const char *const restrict buffer,
	     const size_t size);

static inline void
print_display(void);
static inline void
player_wins(void);
static inline void
computer_wins(void);
static inline void
cats_game(void);

static inline unsigned int
get_player_cell(void);
static inline void
player_move(void);

int
score_player_move(struct MoveNode *restrict move,
		  unsigned int player,
		  const unsigned int computer);

int
score_computer_move(struct MoveNode *restrict move,
		    unsigned int computer,
		    const unsigned int player);

static inline unsigned int
get_computer_cell(void);
static inline void
computer_move(void);
#endif /* ifndef TICTACTOE_H_ */
