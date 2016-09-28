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

/* global variables
 * ────────────────────────────────────────────────────────────────────────── */
char board[] = "┌───┬───┬───┐\n"
	       "│ 0 │ 1 │ 2 │\n"
	       "├───┼───┼───┤\n"
	       "│ 3 │ 4 │ 5 │\n"
	       "├───┼───┼───┤\n"
	       "│ 6 │ 7 │ 8 │\n"
	       "└───┴───┴───┘\n";

char *const restrict board_map[9] = {
	[0] = &board[44],
	[1] = &board[50],
	[2] = &board[56],
	[3] = &board[106],
	[4] = &board[112],
	[5] = &board[118],
	[6] = &board[168],
	[7] = &board[174],
	[8] = &board[180]
};





/* macro helpers
 * ────────────────────────────────────────────────────────────────────────── */
#define LIKELY(BOOL)   __builtin_expect(BOOL, true)
#define UNLIKELY(BOOL) __builtin_expect(BOOL, false)

/* 0..9 → '0'..'9' */
#define DIGIT_TO_ASCII(DIGIT)	(((unsigned int) (DIGIT)) | 48u)
/* '0'..'9' → 0..9 */
#define ASCII_TO_DIGIT(ASCII)	(((unsigned int) (ASCII)) & 15u)


#define MOVE(CELL) (1u << (CELL))
/* ┌───┬───┬───┐
 * │ 0 │ 1 │ 2 │
 * ├───┼───┼───┤
 * │ 3 │ 4 │ 5 │
 * ├───┼───┼───┤
 * │ 6 │ 7 │ 8 │
 * └───┴───┴───┘
 */

#define WIN_0 (MOVE(0) | MOVE(1) | MOVE(2))
#define WIN_1 (MOVE(6) | MOVE(7) | MOVE(8))
#define WIN_2 (MOVE(0) | MOVE(3) | MOVE(6))
#define WIN_3 (MOVE(2) | MOVE(5) | MOVE(8))
#define WIN_4 (MOVE(3) | MOVE(4) | MOVE(5))
#define WIN_5 (MOVE(1) | MOVE(4) | MOVE(7))
#define WIN_6 (MOVE(0) | MOVE(4) | MOVE(8))
#define WIN_7 (MOVE(6) | MOVE(4) | MOVE(2))


static inline bool
is_winner(const unsigned int moveset);

static inline void
update_board(const unsigned int cell,
	     const char token);

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
print_board(void);

static inline unsigned int
get_cell(void);
#endif /* ifndef TICTACTOE_H_ */
