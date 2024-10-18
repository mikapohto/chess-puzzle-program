#ifndef GAME_MAIN_H
#define GAME_MAIN_H
#include <SDL2/SDL.h>
#include "puzzle_library.h"
#include "chess_textures_and_draw.h"

#define FPS_TARGET	30
#define PUZZLE_NAME_LEN 29

struct button
{
	SDL_Rect area;
	int id;
};

void reset_board(char board[8][9]);
int make_a_move_copy_alg(char *puzzle_pgn, int pgn_index, char board[8][9], char buf_board[8][9], int start_col, int start_row, int end_col, int end_row, turn_t answer_turn);
int puzzle_screen(puzzle_library_t *puzzle_lib, SDL_Renderer *rend_ptr, chess_square_t squares[SQUARES_COUNT], struct chess_textures_struct *chess_textures);
void get_end_square(char *puzzle_pgn, int pgn_index, int *row, int *col);
Uint32 menu_screen(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, char puzzle_name[PUZZLE_NAME_LEN]);
int read_puzzle_names(char names[][PUZZLE_NAME_LEN], int num);

#endif //GAME_MAIN_H