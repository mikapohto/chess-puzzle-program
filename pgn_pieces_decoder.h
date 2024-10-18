#ifndef PGN_PIECES_DECODER_H
#define PGN_PIECES_DECODER_H

/*
* The board consists of 8*8 characters + '\0' to end the string.
* The functions in this file change the board according to the pgn it is given
*	and the index of the current move in the pgn string.
* The moves are separated with a dot '.' in the pgn string.
*/

/*
* small = black
* big = white
* Rook 		- r
* Knight 	- n
* Bishop	- b
* Queen		- q
* King		- k
* Pawn		- p (epsilon €)
*/

typedef enum { TURN_WHITE = 0, TURN_BLACK = 1} turn_t;

int decode_pgn(char board[8][9], const char *pgn, int pgn_i, int steps, turn_t *turn);
int decode_pgn_step(char board[8][9], const char *pgn, int i, turn_t turn);
int is_free_path(char board[8][9], int srow, int scol, int erow, int ecol);
int pgn_pawn(char board[8][9], const char *pgn, int i, turn_t turn);
int pgn_rook(char board[8][9], const char *pgn, int i, turn_t turn);
int pgn_knight(char board[8][9], const char *pgn, int i, turn_t turn);
int pgn_bishop(char board[8][9], const char *pgn, int i, turn_t turn);
int pgn_queen(char board[8][9], const char *pgn, int i, turn_t turn);
int pgn_king(char board[8][9], const char *pgn, int i, turn_t turn);
int pgn_castle(char board[8][9], const char *pgn, int i, turn_t turn);

#endif //PGN_PIECES_DECODER_H