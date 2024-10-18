#include <SDL2/SDL.h>
#include "chess_textures_and_draw.h"
#include "pgn_pieces_decoder.h"

const static SDL_Rect rects_pawn[] = {{20, 60, 40, 10}, {35, 30, 10, 40}, {30, 30, 20, 20}};
const static SDL_Rect rects_rook[] = {{20, 60, 40, 10}, {25, 50, 30, 10}, {30, 30, 20, 40}, {25, 25, 30, 10}, {20, 20, 40, 10}};
const static SDL_Rect rects_knight[] = {{20, 60, 40, 10}, {25, 50, 30, 10}, {40, 30, 15, 20}, {25, 20, 30, 15}, {25, 30, 10, 10}};
const static SDL_Rect rects_bishop[] = {{20, 60, 40, 10}, {25, 50, 30, 10}, {35, 30, 10, 40}, {30, 20, 20, 20}, {35, 15, 10, 5}};
const static SDL_Rect rects_queen[] = {{20, 60, 40, 10}, {25, 50, 30, 10},  {30, 30, 20, 40}, {20, 25, 40, 10}, {15, 15, 10, 10}, {35, 15, 10, 10}, {55, 15, 10, 10}};
const static SDL_Rect rects_king[] = {{20, 60, 40, 10}, {25, 50, 30, 10}, {30, 30, 20, 40}, {25, 21, 30, 20}, {34, 12, 12, 6}, {37, 9, 6, 12}};

const static SDL_Rect *rects_pieces[] = {rects_pawn, rects_rook, rects_knight, rects_bishop, rects_queen, rects_king};
const static int rects_pieces_sizes[] = {3, 5, 5, 5, 7, 6};

const static SDL_Rect rects_num_0[] = {{10,10,20,5},{10,10,5,25},{25,10,5,25},{10,30,20,5}};
const static SDL_Rect rects_num_1[] = {{15,10,5,5}, {20,10,5,25}};
const static SDL_Rect rects_num_2[] = {{10,10,20,5},{25,10,5,15},{10,20,20,5},{10,20,5,15},{10,30,20,5}};
const static SDL_Rect rects_num_3[] = {{10,10,20,5},{10,20,20,5},{10,30,20,5},{25,10,5,25}};
const static SDL_Rect rects_num_4[] = {{10,10,5,15},{10,20,20,5},{25,10,5,25}};
const static SDL_Rect rects_num_5[] = {{10,10,20,5},{10,10,5,15},{10,20,20,5},{25,20,5,15},{10,30,20,5}};
const static SDL_Rect rects_num_6[] = {{10,10,20,5},{10,10,5,20},{10,20,20,5},{25,20,5,15},{10,30,20,5}};
const static SDL_Rect rects_num_7[] = {{10,10,20,5},{25,10,5,25}};
const static SDL_Rect rects_num_8[] = {{10,10,20,5},{10,10,5,20},{10,20,20,5},{25,10,5,25},{10,30,20,5}};
const static SDL_Rect rects_num_9[] = {{10,10,20,5},{10,10,5,15},{10,20,20,5},{10,30,20,5},{25,10,5,25}};

const static SDL_Rect *rects_nums[] = {
			rects_num_0, rects_num_1, rects_num_2, rects_num_3, rects_num_4,
			rects_num_5, rects_num_6, rects_num_7, rects_num_8, rects_num_9};


const static int rects_num_sizes[] = {4,2,5,4,3,5,5,2,5,5};

const static SDL_Rect rects_a[] = {{10,10,20,5},{10,10,5,25},{10,20,20,5},{25,10,5,25}};
const static SDL_Rect rects_b[] = {{10,10,20,5},{10,10,5,20},{10,20,15,5},{10,30,15,5},{25,10,5,10}, {25,25,5,10}};
const static SDL_Rect rects_c[] = {{10,10,20,5},{10,10,5,20},{10,30,20,5}};
const static SDL_Rect rects_d[] = {{10,10,15,5},{10,10,5,25},{25,15,5,15},{10,30,15,5}};
const static SDL_Rect rects_e[] = {{10,10,20,5},{10,20,20,5},{10,30,20,5},{10,10,5,25}};
const static SDL_Rect rects_f[] = {{10,10,20,5},{10,20,20,5},{10,10,5,25}};
const static SDL_Rect rects_g[] = {{10,10,20,5},{10,10,5,20},{10,30,20,5},{20,20,10,5},{25,20,5,10}};
const static SDL_Rect rects_h[] = {{10,10,5,25},{10,20,20,5},{25,10,5,25}};
const static SDL_Rect rects_i[] = {{15,10,5,25}};
const static SDL_Rect rects_j[] = {{25,10,5,25},{10,30,15,5},{10,25,5,5}};
const static SDL_Rect rects_k[] = {{10,10,5,25},{10,20,15,5},{25,10,5,10},{25,25,5,10}};
const static SDL_Rect rects_l[] = {{10,10,5,25},{10,30,20,5}};
const static SDL_Rect rects_m[] = {{10,10,25,5},{10,10,5,25}, {20,10,5,25},{30,10,5,25}};
const static SDL_Rect rects_n[] = {{10,10,20,5},{10,10,5,25}, {25,10,5,25}};
const static SDL_Rect rects_o[] = {{10,10,20,5},{10,10,5,25},{25,10,5,25},{10,30,20,5}};
const static SDL_Rect rects_p[] = {{10,10,20,5},{10,10,5,25},{25,10,5,15},{10,20,20,5}};
const static SDL_Rect rects_q[] = {{10,10,20,5},{10,10,5,25},{25,10,5,25},{10,30,25,5}};
const static SDL_Rect rects_r[] = {{10,10,20,5},{10,10,5,25},{25,10,5,10},{10,20,15,5},{25,25,5,10}};
const static SDL_Rect rects_s[] = {{10,10,20,5},{10,10,5,15},{10,20,20,5},{25,20,5,15},{10,30,20,5}};
const static SDL_Rect rects_t[] = {{10,10,20,5},{20,10,5,25}};
const static SDL_Rect rects_u[] = {{10,10,5,25},{25,10,5,25},{10,30,20,5}};
const static SDL_Rect rects_v[] = {{10,10,5,25},{25,10,5,20},{10,30,15,5}};
const static SDL_Rect rects_w[] = {{10,30,25,5},{10,10,5,25},{20,10,5,25},{30,10,5,25}};
const static SDL_Rect rects_x[] = {{10,10,5,10},{10,25,5,10},{15,20,10,5},{25,10,5,10},{25,25,5,10}};
const static SDL_Rect rects_y[] = {{10,10,5,10},{25,10,5,15},{10,20,20,5},{20,25,5,10}};
const static SDL_Rect rects_z[] = {{10,10,20,5},{15,20,10,5},{10,30,20,5},{25,15,5,5},{10,25,5,5}};

const static SDL_Rect *rects_letters[] = {	rects_a, rects_b, rects_c, rects_d,
											rects_e, rects_f, rects_g, rects_h,
											rects_i, rects_j, rects_k, rects_l,
											rects_m, rects_n, rects_o, rects_p,
											rects_q, rects_r, rects_s, rects_t,
											rects_u, rects_v, rects_w, rects_x,
											rects_y, rects_z};

const static int rects_letter_sizes[] = {	4, 6, 3, 4,
											4, 3, 5, 3,
											1, 3, 4, 2,
											4, 3, 4, 4,
											4, 5, 5, 2,
											3, 3, 4, 5,
											4, 5};
											
const static SDL_Rect rects_dot[] = {{10,30,5,5}};
const static SDL_Rect rects_dash[] = {{10,20,20,5}};

/*
* inits squares[64] structures and returns the chessboard SDL_Texture
* the squares can be easily used to check whether the user clicks the square with a cursor.
* The chessboard texture contains borders with width of CHESS_SCREEN_START_X and height of CHESS_SCREEN_START_Y
* The are represented in hex 0xRRGGBBAA
*/
SDL_Texture * init_squares_and_board(SDL_Renderer *rend_ptr, chess_square_t *squares, Uint32 color_white, Uint32 color_black, Uint32 background_color)
{
	SDL_Texture * text_ptr = NULL;
	SDL_Surface * surface_ptr = NULL;
	int row_i, col_i;
	int total_i;

	surface_ptr = SDL_CreateRGBSurface(0, CHESS_SCREEN_W, CHESS_SCREEN_H, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	//fill the background
	SDL_FillRect(surface_ptr, NULL, background_color);

	for(row_i = 0, total_i = 0; row_i < ROWS; row_i++)
	{
		for(col_i = 0; col_i < COLS; col_i++, total_i++)
		{
			squares[total_i].row = col_i;	//notice row = col_i
			squares[total_i].col = row_i;	//and col = row_i
			squares[total_i].rect.x = CHESS_SCREEN_START_X + row_i * SQUARE_W_H;
			squares[total_i].rect.y = CHESS_SCREEN_START_Y + (COLS - col_i - 1) * SQUARE_W_H;
			squares[total_i].rect.w = SQUARE_W_H;
			squares[total_i].rect.h = SQUARE_W_H;
			
			if(((total_i + row_i) & 0x1) == 0) // if (total_i + row_i) % 2 == 0 color black, otherwise white
			{
				squares[total_i].color = color_black;
			}
			else
			{
				squares[total_i].color = color_white;
			}
			//add the square to the surface
			SDL_FillRect(surface_ptr, &squares[total_i].rect, squares[total_i].color);
		}
	}

	text_ptr = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	SDL_FreeSurface(surface_ptr);
	return text_ptr;
}

/*
* Inits piece textures.
*/
void init_piece_textures(SDL_Renderer *rend_ptr, SDL_Texture *white_pieces[], SDL_Texture *black_pieces[], Uint32 color_white, Uint32 color_black)
{
	int i;
	SDL_Surface * surface_ptr = NULL;
	SDL_Rect remove_rect = {40,20,5,5}; //this is used to remove a piece from the bishop
	
	
	surface_ptr = SDL_CreateRGBSurface(0, SQUARE_W_H, SQUARE_W_H, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	for(i = 0; i < PIECES_TEXTURES_N; i++)
	{
		SDL_FillRect(surface_ptr, NULL, 0xFFFFFF00);
		SDL_FillRects(surface_ptr, rects_pieces[i], rects_pieces_sizes[i], color_white);
		if(i == BISHOP_TEXT_N)
		{
			SDL_FillRect(surface_ptr, &remove_rect, 0x00000000);
		}
		white_pieces[i] = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	}
	for(i = 0; i < PIECES_TEXTURES_N; i++)
	{
		SDL_FillRect(surface_ptr, NULL, 0xFFFFFF00);
		SDL_FillRects(surface_ptr, rects_pieces[i], rects_pieces_sizes[i], color_black);
		if(i == BISHOP_TEXT_N)
		{
			SDL_FillRect(surface_ptr, &remove_rect, 0x00000000);
		}
		black_pieces[i] = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	}
	SDL_FreeSurface(surface_ptr);
}

/*
* Inits number textures.
*/
void init_number_textures(SDL_Renderer *rend_ptr, SDL_Texture *number_textures[], Uint32 color)
{
	int i;
	SDL_Surface * surface_ptr = NULL;
	
	surface_ptr = SDL_CreateRGBSurface(0, SIGN_W_H, SIGN_W_H, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	for(i = 0; i < NUMBER_TEXTURES_N; i++)
	{
		SDL_FillRect(surface_ptr, NULL, 0xFFFFFF00);
		SDL_FillRects(surface_ptr, rects_nums[i], rects_num_sizes[i], color);
		number_textures[i] = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	}
	SDL_FreeSurface(surface_ptr);
}

/*
* Inits letter textures.
*/
void init_letter_textures(SDL_Renderer *rend_ptr, SDL_Texture *letter_textures[], Uint32 color)
{
	SDL_Surface * surface_ptr = NULL;
	int i;
	
	surface_ptr = SDL_CreateRGBSurface(0, SIGN_W_H, SIGN_W_H, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	for(i = 0; i < LETTER_TEXTURES_N; i++)
	{
		SDL_FillRect(surface_ptr, NULL, 0xFFFFFF00);
		SDL_FillRects(surface_ptr, rects_letters[i], rects_letter_sizes[i], color);
		letter_textures[i] = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	}
	SDL_FreeSurface(surface_ptr);
}

/*
* Inits the dot texture.
*/
SDL_Texture * init_dot_texture(SDL_Renderer * rend_ptr, Uint32 color)
{
	SDL_Texture * text_ptr = NULL;
	SDL_Surface * surface_ptr = NULL;
	
	//create a surface
	surface_ptr = SDL_CreateRGBSurface(0, SIGN_W_H, SIGN_W_H, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	SDL_FillRect(surface_ptr, NULL, 0xFFFFFF00);
	SDL_FillRects(surface_ptr, rects_dot, 1, color);
	
	text_ptr = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	SDL_FreeSurface(surface_ptr);
	return text_ptr;
}

/*
* Inits the dash texture.
*/
SDL_Texture * init_dash_texture(SDL_Renderer * rend_ptr, Uint32 color)
{
	SDL_Texture * text_ptr = NULL;
	SDL_Surface * surface_ptr = NULL;
	
	//create a surface
	surface_ptr = SDL_CreateRGBSurface(0, SIGN_W_H, SIGN_W_H, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	SDL_FillRect(surface_ptr, NULL, 0xFFFFFF00);
	SDL_FillRects(surface_ptr, rects_dash, 1, color);
	
	text_ptr = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	SDL_FreeSurface(surface_ptr);
	return text_ptr;
}

/*
* Inits the turn indicator texture.
*/
SDL_Texture * init_turn_indicator(SDL_Renderer *rend_ptr, Uint32 color)
{
	SDL_Texture *text_ptr = NULL;
	SDL_Surface *surface_ptr = NULL;
	
	surface_ptr = SDL_CreateRGBSurface(0, UTILITY_SCREEN_W * 6 / 8, 100, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	SDL_FillRect(surface_ptr, NULL, color);
	
	text_ptr = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	SDL_FreeSurface(surface_ptr);
	return text_ptr;
}

/*
* Inits the turn select mark texture.
*/
SDL_Texture * init_select_mark(SDL_Renderer * rend_ptr, Uint32 color)
{
	SDL_Texture *text_ptr = NULL;
	SDL_Surface *surface_ptr = NULL;
	SDL_Rect rect = {5,5,70,70};
	SDL_Rect alpha_rect = {10,10,60,60};

	surface_ptr = SDL_CreateRGBSurface(0, SQUARE_W_H, SQUARE_W_H, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	
	SDL_FillRect(surface_ptr, NULL, 0xFFFFFF00);
	SDL_FillRect(surface_ptr, &rect, color);
	SDL_FillRect(surface_ptr, &alpha_rect, 0x00000000);
	
	text_ptr = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	SDL_FreeSurface(surface_ptr);
	return text_ptr;
}

/*
* Inits the utility screen background texture.
*/
SDL_Texture * init_utility_bg_texture(SDL_Renderer *rend_ptr, Uint32 color)
{
	SDL_Texture *text_ptr = NULL;
	SDL_Surface *surface_ptr = NULL;
	SDL_Rect rects[8] = {{90,215,5,5},{90,225,5,5},{190,215,5,5},{190,225,5,5}, {90,135,5,5},{90,145,5,5},{190,135,5,5},{190,145,5,5}};
	
	surface_ptr = SDL_CreateRGBSurface(0, UTILITY_SCREEN_W, UTILITY_SCREEN_H, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	
	//fill the background
	SDL_FillRect(surface_ptr, NULL, color);
	SDL_FillRects(surface_ptr, rects, 8, 0xFFFFFFFF); //create colon as part of the surface
	
	text_ptr = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	SDL_FreeSurface(surface_ptr);
	return text_ptr;
}

/*
* Inits the mainmenu background texture.
*/
SDL_Texture * init_mainmenu_bg_texture(SDL_Renderer *rend_ptr, Uint32 color)
{
	SDL_Texture *text_ptr = NULL;
	SDL_Surface *surface_ptr = NULL;
	SDL_Rect rects[2] = {{200, 200, 600, 120}, {200, 400, 600, 120}};
	surface_ptr = SDL_CreateRGBSurface(0, SCREEN_W, SCREEN_H, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	
	//fill the background
	SDL_FillRect(surface_ptr, NULL, color);
	SDL_FillRects(surface_ptr, rects, 2, 0x000000FF); //create colon as part of the surface
	
	text_ptr = SDL_CreateTextureFromSurface(rend_ptr, surface_ptr);
	SDL_FreeSurface(surface_ptr);
	return text_ptr;
}

/*
* Renders the mainmenu screen.
*/
void render_mainmenu_screen(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, char *puzzle_name)
{
	SDL_RenderCopy(rend_ptr, chess_textures->mainmenu_bg_texture, NULL, NULL);
	render_text(rend_ptr, chess_textures, puzzle_name, 14, 2, 220, 220, 0, 0);
	render_text(rend_ptr, chess_textures, "o", 1, 1, 160, 240, 0, 0);
	render_text(rend_ptr, chess_textures, "o", 1, 1, 800, 240, 0, 0);
	render_text(rend_ptr, chess_textures, "play", 4, 1, 420, 440, 0, 0);
	render_text(rend_ptr, chess_textures, "press h for help", 16, 1, 180, 560, 0, 0);
}


/*
* Renders text on the screen. Use only lowercase letters.
* if letter_size == 0 then use default size SIGN_W_H
*/
void render_text(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, char *text, int width, int max_heigth, int x, int y, int letter_size, int dash_lines)
{
	int w, h, text_i;
	char c;
	SDL_Rect rect_location = {0, 0, SIGN_W_H, SIGN_W_H};
	
	if(letter_size != 0)
	{
		rect_location.w = letter_size;
		rect_location.h = letter_size;
	}
	
	rect_location.x = x;
	rect_location.y = y;
	text_i = 0;
	w = 0;
	h = 0;
	for(text_i = 0; (c = text[text_i]) != 0; text_i++)
	{
		if(c >= 'a' && c <= 'z')	//letter
		{
			if(dash_lines == 1 && w == width - 1 && (text[text_i + 1] >= 'a' && text[text_i + 1] <= 'z')) //dash line to cut the text
			{
				if(text[text_i - 1] != ' ') //to not start a word with a dash line
				{
					SDL_RenderCopy(rend_ptr, chess_textures->dash, NULL, &rect_location);
				}
				text_i--;
			}
			else
			{
				SDL_RenderCopy(rend_ptr, chess_textures->letter_textures[c - 'a'], NULL, &rect_location);
			}
		}
		else if(c >= '0' && c <= '9') //number
		{
			SDL_RenderCopy(rend_ptr, chess_textures->number_textures[c - '0'], NULL, &rect_location);
		}
		else if(c == ' ')
		{
			if(w == 0)
			{
				//if the row begins with spaces, then skip them
				continue;
			}
		}
		else if(c == '-')
		{
			SDL_RenderCopy(rend_ptr, chess_textures->dash, NULL, &rect_location);
		}
		else //rest are replaced with a dot including the dot
		{
			SDL_RenderCopy(rend_ptr, chess_textures->dot, NULL, &rect_location);
		}
		rect_location.x += rect_location.w;
		
		w++;
		if(w >= width)
		{
			w = 0;
			h++;
			rect_location.x = x;
			rect_location.y += rect_location.h;
		}
		if(h >= max_heigth)
		{
			break;
		}
	}
}

/*
* Renders utility screen.
* 1 <= cur_puzzle <= 999 and 1 <= puzzles_n <= 999
*/
void render_utility_screen(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, char *util_text, int time, int lowest_time, int cur_puzzle, int puzzles_n, int turn)
{
	int h, m, s;
	int i;
	int times[6]; //hours2,minutes2,seconds2
	int lowest_times[6];
	char puzz_str[8] = "nnn-nnn";
	SDL_Rect rect_location = {CHESS_SCREEN_W, 0, UTILITY_SCREEN_W, UTILITY_SCREEN_H};
	SDL_Rect rect_time_locations[6] = {{0 + CHESS_SCREEN_W,200,40,40},{40 + CHESS_SCREEN_W,200,40,40},
										{100 + CHESS_SCREEN_W,200,40,40},{140 + CHESS_SCREEN_W,200,40,40},
										{200 + CHESS_SCREEN_W,200,40,40},{240 + CHESS_SCREEN_W,200,40,40}};
										
	SDL_Rect rect_lowest_time_locations[6] = {{0 + CHESS_SCREEN_W,120,40,40},{40 + CHESS_SCREEN_W,120,40,40},
										{100 + CHESS_SCREEN_W,120,40,40},{140 + CHESS_SCREEN_W,120,40,40},
										{200 + CHESS_SCREEN_W,120,40,40},{240 + CHESS_SCREEN_W,120,40,40}};
										
	SDL_Rect turn_indicator_location = {0 + CHESS_SCREEN_W + UTILITY_SCREEN_W / 8, 260, UTILITY_SCREEN_W * 6 / 8, 100};
	
	SDL_RenderCopy(rend_ptr, chess_textures->utility_bg_texture, NULL, &rect_location);


	puzz_str[2] = cur_puzzle % 10 + '0';
	puzz_str[1] = (cur_puzzle / 10) % 10 + '0';
	puzz_str[0] = cur_puzzle / 100 + '0';
	puzz_str[6] = puzzles_n % 10 + '0';
	puzz_str[5] = (puzzles_n / 10) % 10 + '0';
	puzz_str[4] = puzzles_n / 100 + '0';
	
	render_text(rend_ptr, chess_textures, puzz_str, 7, 1, CHESS_SCREEN_W, 40, 0, 0);
	
	time /= 1000; //time in seconds
	s = time % 60; //seconds
	m = (time / 60) % 60; //minutes
	h = time / 3600; //hours 
	
	//calculate the numbers to be used on the screen
	times[5] = s % 10;
	times[4] = s / 10;
	times[3] = m % 10;
	times[2] = m / 10;
	times[1] = h % 10;
	times[0] = h / 10;
	
	//render time on the screen
	for(i = 0; i < 6; i++)
	{
		SDL_RenderCopy(rend_ptr, chess_textures->number_textures[times[i]], NULL, &rect_time_locations[i]);
	}
	
	//lowest_time:
	lowest_time /= 1000; //time in seconds
	s = lowest_time % 60; //seconds
	m = (lowest_time / 60) % 60; //minutes
	h = lowest_time / 3600; //hours 
	
	//calculate the numbers to be used on the screen
	lowest_times[5] = s % 10;
	lowest_times[4] = s / 10;
	lowest_times[3] = m % 10;
	lowest_times[2] = m / 10;
	lowest_times[1] = h % 10;
	lowest_times[0] = h / 10;
	
	//render lowest_time on the screen
	for(i = 0; i < 6; i++)
	{
		SDL_RenderCopy(rend_ptr, chess_textures->number_textures[lowest_times[i]], NULL, &rect_lowest_time_locations[i]);
	}
	
	//render turn indicator
	if(turn == TURN_WHITE)
	{
		SDL_RenderCopy(rend_ptr, chess_textures->white_turn_indicator, NULL, &turn_indicator_location);
	}
	else //TURN_BLACK
	{
		SDL_RenderCopy(rend_ptr, chess_textures->black_turn_indicator, NULL, &turn_indicator_location);
	}
	
	if(util_text != NULL)
	{
		render_text(rend_ptr, chess_textures, util_text, 14, 16, CHESS_SCREEN_W, 400, 20, 1);
	}
}

/*
* Renders the chess puzzle screen.
*/
void render_chess_screen(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, char board[8][9], indicators_t *indicators, turn_t turn)
{
	int i, j;
	SDL_Rect rect_board = {0,0,0,0};
	SDL_Rect draw_rect;

	rect_board.w = CHESS_SCREEN_W;
	rect_board.h = CHESS_SCREEN_H;

	SDL_RenderCopy(rend_ptr, chess_textures->board_texture, NULL, &rect_board);
		
	draw_rect.w = SQUARE_W_H;
	draw_rect.h = SQUARE_W_H;
	//draw the pieces
	for(i = 0; i < COLS; i++)
	{
		for(j = 0; j < ROWS; j++)
		{
			if(turn == TURN_WHITE)
			{
				draw_rect.x = CHESS_SCREEN_START_X + j * SQUARE_W_H;
				draw_rect.y = CHESS_SCREEN_START_Y + (7-i) * SQUARE_W_H;
			}
			else //TURN_BLACK
			{
				draw_rect.x = CHESS_SCREEN_START_X + (7-j) * SQUARE_W_H;
				draw_rect.y = CHESS_SCREEN_START_Y + i * SQUARE_W_H;
			}

			switch(board[i][j])
			{
				case 'P':
					SDL_RenderCopy(rend_ptr, chess_textures->white_pieces[PAWN_TEXT_N], NULL, &draw_rect);
					break;
				case 'R':
					SDL_RenderCopy(rend_ptr, chess_textures->white_pieces[ROOK_TEXT_N], NULL, &draw_rect);
					break;
				case 'N':
					SDL_RenderCopy(rend_ptr, chess_textures->white_pieces[KNIGHT_TEXT_N], NULL, &draw_rect);
					break;
				case 'B':
					SDL_RenderCopy(rend_ptr, chess_textures->white_pieces[BISHOP_TEXT_N], NULL, &draw_rect);
					break;
				case 'Q':
					SDL_RenderCopy(rend_ptr, chess_textures->white_pieces[QUEEN_TEXT_N], NULL, &draw_rect);
					break;
				case 'K':
					SDL_RenderCopy(rend_ptr, chess_textures->white_pieces[KING_TEXT_N], NULL, &draw_rect);
					break;
				case 'p':
					SDL_RenderCopy(rend_ptr, chess_textures->black_pieces[PAWN_TEXT_N], NULL, &draw_rect);
					break;
				case 'r':
					SDL_RenderCopy(rend_ptr, chess_textures->black_pieces[ROOK_TEXT_N], NULL,&draw_rect);
					break;
				case 'n':
					SDL_RenderCopy(rend_ptr, chess_textures->black_pieces[KNIGHT_TEXT_N], NULL, &draw_rect);
					break;
				case 'b':
					SDL_RenderCopy(rend_ptr, chess_textures->black_pieces[BISHOP_TEXT_N], NULL, &draw_rect);
					break;
				case 'q':
					SDL_RenderCopy(rend_ptr, chess_textures->black_pieces[QUEEN_TEXT_N], NULL, &draw_rect);
					break;
				case 'k':
					SDL_RenderCopy(rend_ptr, chess_textures->black_pieces[KING_TEXT_N], NULL, &draw_rect);
					break;
				case '.':
					//fallthrough
				default:
					break;
			}
		}
	}

	//render the numbers	
	draw_rect.x = 0;
	draw_rect.y = SQUARE_W_H * (ROWS - 1) + CHESS_SCREEN_START_Y + CHESS_SCREEN_START_Y/2 - 2;
	draw_rect.w = SIGN_W_H;
	draw_rect.h = SIGN_W_H;

	if(turn == TURN_WHITE)
	{
		for(i = 1; i <= ROWS; i++, draw_rect.y -= SQUARE_W_H)
		{
			SDL_RenderCopy(rend_ptr, chess_textures->number_textures[i], NULL, &draw_rect);
		}
	}
	else //TURN_BLACK
	{
		for(i = 1; i <= ROWS; i++, draw_rect.y -= SQUARE_W_H)
		{
			SDL_RenderCopy(rend_ptr, chess_textures->number_textures[ROWS + 1 - i], NULL, &draw_rect);
		}
	}
	
	//render the letters
	draw_rect.x = CHESS_SCREEN_START_X + CHESS_SCREEN_START_X / 2;
	draw_rect.y = CHESS_SCREEN_START_Y + SQUARE_W_H * ROWS;
	draw_rect.w = SIGN_W_H;
	draw_rect.h = SIGN_W_H;

	if(turn == TURN_WHITE)
	{
		for(i = 0; i < COLS; i++, draw_rect.x += SQUARE_W_H)
		{
			SDL_RenderCopy(rend_ptr, chess_textures->letter_textures[i], NULL, &draw_rect);
		}
	}
	else //TURN_BLACK
	{
		for(i = 0; i < COLS; i++, draw_rect.x += SQUARE_W_H)
		{
			SDL_RenderCopy(rend_ptr, chess_textures->letter_textures[COLS - 1 - i], NULL, &draw_rect);
		}
	}
	
	//render indicator
	if(indicators->visible_help == 1)
	{
		if(turn == TURN_WHITE)
		{
			draw_rect.x = CHESS_SCREEN_START_X + indicators->help_x * SQUARE_W_H;
			draw_rect.y = CHESS_SCREEN_START_Y + (7 - indicators->help_y) * SQUARE_W_H;
		}
		else //TURN_BLACK
		{
			draw_rect.x = CHESS_SCREEN_START_X + (7 - indicators->help_x) * SQUARE_W_H;
			draw_rect.y = CHESS_SCREEN_START_Y + indicators->help_y * SQUARE_W_H;
		}
		draw_rect.w = SQUARE_W_H;
		draw_rect.h = SQUARE_W_H;
		SDL_RenderCopy(rend_ptr, chess_textures->select_mark_help, NULL, &draw_rect);
	}
	if(indicators->visible_select_begin == 1)
	{
		draw_rect.x = CHESS_SCREEN_START_X + indicators->select_begin_x * SQUARE_W_H;
		draw_rect.y = CHESS_SCREEN_START_Y + (7 - indicators->select_begin_y) * SQUARE_W_H;
		draw_rect.w = SQUARE_W_H;
		draw_rect.h = SQUARE_W_H;
		SDL_RenderCopy(rend_ptr, chess_textures->select_mark_begin, NULL, &draw_rect);
	}
	if(indicators->visible_select_end == 1)
	{
		draw_rect.x = CHESS_SCREEN_START_X + indicators->select_end_x * SQUARE_W_H;
		draw_rect.y = CHESS_SCREEN_START_Y + (7 - indicators->select_end_y) * SQUARE_W_H;
		draw_rect.w = SQUARE_W_H;
		draw_rect.h = SQUARE_W_H;
		SDL_RenderCopy(rend_ptr, chess_textures->select_mark_end, NULL, &draw_rect);
	}
}

/*
* Inits all the textures.
*/
void init_textures_and_squares(SDL_Renderer *rend_ptr, struct chess_textures_struct *chess_textures, chess_square_t *squares)
{
	chess_textures->board_texture = init_squares_and_board(rend_ptr, squares, 0xC0C0C0FF, 0x808080FF, 0xA0A0A0FF);
	chess_textures->utility_bg_texture = init_utility_bg_texture(rend_ptr, 0x606060FF);
	init_piece_textures(rend_ptr, chess_textures->white_pieces, chess_textures->black_pieces, 0xFFFFFFFF, 0x000000FF);
	init_number_textures(rend_ptr, chess_textures->number_textures, 0xFFFFFFFF);
	init_letter_textures(rend_ptr, chess_textures->letter_textures, 0xFFFFFFFF);
	chess_textures->dot = init_dot_texture(rend_ptr, 0xFFFFFFFF);
	chess_textures->dash = init_dash_texture(rend_ptr, 0xFFFFFFFF);
	chess_textures->white_turn_indicator = init_turn_indicator(rend_ptr, 0xFFFFFFFF);
	chess_textures->black_turn_indicator = init_turn_indicator(rend_ptr, 0x000000FF);
	chess_textures->mainmenu_bg_texture = init_mainmenu_bg_texture(rend_ptr, 0x909090FF);
	chess_textures->select_mark_help = init_select_mark(rend_ptr, 0x3333337F);
	chess_textures->select_mark_begin = init_select_mark(rend_ptr, 0x00ff007F);
	chess_textures->select_mark_end = init_select_mark(rend_ptr, 0xff00007F);
}

/*
* Frees all the textures.
*/
void free_textures(struct chess_textures_struct *chess_textures)
{
	int i;
	SDL_DestroyTexture(chess_textures->board_texture);
	SDL_DestroyTexture(chess_textures->utility_bg_texture);
	SDL_DestroyTexture(chess_textures->white_turn_indicator);
	SDL_DestroyTexture(chess_textures->black_turn_indicator);
	SDL_DestroyTexture(chess_textures->mainmenu_bg_texture);
	SDL_DestroyTexture(chess_textures->dot);
	SDL_DestroyTexture(chess_textures->dash);
	SDL_DestroyTexture(chess_textures->select_mark_help);
	SDL_DestroyTexture(chess_textures->select_mark_begin);
	SDL_DestroyTexture(chess_textures->select_mark_end);
	for(i = 0; i < PIECES_TEXTURES_N; i++)
	{
		SDL_DestroyTexture(chess_textures->white_pieces[i]);
		SDL_DestroyTexture(chess_textures->black_pieces[i]);
	}
	for(i = 0; i < NUMBER_TEXTURES_N; i++)
	{
		SDL_DestroyTexture(chess_textures->number_textures[i]);
	}
	for(i = 0; i < LETTER_TEXTURES_N; i++)
	{
		SDL_DestroyTexture(chess_textures->letter_textures[i]);
	}
}

/*
* Inits SDL2, the window and the renderer.
*/
int init_window_and_renderer(SDL_Renderer **rend_ptr, SDL_Window **win_ptr, int window_w, int window_h)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL_Init error\n");
		return 0;
	}
	
	*win_ptr = SDL_CreateWindow("Shakki", 50, 50, window_w, window_h, 0);
	
	if(*win_ptr == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow error\n");
		return 0;
	}
	
	*rend_ptr = SDL_CreateRenderer(*win_ptr, -1, SDL_RENDERER_ACCELERATED);
	
	if(*rend_ptr == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer error\n");
		return 0;
	}
	return 1;
}