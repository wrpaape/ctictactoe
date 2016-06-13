#include "tictactoe_display.h"

void init_display(struct *const restrict Display display,
		  const unsigned int *input_move_map,
		  const unsigned int cell_count)
{
	init_display_dims(&display->dims,
			  cell_count);

	HANDLE_MALLOC(display->cell_map,
		      sizeof(struct DisplayBoardCell *) * cell_count);


}

void init_display_dims(struct *const restrict DisplayDims dims,
		       const unsigned int cell_count)
{
	dims->cell_count = cell_count;

	get_stdio_winsize(&dims->window);

	dims->window.ws_row;
	dims->window.ws_col;
}
