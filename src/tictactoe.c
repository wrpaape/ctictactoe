#include "tictactoe.h"

int
main(void)
{
	while (1) {
		player_move();

		if (is_winner(player_moveset)) {
			player_wins();
			return 0;
		}

		if (board_moveset == CATS_GAME) {
			cats_game();
			return 0;
		}

		computer_move();

		if (is_winner(computer_moveset)) {
			computer_wins();
			return 0;
		}
	}
}

static inline bool
is_winner(const unsigned int moveset)
{
	return ((moveset & WIN_0) == WIN_0)
	    || ((moveset & WIN_1) == WIN_1)
	    || ((moveset & WIN_2) == WIN_2)
	    || ((moveset & WIN_3) == WIN_3)
	    || ((moveset & WIN_4) == WIN_4)
	    || ((moveset & WIN_5) == WIN_5)
	    || ((moveset & WIN_6) == WIN_6)
	    || ((moveset & WIN_7) == WIN_7);
}

static inline void
update_display(const unsigned int cell,
	       const char token)
{
	*(display_map[cell]) = token;
}

static inline void
remove_move(struct MoveNode *const restrict move)
{
	struct MoveNode *const restrict prev = move->prev;
	struct MoveNode *const restrict next = move->next;

	if (prev != NULL)
		prev->next = next;

	if (next != NULL)
		next->prev = prev;
}

static inline void
insert_move(struct MoveNode *const restrict move)
{
	struct MoveNode *const restrict prev = move->prev;
	struct MoveNode *const restrict next = move->next;

	if (prev != NULL)
		prev->next = move;

	if (next != NULL)
		next->prev = move;
}

static inline void
update_moves(const unsigned int cell)
{
	struct MoveNode *const restrict move = &moves[cell];

	if (move == rem_moves)
		rem_moves = rem_moves->next;

	remove_move(move);
}

static inline void
read_stdin(char *const restrict buffer,
	   const size_t size)
{
	if (LIKELY(read(STDIN_FILENO,
			buffer,
			size) == size))
		return;

	perror("read failure:\n\t");
	exit(1);
	__builtin_unreachable();
}

static inline void
read_size_stdin(size_t *const restrict size_read,
		char *const restrict buffer,
		const size_t size)
{
	*size_read = (size_t) read(STDIN_FILENO,
				   buffer,
				   size);

	if (LIKELY(((ssize_t) *size_read) >= 0l))
		return;

	perror("read failure:\n\t");
	exit(1);
	__builtin_unreachable();
}

static inline void
flush_stdin(void)
{
	char buffer[256];
	size_t size_read;

	 do {
		 read_size_stdin(&size_read,
				 &buffer[0],
				 sizeof(buffer));
	 } while (size_read == sizeof(buffer));
}


static inline void
write_stdout(const char *const restrict buffer,
	     const size_t size)
{
	if (LIKELY(write(STDOUT_FILENO,
			 buffer,
			 size) == size))
		return;

	perror("write failure:\n\t");
	exit(1);
	__builtin_unreachable();
}

static inline void
print_display(void)
{
	write_stdout(&display[0],
		     sizeof(display) - 1lu);
}

static inline void
player_wins(void)
{
	print_display();
	PRINT_LITERAL("player wins\n");
}

static inline void
computer_wins(void)
{	print_display();
	PRINT_LITERAL("computer wins\n");
}

static inline void
cats_game(void)
{
	print_display();
	PRINT_LITERAL("cats game\n");
}




static inline unsigned int
get_player_cell(void)
{
	char input;

	while (1) {
		read_stdin(&input,
			   sizeof(input));

		flush_stdin();

		if ((input < '9') && (input > '/'))
			return ASCII_TO_DIGIT(input);

		PRINT_LITERAL("invalid input\n> ");
	}
}


static inline void
player_move(void)
{
	unsigned int cell;
	unsigned int move;

	print_display();
	PRINT_LITERAL("player move\n> ");

	while (1) {
		cell = get_player_cell();

		move = MOVE(cell);

		if ((move & board_moveset) == 0u)
			break;

		PRINT_LITERAL("cell taken\n> ");
	}

	board_moveset  |= move;
	player_moveset |= move;

	update_moves(cell);
	update_display(cell,
		       player_token);
}

int
score_player_move(struct MoveNode *restrict move,
		  unsigned int player,
		  const unsigned int computer)
{
	int score;
	int max_score;

	player |= move->move;

	if (is_winner(player))
		return -1;

	if (rem_moves == NULL)
		return 0;

	move	  = rem_moves;
	rem_moves = rem_moves->next;
	max_score = score_computer_move(move,
					computer,
					player);
	rem_moves = move;

	for (move = move->next; move != NULL; move = move->next) {
		remove_move(move);
		score = score_computer_move(move,
					    computer,
					    player);
		insert_move(move);

		if (score > max_score)
			max_score = score;
	}

	return max_score;
}


int
score_computer_move(struct MoveNode *restrict move,
		    unsigned int computer,
		    const unsigned int player)
{
	int score;
	int min_score;

	computer |= move->move;

	if (is_winner(computer))
		return 1;

	if (rem_moves == NULL)
		return 0;

	move	  = rem_moves;
	rem_moves = rem_moves->next;
	min_score = score_player_move(move,
				      player,
				      computer);
	rem_moves = move;

	for (move = move->next; move != NULL; move = move->next) {
		remove_move(move);
		score = score_player_move(move,
					  player,
					  computer);
		insert_move(move);

		if (score < min_score)
			min_score = score;
	}

	return min_score;
}


static inline unsigned int
get_computer_cell(void)
{
	int score;
	int max_score;
	unsigned int cell;
	struct MoveNode *move;

	move	  = rem_moves;
	rem_moves = rem_moves->next;
	max_score = score_computer_move(move,
					computer_moveset,
					player_moveset);
	rem_moves = move;
	cell      = rem_moves->cell;

	for (move = move->next; move != NULL; move = move->next) {
		remove_move(move);
		score = score_computer_move(move,
					    computer_moveset,
					    player_moveset);
		insert_move(move);

		if (score > max_score) {
			max_score = score;
			cell	  = move->cell;
		}
	}

	return cell;
}


static inline void
computer_move(void)
{
	static char input[] = "0\n";

	print_display();
	PRINT_LITERAL("computer move\n> ");

	const unsigned int cell = get_computer_cell();

	input[0] = DIGIT_TO_ASCII(cell);

	write_stdout(&input[0],
		     sizeof(input));

	const unsigned int move = MOVE(cell);

	board_moveset    |= move;
	computer_moveset |= move;

	update_moves(cell);
	update_display(cell,
		       computer_token);
}
