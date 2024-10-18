#ifndef CHESS_TEXTURES_AND_DRAW_H
#define CHESS_TEXTURES_AND_DRAW_H
#include <SDL2/SDL.h>
#include "pgn_pieces_decoder.h"

/*
* The functions in this file are used to manipulate textures and render the screen
* 	using SDL2.
*/

#define COLS 					8
#define ROWS 					8
#define SQUARES_COUNT			64
#define SQUARE_W_H				80
#define SIGN_W_H				40
#define SCREEN_W				1000
#define SCREEN_H				720
#define UTILITY_SCREEN_W		280
#define UTILITY_SCREEN_H		720
#define CHESS_SCREEN_W			720
#define CHESS_SCREEN_H			720
#define CHESS_SCREEN_START_X	40
#define CHESS_SCREEN_START_Y	40

#define NUMBER_TEXTURES_N		10
#define LETTER_TEXTURES_N		26
#define PIECES_TEXTURES_N		6

#define PAWN_TEXT_N 			0
#define ROOK_TEXT_N 			1
#define KNIGHT_TEXT_N 			2
#define BISHOP_TEXT_N 			3
#define QUEEN_TEXT_N 			4
#define KING_TEXT_N 			5


//struct used to draw and detect the squares of the chessboard
typedef struct
{
	SDL_Rect rect;
	Uint32 color;
	int row;
	int col;
} chess_square_t;

typedef struct
{
	//help
	int help_x;
	int help_y;
	int visible_help;
	//select
	int select_begin_x;
	int select_begin_y;
	int visible_select_begin;
	//end
	int select_end_x;
	int select_end_y;
	int visible_select_end;
} indicators_t;

//contains all the textures
struct chess_textures_struct
{
	//chess related textures
	SDL_Texture *board_texture;
	SDL_Texture *white_pieces[PIECES_TEXTURES_N]; // the order is: p,r,n,b,q,k
	SDL_Texture *black_pieces[PIECES_TEXTURES_N];
	//numbers and letters
	SDL_Texture *number_textures[NUMBER_TEXTURES_N];
	SDL_Texture *letter_textures[LETTER_TEXTURES_N];
	SDL_Texture *dot;
	SDL_Texture *dash;
	//utility screen
	SDL_Texture *utility_bg_texture;
	SDL_Texture *white_turn_indicator;
	SDL_Texture *black_turn_indicator;
	//mainmenu screen
	SDL_Texture *mainmenu_bg_texture;
	//select marks
	SDL_Texture *select_mark_help;
	SDL_Texture *select_mark_begin;
	SDL_Texture *select_mark_end;
};


SDL_Texture * init_squares_and_board(SDL_Renderer *rend_ptr, chess_square_t *squares, Uint32 color_white, Uint32 color_black, Uint32 background_color);
SDL_Texture * init_utility_bg_texture(SDL_Renderer *rend_ptr, Uint32 color);
SDL_Texture * init_mainmenu_bg_texture(SDL_Renderer *rend_ptr, Uint32 color);

SDL_Texture * init_turn_indicator(SDL_Renderer *rend_ptr, Uint32 color);
SDL_Texture * init_dot_texture(SDL_Renderer * rend_ptr, Uint32 color);
SDL_Texture * init_dash_texture(SDL_Renderer * rend_ptr, Uint32 color);
SDL_Texture * init_select_mark(SDL_Renderer * rend_ptr, Uint32 color);

void init_piece_textures(SDL_Renderer *rend_ptr, SDL_Texture *white_pieces[], SDL_Texture *black_pieces[], Uint32 color_white, Uint32 color_black);
void init_number_textures(SDL_Renderer * rend_ptr, SDL_Texture *number_textures[], Uint32 color);
void init_letter_textures(SDL_Renderer *rend_ptr, SDL_Texture *letter_textures[], Uint32 color);

int init_window_and_renderer(SDL_Renderer **rend_ptr, SDL_Window **win_ptr, int window_w, int window_h);
void render_mainmenu_screen(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, char *puzzle_name);
void render_utility_screen(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, char *util_text, int time, int lowest_time, int cur_puzzle, int puzzles_n, int turn);
void render_chess_screen(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, char board[8][9], indicators_t *indicators, turn_t turn);
void render_text(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, char *text, int width, int max_heigth, int x, int y, int letter_size, int dash_lines);
void init_textures_and_squares(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, chess_square_t *squares);


void free_textures(struct chess_textures_struct *chess_textures);

#endif //CHESS_TEXTURES_AND_DRAW_H