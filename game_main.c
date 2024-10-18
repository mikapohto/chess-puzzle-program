#include <stdio.h>
#include <SDL2/SDL.h>
#include "game_main.h"
#include "pgn_pieces_decoder.h"
#include "puzzle_library.h"
#include "chess_textures_and_draw.h"
#include "random_gen.h"

int main(int argc, char *argv[])
{
	int seed;
	//Related to the chess and puzzles
	puzzle_library_t *puzzle_lib;

	//Related to SDL2
	SDL_Window *win_ptr = NULL;
	SDL_Renderer *rend_ptr = NULL;
	struct chess_textures_struct chess_textures = {NULL}; //init all pointers to NULL
	chess_square_t squares[SQUARES_COUNT];
	int window_size_w = CHESS_SCREEN_W + UTILITY_SCREEN_W;
	int window_size_h = CHESS_SCREEN_H;
	char puzzle_name[PUZZLE_NAME_LEN];
	
	//initiate SDL2 etc.
	if(init_window_and_renderer(&rend_ptr, &win_ptr, window_size_w, window_size_h) == 0)
	{
		return 1;
	}
	init_textures_and_squares(rend_ptr, &chess_textures, squares);
	
	
	seed = menu_screen(rend_ptr, &chess_textures, puzzle_name); //seed is 0 on exit
	if(seed == 0)
	{
		free_textures(&chess_textures);
		SDL_DestroyRenderer(rend_ptr);
		SDL_DestroyWindow(win_ptr);
		SDL_Quit();
		return 0;
	}
	
	init_random_gen(seed);
	
	while(1)
	{
	//initiate chess and puzzles
		puzzle_lib = load_puzzle_library(puzzle_name);
		if(puzzle_lib == NULL)
		{
			free_textures(&chess_textures);
			SDL_DestroyRenderer(rend_ptr);
			SDL_DestroyWindow(win_ptr);
			SDL_Quit();
			return 1;
		}

		shuffle_pointers((void **)puzzle_lib->puzzles, puzzle_lib->num_of_puzzles);
		if(puzzle_screen(puzzle_lib, rend_ptr, squares, &chess_textures) == 0) //returns 0 on exit
		{
			free_puzzle_library(puzzle_lib);
			break;
		}
		free_puzzle_library(puzzle_lib);
		if(menu_screen(rend_ptr, &chess_textures, puzzle_name) == 0) //returns 0 on exit
		{
			break;
		}
	}
	free_textures(&chess_textures);
	SDL_DestroyRenderer(rend_ptr);
	SDL_DestroyWindow(win_ptr);
	SDL_Quit();

	return 0;
}

/*
* Menu screen: used to load the wanted puzzle.
* Loads the selected puzzle library.
* Returns how long it took time to be in the main menu screen
*	which can be used in the random generator initialization.
* Can also return 0 on a quit or error.
*/
Uint32 menu_screen(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, char puzzle_name_re[PUZZLE_NAME_LEN])
{
	int quit_loop = 0;
	int quit_program = 0;
	int i;
	int button_id_up;
	int button_id_down;
	int puzzle_name_i = 0;
	SDL_Point mouse_xy;
	SDL_Event event;
	Uint64 screen_update_time_ms = 0, time_ms;
	char puzzle_name[8][PUZZLE_NAME_LEN];
	
	struct button buttons[3] = {{.area.x = 160, .area.y = 240, .area.w = SIGN_W_H, .area.h = SIGN_W_H, .id = 1},
								{.area.x = 800, .area.y = 240, .area.w = SIGN_W_H, .area.h = SIGN_W_H, .id = 2},
								{.area.x = 200, .area.y = 400, .area.w = 600, .area.h = 120, .id = 3}};


	if(read_puzzle_names(puzzle_name, 8) == 0)
	{
		return 0;
	}

	while(!quit_loop)
	{
		button_id_up = 0;
		button_id_down = 0;
		// handle the events shortly
		// handle them better after this while loop to keep the event handler simple
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit_loop = 1;
					quit_program = 1;
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouse_xy.x = event.button.x;
					mouse_xy.y = event.button.y;
					for(i = 0; i < 3; i++)
					{
						if(SDL_PointInRect(&mouse_xy, &buttons[i].area))
						{
							button_id_down = buttons[i].id;
							break;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					mouse_xy.x = event.button.x;
					mouse_xy.y = event.button.y;
					for(i = 0; i < 3; i++)
					{
						if(SDL_PointInRect(&mouse_xy, &buttons[i].area))
						{
							button_id_up = buttons[i].id;
							break;
						}
					}
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_LEFT && event.key.repeat == 0)
					{
						button_id_down = buttons[0].id;
					}
					else if(event.key.keysym.sym == SDLK_RIGHT && event.key.repeat == 0)
					{
						button_id_down = buttons[1].id;
					}
					break;
				case SDL_KEYUP:
					if(event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0)
					{
						button_id_up = buttons[2].id;
					}
				default:
					break;
			}
		}
		
		switch(button_id_down)
		{
			case 1:
				puzzle_name_i--;
				if(puzzle_name_i < 0)
				{
					puzzle_name_i = 7;
				}
				break;
			case 2:
				puzzle_name_i++;
				if(puzzle_name_i > 7)
				{
					puzzle_name_i = 0;
				}
				break;
			case 3:
				break;
			default:
				break;
		}
		switch(button_id_up)
		{
			case 1:
				break;
			case 2:
				break;
			case 3:
				if(puzzle_name[puzzle_name_i][0] != 0)
				{
					quit_loop = 1;
				}
				break;
			default:
				break;
		}
		
		//update screen every (1000/FPS_TARGET) millisecond.
		time_ms = SDL_GetTicks64();
		if(time_ms >= screen_update_time_ms)
		{
			render_mainmenu_screen(rend_ptr, chess_textures, puzzle_name[puzzle_name_i]);
			SDL_RenderPresent(rend_ptr);
			screen_update_time_ms = time_ms + (1000 / FPS_TARGET);
		}
	}
	if(quit_program == 1)
	{
		return 0;
	}
	for(i = 0; i < PUZZLE_NAME_LEN; i++)
	{
		puzzle_name_re[i] = puzzle_name[puzzle_name_i][i];
	}
	return SDL_GetTicks();
}

/*
* This is the actual game screen.
* Returns 0 on exit, 1 otherwise.
*/
int puzzle_screen(puzzle_library_t *puzzle_lib, SDL_Renderer *rend_ptr, chess_square_t squares[SQUARES_COUNT], struct chess_textures_struct *chess_textures)
{
	int pgn_index;
	int puzzle_i;
	int i;
	int quit = 0;
	int no_time = 0;
	int all_puzzles_done = 0;
	int squares_selected = 0;
	int help = 0;
	int start_col = 0, start_row = 0, end_col = 0, end_row = 0;
	SDL_Event event;
	char buf_board[8][9];
	char board[8][9];
	puzzle_t *puzzle_ptr = NULL;
	Uint64 start_time_ms, puzzle_time_ms, screen_update_time_ms = 0, time_ms;
	indicators_t indicators = {0,0,0,0,0,0,0,0,0};
	turn_t turn;
	SDL_Point mouse_xy;

	//set the first puzzle
	puzzle_i = 0;
	puzzle_ptr = puzzle_lib->puzzles[puzzle_i];
	turn = TURN_WHITE;
	reset_board(board);
	pgn_index = decode_pgn(board, puzzle_ptr->puzzle_pgn, 0, puzzle_ptr->begin, &turn);
	time_ms = SDL_GetTicks64();
	start_time_ms = time_ms;

	while(!quit)
	{
		// handle the events shortly
		// handle them better after this while loop to keep the event handler simple
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = 1;
					break;
				case SDL_MOUSEBUTTONDOWN:
					indicators.visible_select_begin = 0;
					mouse_xy.x = event.button.x;
					mouse_xy.y = event.button.y;
					if(turn == TURN_BLACK) //The board is inverted so invert the mouse too to hit the right square
					{
						//invert the mouse
						mouse_xy.x = CHESS_SCREEN_W - mouse_xy.x;
						mouse_xy.y = CHESS_SCREEN_H - mouse_xy.y;
					}
					//find if the mouse_xy collides with a square
					for(i = 0; i < SQUARES_COUNT; i++)
					{
						if(SDL_PointInRect(&mouse_xy, &squares[i].rect))
						{
							start_row = squares[i].row;
							start_col = squares[i].col;
							squares_selected = 1;
							break;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					mouse_xy.x = event.button.x;
					mouse_xy.y = event.button.y;
					if(turn == TURN_BLACK) //The board is inverted so invert the mouse too to hit the right square
					{
						//invert the mouse
						mouse_xy.x = CHESS_SCREEN_W - mouse_xy.x;
						mouse_xy.y = CHESS_SCREEN_H - mouse_xy.y;
					}
					//find if the mouse_xy collides with a square
					for(i = 0; i < SQUARES_COUNT; i++)
					{
						if(SDL_PointInRect(&mouse_xy, &squares[i].rect))
						{
							end_row = squares[i].row;
							end_col = squares[i].col;
							squares_selected = 2;
							break;
						}
					}
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_h && event.key.repeat == 0)
					{
						help = 1;
					}
					if(event.key.keysym.sym == SDLK_ESCAPE && event.key.repeat == 0)
					{
						quit = 1;
						no_time = 1;
					}
					if(event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0)
					{
						if(squares_selected == 0)
						{
							indicators.visible_select_end = 1;
							if(turn == TURN_WHITE)
							{
								start_row = indicators.select_begin_y;
								start_col = indicators.select_begin_x;
							}
							else //TURN_BLACK
							{
								//the board is inverted
								start_row = 7 - indicators.select_begin_y;
								start_col = 7 - indicators.select_begin_x;
							}
							indicators.select_end_x = indicators.select_begin_x;
							indicators.select_end_y = indicators.select_begin_y;
							squares_selected++;
						}
						else if(squares_selected == 1)
						{
							if(turn == TURN_WHITE)
							{
								end_row = indicators.select_end_y;
								end_col = indicators.select_end_x;
							}
							else //TURN_BLACK
							{
								//the board is inverted
								end_row = 7 - indicators.select_end_y;
								end_col = 7 - indicators.select_end_x;
							}
							indicators.select_begin_x = indicators.select_end_x;
							indicators.select_begin_y = indicators.select_end_y;
							squares_selected++;
						}
						else
						{
							//not possible
							squares_selected = 0;
						}
					}
					if(event.key.keysym.sym == SDLK_LEFT && event.key.repeat == 0)
					{
						if(squares_selected == 0 && indicators.select_begin_x > 0)
						{
							indicators.visible_select_begin = 1;
							indicators.select_begin_x--;
						}
						if(squares_selected == 1 && indicators.select_end_x > 0)
						{
							indicators.visible_select_end = 1;
							indicators.select_end_x--;
						}
					}
					if(event.key.keysym.sym == SDLK_RIGHT && event.key.repeat == 0)
					{
						if(squares_selected == 0 && indicators.select_begin_x < 7)
						{
							indicators.visible_select_begin = 1;
							indicators.select_begin_x++;
						}
						if(squares_selected == 1 && indicators.select_end_x < 7)
						{
							indicators.visible_select_end = 1;
							indicators.select_end_x++;
						}
					}
					if(event.key.keysym.sym == SDLK_DOWN && event.key.repeat == 0)
					{
						if(squares_selected == 0 && indicators.select_begin_y > 0)
						{
							indicators.visible_select_begin = 1;
							indicators.select_begin_y--;
						}
						if(squares_selected == 1 && indicators.select_end_y > 0)
						{
							indicators.visible_select_end = 1;
							indicators.select_end_y--;
						}
					}
					if(event.key.keysym.sym == SDLK_UP && event.key.repeat == 0)
					{
						if(squares_selected == 0 && indicators.select_begin_y < 7)
						{
							indicators.visible_select_begin = 1;
							indicators.select_begin_y++;
						}
						if(squares_selected == 1 && indicators.select_end_y < 7)
						{
							indicators.visible_select_end = 1;
							indicators.select_end_y++;
						}
					}
					break;
				default:
					break;
			}
		}
		
		//do a puzzle move
		//squares selected: 1 first square, 2 both squares
		if(squares_selected == 2)
		{
			squares_selected = 0;
			if(make_a_move_copy_alg(puzzle_ptr->puzzle_pgn, pgn_index, board, buf_board, start_col, start_row, end_col, end_row, turn) == 1)
			{
				pgn_index = decode_pgn(board, puzzle_ptr->puzzle_pgn, pgn_index, 2, &turn);
				if(pgn_index == 0) //puzzle is over
				{
					puzzle_i++;
					if(puzzle_i >= puzzle_lib->num_of_puzzles)
					{
						quit = 1;
						all_puzzles_done = 1;
					}
					else
					{
						//set the next puzzle
						puzzle_ptr = puzzle_lib->puzzles[puzzle_i];
						turn = TURN_WHITE;
						reset_board(board);
						pgn_index = decode_pgn(board, puzzle_ptr->puzzle_pgn, 0, puzzle_ptr->begin, &turn);
					}
				}
			}
			indicators.help_x = 0;
			indicators.help_y = 0;
			indicators.visible_help = 0;
			indicators.visible_select_end = 0;
		}
		
		if(help == 1)
		{
			help = 0;
			get_end_square(puzzle_ptr->puzzle_pgn, pgn_index, &indicators.help_x, &indicators.help_y);
			indicators.visible_help = 1;
		}
		//update screen every (1000/FPS_TARGET) millisecond.
		time_ms = SDL_GetTicks64();
		if(time_ms >= screen_update_time_ms)
		{
			puzzle_time_ms = time_ms - start_time_ms;
			render_chess_screen(rend_ptr, chess_textures, board, &indicators, turn);
			render_utility_screen(rend_ptr, chess_textures, puzzle_ptr->text_str, puzzle_time_ms, puzzle_lib->lowest_time, puzzle_i + 1, puzzle_lib->num_of_puzzles, turn);
			SDL_RenderPresent(rend_ptr);
			screen_update_time_ms = time_ms + (1000 / FPS_TARGET);
		}
	}
	
	if(no_time == 1)
	{
		return 1;
	}
	if(all_puzzles_done)
	{
		if(puzzle_lib->lowest_time == 0 || puzzle_time_ms < puzzle_lib->lowest_time)
		{
			puzzle_lib->lowest_time = puzzle_time_ms;
			save_puzzle_library_t(puzzle_lib);
		}
		return 1;
	}
	return 0;
}


/*
* The function returns 1 if the move is correct, 0 otherwise.
* The following algorith works in the following way: it copies the current board to buf_boar
* and advances it by 1 move. Then it finds the starting square and end square
* and compares them to the advanced board. If the move is correct then both the
* start square and the end square should be changed and the start square should be empty.
*/
int make_a_move_copy_alg(char *puzzle_pgn, int pgn_index, char board[8][9], char buf_board[8][9], int start_col, int start_row, int end_col, int end_row, turn_t answer_turn)
{
	int i;	
	//copy board to buf_board
	for(i = 0; i < 8*9; i++)
	{
		*((char *)buf_board + i) = *((char *)board + i);
	}
	
	//update the buf_board
	decode_pgn_step(buf_board, puzzle_pgn, pgn_index, answer_turn);
	
	if(start_row == end_row && start_col == end_col)
	{
		return 0;
	}
	
	if(board[start_row][start_col] == '.')
	{
		return 0;
	}
	if(buf_board[start_row][start_col] != '.')
	{
		return 0;
	}
	
	if(board[start_row][start_col] != buf_board[start_row][start_col] &&
		board[end_row][end_col] != buf_board[end_row][end_col])
	{
		//the piece on starting square has changed and the piece on the end square has changed
		return 1;
	}
	return 0;
}

/*
* changes row and col according to the correct move.
*/
void get_end_square(char *puzzle_pgn, int pgn_index, int *row, int *col)
{
	int i = pgn_index;
	while(puzzle_pgn[++i] != '.')
	{
		//do nothing
	}
	if(puzzle_pgn[i - 2] == '=') //promotion
	{
		*col = puzzle_pgn[i - 3] - '1';
		*row = puzzle_pgn[i - 4] - 'a';

	}
	else
	{
		*col = puzzle_pgn[i - 1] - '1';
		*row = puzzle_pgn[i - 2] - 'a';
	}
}

/*
* Resets the board.
* the row 0 is the white row side
*/
void reset_board(char board[8][9])
{
	char reset_board[8][9] = {	"RNBQKBNR", // row 1
								"PPPPPPPP", // row 2
								"........", // row 3
								"........", // ...
								"........", // x-axis mirrored
								"........", //
								"pppppppp", //
								"rnbqkbnr"};// 
	int i;
	for(i = 0; i < 8*9; i++)
	{
		*((char *)board + i) = *((char *)reset_board + i);
	}
}

/*
* read num names of max length PUZZLE_NAME_LEN from menu_data.txt
* returns 1 on success, 0 otherwise.
*/
int read_puzzle_names(char names[][PUZZLE_NAME_LEN], int num)
{
	int name_i, i;
	char c;
	FILE *file_ptr;
	
	file_ptr = fopen("menu_data.txt", "r");
	if(file_ptr == NULL)
	{
		return 0;
	}
	for(name_i = 0; name_i < num; name_i++)
	{
		names[name_i][0] = '\0';
		for(i = 0; i < PUZZLE_NAME_LEN - 1 && (c = fgetc(file_ptr)) != ';' && c != EOF; i++)
		{
			names[name_i][i] = c;
		}
		names[name_i][i] = '\0';
	}
	fclose(file_ptr);
	return 1;
}