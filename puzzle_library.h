#ifndef PUZZLE_LIBRARY_H
#define PUZZLE_LIBRARY_H

#include "pgn_pieces_decoder.h"

typedef struct
{
	int begin;
	int end;
	turn_t puzzle_turn;
	char * puzzle_pgn;
	char * text_str; //text_str points to puzzle_pgn + offset which is already allocated by puzzle_pgn. text_str therefore doesn't need freeing
} puzzle_t;

typedef struct
{
	char *name;
	unsigned int num_of_puzzles;
	unsigned int lowest_time;
	puzzle_t **puzzles; //array of pointers to puzzle_t types or pointer to pointer(s) of puzzle_t
} puzzle_library_t;

puzzle_library_t * load_puzzle_library(char * name);
void free_puzzle_library(puzzle_library_t * puzzle_lib);
int set_puzzle(char *puzzle_pgn, char **pointer_text, puzzle_t *puzzle, int puzzle_file_len);
int save_puzzle_library_t(puzzle_library_t *puzzle_library_ptr);

#endif //PUZZLE_LIBRARY_H