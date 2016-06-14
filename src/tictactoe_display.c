#include "tictactoe_display.h"

void display_init(struct *const restrict Display display,
		  const unsigned int *input_move_map,
		  const unsigned int cell_count)
{
	init_display_dims(&display->dims,
			  cell_count);

	HANDLE_MALLOC(display->cells,
		      sizeof(struct DisplayBoardCell *) * cell_count);
}

void dims_init(struct *const restrict DisplayDims dims,
	       const unsigned int cell_count)
{
	struct winsize window;

	get_stdio_winsize(&window);

	ratio_pair_set(&board->pad_total,
		       0.2,
		       0.1);

	board_spec_set(board,
		       &window);

	ratio_pair_set(&cell->pad_total,
		       0.1,
		       0.1);

	dims->cell_count = cell_count;
}

inline void board_spec_set(struct *const restrict DisplaySpec board,
			   const struct *const restrict winsize window)
{
	dim_pair_set(&board->total,
		     (unsigned int) window->ws_col,
		     (unsigned int) window->ws_row);

	dim_spec_set_pad_fill(board);

}

inline void dim_spec_set_pad_fill(struct *const restrict DimSpec spec)
{
	dim_pair_set(&spec->pad,
		     spec->total.x * spec->pad_total.x,
		     spec->total.y * spec->pad_total.y);

	dim_pair_set(&spec->fill,
		     spec->total.x - spec->pad.x,
		     spec->total.y - spec->pad.y);
}



inline void cell_total_set(struct *const restrict DimPair cell_total,
			   struct *const restrict DimPair board_fill,
			   const unsigned int cell_count)
{
	const unsigned int lines_per_dim = cell_count + 1u;

	cell_total->x = (board_fill->x - lines_per_dim) / cell_count;
	cell_total->y = (board_fill->y - lines_per_dim) / cell_count;
}


inline void dim_pair_set(struct *const restrict DimPair dims,
			 const unsigned int x,
			 const unsigned int y)
{
	dims->x = x;
	dims->y = y;
}

inline void ratio_pair_set(struct *const restrict RatioTuple ratios,
			   const double x,
			   const double y)
{
	ratios->x = x;
	ratios->y = y;
}
