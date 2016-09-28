#include "tictactoe.h"

int
main(void)
{
	unsigned int taken = 0u;
	unsigned int cell;
	unsigned int move;

	do {
		print_board();

		cell = get_cell();

		move = MOVE(cell);

		if ((move & taken) == move) {
			write_stdout("cell taken\n",
				     sizeof("cell taken\n") - 1lu);
			continue;
		}

		taken |= move;

		update_board(cell,
			     'X');

	} while (!is_winner(taken));

	print_board();

	write_stdout("game over\n",
		     sizeof("game over\n") - 1lu);

	return 0;
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
update_board(const unsigned int cell,
	     const char token)
{
	*(board_map[cell]) = token;
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
print_board(void)
{
	write_stdout(&board[0],
		     sizeof(board) - 1lu);
}

static inline unsigned int
get_cell(void)
{
	char input;

	write_stdout("player move:\n",
		     sizeof("player move:\n") - 1lu);

	while (1) {
		read_stdin(&input,
			   sizeof(input));

		flush_stdin();

		if ((input < '9') && (input > '/'))
			return ASCII_TO_DIGIT(input);

		write_stdout("invalid input\n",
			     sizeof("invalid input\n") - 1lu);
	}
}

