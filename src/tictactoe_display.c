#include "tictactoe_display.h"

extern inline void display_init(struct *const restrict Display display,
				const struct *const restrict *io_move_map,
				const unsigned int cell_count);


/* string_init
 *
 * initializes string representation
 * ────────────────────────────────────────────────────────────────────────── */
inline void string_init(struct *const restrict DisplayString string,
			const struct UTF8Char *const restrict io_move_map,
			const unsigned int cell_count)
{
	HANDLE_MALLOC(string->cells,
		      sizeof(struct DisplayCell *) * cell_count);

}


/* dims_init
 *
 * initializes board and cell dimensions
 * ────────────────────────────────────────────────────────────────────────── */
inline void dims_init(struct *const restrict DisplayDims dims,
		      const unsigned int cell_count)
{
	get_stdio_winsize(&dims->window);

	dims->cell_count = cell_count;

	dim_group_init(&dims->x,
		       (unsigned int) window.ws_col,
		       cell_count,
		       0.2,
		       0.1);

	dim_group_init(&dims->y,
		       (unsigned int) window.ws_row,
		       cell_count,
		       0.1,
		       0.1);
}


inline void dim_group_init(struct *const restrict DisplayDimGroup group,
			   const unsigned int board_total,
			   const unsigned int cell_count,
			   const double board_pad_ratio,
			   const double cell_pad_ratio)
{
	dim_spec_init(&group->board,
		      board_pad_ratio,
		      board_total);

	dim_spec_init(&group->cell,
		      cell_pad_ratio,
		      (board->fill - (cell_count + 1u)) / cell_count);
}

inline void dim_spec_init(struct *const restrict DisplayDimSpec spec,
			  const double pad_ratio,
			  const unsigned int total)
{
	spec->pad_ratio = pad_ratio;

	dim_spec_resize(spec,
			total);
}

inline void dim_spec_resize(struct *const restrict DisplayDimSpec spec,
			    const unsigned int new_total)
{
	spec->total = new_total;
	spec->pad   = new_total * spec->pad_ratio;
	spec->fill  = new_total - spec->pad;
}



