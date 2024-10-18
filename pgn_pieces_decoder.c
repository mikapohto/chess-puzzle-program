#include "pgn_pieces_decoder.h"

/*
* decode pgn for some steps.
* returns the new board in the board argument
* IN:	const char *pgn
*			in pgn format with spaces, without turn numbers and without #/+.
*			pgn must end in a space
* returns the index of pgn char array where the program were stopped.
* returns 0 if the puzzle is over.
*/
int decode_pgn(char board[8][9], const char *pgn, int pgn_i, int steps, turn_t *turn)
{
	int step_counter;
	for(step_counter = 0; pgn[pgn_i] != 0 && step_counter < steps; step_counter++)
	{
		pgn_i = decode_pgn_step(board, pgn, pgn_i, *turn);
		if(*turn == TURN_WHITE)
		{
			*turn = TURN_BLACK;
		}
		else
		{
			*turn = TURN_WHITE;
		}
		if(pgn_i < 1)
		{
			return 0;
		}
	}
	if(pgn[pgn_i] == 0)
	{
		return 0;
	}
	return pgn_i;
}

/*
* decode pgn for 1 step.
* updates the new board in the board argument
* IN:	const char *pgn
*			in pgn format with spaces, without turn numbers and without #/+.
*			pgn must end in a space
*		int i
*			the index of pgn
* OUT: returns one of the following:
*			updated i 		(i > 0)
*			end of the game (i == 0)
*			error			(i < 0)
*/
int decode_pgn_step(char board[8][9], const char *pgn, int i, turn_t turn)
{
	int re;
	switch(pgn[i])
	{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
			re = pgn_pawn(board, pgn, i-1, turn);
			re--;
			break;
		case 'R':
			re = pgn_rook(board, pgn, i, turn);
			break;
		case 'N':
			re = pgn_knight(board, pgn, i, turn);
			break;
		case 'B':
			re = pgn_bishop(board, pgn, i, turn);
			break;
		case 'Q':
			re = pgn_queen(board, pgn, i, turn);
			break;
		case 'K':
			re = pgn_king(board, pgn, i, turn);
			break;
		case 'O':
			re = pgn_castle(board, pgn, i, turn);
			break;
		case '1': //PASSTHROUGH
		case '0': //Lose
		case 'D': //halfhalf
			return 0;
		default:
			return -1;
	}
	if(re < 0)
	{
		return -1;
	}
	i += re + 1; //skip the space or dot
	return i;
}

/*
* checks if the path between two pieces is free.
* works diagonally, horizontally and vertically.
* other kind of inputs return 0.
* returns 0 if not free, 1 if free
*/
int is_free_path(char board[8][9], int srow, int scol, int erow, int ecol)
{
	int i;
	int smaller, larger;
	if(srow == erow)		//horizontal
	{
		if(scol < ecol)
		{
			smaller = scol;
			larger = ecol;
		}
		else //scol > ecol
		{
			smaller = ecol;
			larger = scol;
		}
		for(i = smaller + 1; i < larger; i++)
		{
			if(board[srow][i] != '.')
			{
				return 0;
			}
		}
	}
	else if(scol == ecol)	//vertically
	{
		if(srow < erow)
		{
			smaller = srow;
			larger = erow;
		}
		else //srow > erow
		{
			smaller = erow;
			larger = srow;
		}
		for(i = smaller + 1; i < larger; i++)
		{
			if(board[i][scol] != '.')
			{
				return 0;
			}
		}
	}
	else					//diagonally
	{
		//four different combinations possible
		if(erow < srow && ecol < scol)
		{
			for(i = 1; i < (scol - ecol); i++)
			{
				if(board[erow + i][ecol + i] != '.')
				{
					return 0;
				}
			}
		}
		else if(erow < srow && ecol > scol)
		{
			for(i = 1; i < (srow - erow); i++)
			{
				if(board[erow + i][ecol - i] != '.')
				{
					return 0;
				}
			}
		}
		else if(erow > srow && ecol > scol)
		{
			for(i = 1; i < (erow - srow); i++)
			{
				if(board[erow - i][ecol - i] != '.')
				{
					return 0;
				}
			}
		}
		else if(erow > srow && ecol < scol)
		{
			for(i = 1; i < (erow - srow); i++)
			{
				if(board[erow - i][ecol + i] != '.')
				{
					return 0;
				}
			}
		}
		else
		{
			//incorrect
			return 0;
		}
	}
	return 1;
}

/*
* modifies board[][] according to the pawn move
* returns the number of used regex, e.g. number until beginning of next move
* regex: P(€|Cx)CR
* returns 0 if not free, 1 if free
*/
int pgn_pawn(char board[8][9], const char *pgn, int i, turn_t turn)
{
	int ecol, erow, scol, srow;
	int re, promote_pgn;
	char pawn = 'P' + turn * ('a' - 'A'); // 'P' if white, 'p' if black;
	
	//divided in 2 cases: pawn eats or doesn't eat.
	//The starting location of the pawn depends on whose turn is it.
	if(pgn[i + 2] == 'x')	//the pawn is eating
	{
		ecol = pgn[i + 3] - 'a';
		erow = pgn[i + 4] - '1';
		promote_pgn = i + 5;
		if(turn == TURN_WHITE)
		{
			srow = erow - 1;
		}
		else //TURN_BLACK
		{
			srow = erow + 1;
		}
		if(board[erow][ecol] == '.') //en passant because eating an empty square
		{
			if(turn == TURN_WHITE)
			{
				board[erow - 1][ecol] = '.';
			}
			else //TURN_BLACK
			{
				board[erow + 1][ecol] = '.';
			}
		}
		scol = pgn[i + 1] - 'a';
		re = 5;
	}
	else	//the pawn is not eating
	{
		ecol = pgn[i + 1] - 'a';
		erow = pgn[i + 2] - '1';
		scol = ecol;
		promote_pgn = i + 3;
		if(turn == TURN_WHITE)
		{
			if(board[erow - 1][ecol] == '.') // double move
			{
				srow = erow - 2;
			}
			else // single move
			{
				srow = erow - 1;
			}
		}
		else //TURN_BLACK
		{
			if(board[erow + 1][ecol] == '.') // double move
			{
				srow = erow + 2;
			}
			else // single move
			{
				srow = erow + 1;
			}
		}
		re = 3;
	}
	if(pgn[promote_pgn] == '=')
	{
		//promote the pawn
		pawn = pgn[promote_pgn + 1] + turn * ('a' - 'A');
		re += 2;
	}
	board[srow][scol] = '.';
	board[erow][ecol] = pawn;
	return re;
}

/*
* modifies board[][] according to the rook move
* returns the number of used regex, e.g. number until beginning of next move
* regex: R(€|C)(€|R)(€|x)CR
* returns 0 if not free, 1 if free
*/
int pgn_rook(char board[8][9], const char *pgn, int i, turn_t turn)
{
	int ecol, erow, scol, srow;
	int j, re;
	char rook = 'R' + turn * ('a' - 'A'); // 'R' if white, 'r' if black
	
	//go to the next dot
	for(j = i; pgn[j] != ' ' && pgn[j] != '.' && pgn[j] != 0; j++)
	{
		//do nothing
	}
	j--;
	erow = pgn[j--] - '1';
	ecol = pgn[j--] - 'a';
	re = 0;
	if(pgn[j] == 'x') //skip the 'x'
	{
		re++;
		j--;
	}
	//there's 3 possible regex types left: CR, C|R, €
	switch(j - i)
	{
		case 0:
			//find the original rook from the same column or row
			for(j = 1; j < 8; j++)
			{
				if((erow + j < 8) && (board[erow + j][ecol] == rook))
				{
					srow = erow + j;
					scol = ecol;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((ecol + j < 8) && (board[erow][ecol + j] == rook))
				{
					srow = erow;
					scol = ecol + j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((erow - j > -1) && (board[erow - j][ecol] == rook))
				{
					srow = erow - j;
					scol = ecol;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((ecol - j > -1) && (board[erow][ecol - j] == rook))
				{
					srow = erow;
					scol = ecol - j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
			}
			re += 3;
			break;
		case 1:
			//check if the pgn[i + 1] is a number or column, then find the rook
			if((pgn[i + 1] - 'a') < 0 || (pgn[i + 1] - 'a') > 7)
			{
				//if true, then pgn[i + 1] is a number aka row
				srow = pgn[i + 1] - '1';
				if(srow == erow)
				{
					for(j = 0; j < 8; j++)
					{
						if(board[srow][j] == rook)
						{
							scol = j;
							if(is_free_path(board, srow, scol, erow, ecol))
							{
								break;
							}
						}
					}
				}
				else
				{
					scol = ecol;
				}
			}
			else //column
			{
				scol = pgn[i + 1] - 'a';
				if(scol == ecol)
				{
					for(j = 0; j < 8; j++)
					{
						if(board[j][scol] == rook)
						{
							srow = j;
							if(is_free_path(board, srow, scol, erow, ecol))
							{
								break;
							}
						}
					}
				}
				else
				{
					srow = erow;
				}
			}
			re += 4;
			break;
		case 2:
			scol = pgn[i + 1] - 'a';
			srow = pgn[i + 2] - '1';
			re += 5;
			break;
		default:
			return -1;
	}
	
	board[srow][scol] = '.';
	board[erow][ecol] = rook;
	return re;
}

/*
* modifies board[][] according to the knight move
* returns the number of used regex, e.g. number until beginning of next move
* regex: N(€|C)(€|R)(€|x)CR
* returns 0 if not free, 1 if free
*/
int pgn_knight(char board[8][9], const char *pgn, int i, turn_t turn)
{
	int ecol, erow, scol, srow;
	int j, re;
	char knight	= 'N' + turn * ('a' - 'A'); // 'N' if white, 'n' if black
	int knight_path[8][2] = {{2,1}, {1,2}, {-1,2}, {-2,1},
							{-2,-1}, {-1,-2}, {1,-2}, {2,-1}};

	for(j = i; pgn[j] != ' ' && pgn[j] != '.' && pgn[j] != 0; j++) //go to the next space
	{
		//do nothing
	}
	j--;
	erow = pgn[j--] - '1';
	ecol = pgn[j--] - 'a';
	re = 0;
	if(pgn[j] == 'x') //skip the 'x'
	{
		re++;
		j--;
	}
	//there's 3 possible regex types left: CR, C|R, €
	switch(j - i)
	{
		case 0:
			for(j = 0; j < 8; j++)
			{
				//check if any of the cell contains a knight
				if(erow + knight_path[j][0] < 0 || erow + knight_path[j][0] > 7 ||
					ecol + knight_path[j][1] < 0 || ecol + knight_path[j][1] > 7)
				{
					// outside of the board
					continue;
				}
				//inside of the board
				if(board[erow + knight_path[j][0]][ecol + knight_path[j][1]] == knight)
				{
					srow = erow + knight_path[j][0];
					scol = ecol + knight_path[j][1];
				}
			}
			re += 3;
			break;
		case 1:
			//check if the pgn[i + 1] is a number or column, then find the knight
			if((pgn[i + 1] - 'a') < 0 || (pgn[i + 1] - 'a') > 7)
			{
				//if true, then pgn[i + 1] is a number aka row
				srow = pgn[i + 1] - '1';
				for(j = 0; j < 8; j++)
				{
					if(erow + knight_path[j][0] != srow)
					{
						//skip if the starting row isn't what it is supposed to be
						continue;
					}
					//check if any of the cell contains a knight
					if(erow + knight_path[j][0] < 0 || erow + knight_path[j][0] > 7 ||
						ecol + knight_path[j][1] < 0 || ecol + knight_path[j][1] > 7)
					{
						// outside of the board
						continue;
					}
					//inside of the board
					if(board[erow + knight_path[j][0]][ecol + knight_path[j][1]] == knight)
					{
						scol = ecol + knight_path[j][1];
					}
				}
			}
			else //column
			{
				scol = pgn[i + 1] - 'a';
				for(j = 0; j < 8; j++)
				{
					if(ecol + knight_path[j][1] != scol)
					{
						//skip if the starting row isn't what it is supposed to be
						continue;
					}
					//check if any of the cell contains a knight
					if(erow + knight_path[j][0] < 0 || erow + knight_path[j][0] > 7 ||
						ecol + knight_path[j][1] < 0 || ecol + knight_path[j][1] > 7)
					{
						// outside of the board
						continue;
					}
					//inside of the board
					if(board[erow + knight_path[j][0]][ecol + knight_path[j][1]] == knight)
					{
						srow = erow + knight_path[j][0];
					}
				}
			}
			re += 4;
			break;
		case 2:
			scol = pgn[i + 1] - 'a';
			srow = pgn[i + 2] - '1';
			re += 5;
			break;
		default:
			return -1;
	}
	board[srow][scol] = '.';
	board[erow][ecol] = knight;
	return re;
}

/*
* modifies board[][] according to the bishop move
* returns the number of used regex, e.g. number until beginning of next move
* regex: B(€|C)(€|R)(€|x)CR
* returns 0 if not free, 1 if free
*/
int pgn_bishop(char board[8][9], const char *pgn, int i, turn_t turn)
{
	int ecol, erow, scol, srow;
	int j, re, diff;
	char bishop	= 'B' + turn * ('a' - 'A'); // 'B' if white, 'b' if black

	for(j = i; pgn[j] != ' ' && pgn[j] != '.' && pgn[j] != 0; j++) //go to the next space
	{
		//do nothing
	}
	j--;
	erow = pgn[j--] - '1';
	ecol = pgn[j--] - 'a';
	re = 0;
	if(pgn[j] == 'x') //skip the 'x'
	{
		re++;
		j--;
	}
	//there's 3 possible regex types left: CR, C|R, €
	switch(j - i)
	{
		case 0:
			//check (1,1), then (-1,1), (-1,-1), (1,-1)
			for(j = 1; j < 8; j++)
			{
				//check if inside the board and then for bishop
				if((erow + j < 8 && ecol + j < 8) &&
					(board[erow + j][ecol + j] == bishop))
				{
					srow = erow + j;
					scol = ecol + j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((erow + j < 8 && ecol - j > -1) &&
					(board[erow + j][ecol - j] == bishop))
				{
					srow = erow + j;
					scol = ecol - j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((erow - j > -1 && ecol - j > -1) &&
					(board[erow - j][ecol - j] == bishop))
				{
					srow = erow - j;
					scol = ecol - j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((erow - j > -1 && ecol + j < 8) &&
					(board[erow - j][ecol + j] == bishop))
				{
					srow = erow - j;
					scol = ecol + j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
			}
			re += 3;
			break;
		case 1:
			//need to check only 2 squares
			//check if the pgn[i + 1] is a number or column, then find the bishop
			if((pgn[i + 1] - 'a') < 0 || (pgn[i + 1] - 'a') > 7)
			{
				//if true, then pgn[i + 1] is a number aka row
				srow = pgn[i + 1] - '1';
				diff = srow - erow; //the sign doesn't matter
				if(board[srow][ecol - diff] == bishop && is_free_path(board, srow, ecol - diff, erow, ecol))
				{
					scol = ecol - diff;
				}
				else
				{
					scol = ecol + diff;
				}
			}
			else //column
			{
				scol = pgn[i + 1] - 'a';
				diff = scol - ecol; //the sign doesn't matter
				if(board[erow - diff][scol] == bishop && is_free_path(board, erow - diff, scol, erow, ecol))
				{
					srow = erow - diff;
				}
				else
				{
					srow = erow + diff;
				}
			}
			re += 4;
			break;
		case 2:
			scol = pgn[i + 1] - 'a';
			srow = pgn[i + 2] - '1';
			re += 5;
			break;
		default:
			return -1;
	}
	board[srow][scol] = '.';
	board[erow][ecol] = bishop;
	return re;
}

/*
* modifies board[][] according to the bishop move
* returns the number of used regex, e.g. number until beginning of next move
* regex: Q(€|C)(€|R)(€|x)CR
* returns 0 if not free, 1 if free
*/
int pgn_queen(char board[8][9], const char *pgn, int i, turn_t turn)
{
	int ecol, erow, scol, srow;
	int j, re, diff;
	char queen = 'Q' + turn * ('a' - 'A'); // 'Q' if white, 'q' if black

	for(j = i; pgn[j] != ' ' && pgn[j] != '.' && pgn[j] != 0; j++) //go to the next space
	{
		//do nothing
	}
	j--;
	erow = pgn[j--] - '1';
	ecol = pgn[j--] - 'a';
	re = 0;
	if(pgn[j] == 'x') //skip the 'x'
	{
		re++;
		j--;
	}
	//there's 3 possible regex types left: CR, C|R, €
	switch(j - i)
	{
		case 0:
			//check (1,1), then (-1,1), (-1,-1), (1,-1),
			//	then (1,0), (0,1), (-1,0), (0,-1)
			for(j = 1; j < 8; j++)
			{
				//check if inside a board and then for the queen
				//check (1,1), (-1,1), (-1,-1), (1,-1)
				if((erow + j < 8 && ecol + j < 8) &&
					(board[erow + j][ecol + j] == queen))
				{
					srow = erow + j;
					scol = ecol + j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((erow + j < 8 && ecol - j > -1) &&
					(board[erow + j][ecol - j] == queen))
				{
					srow = erow + j;
					scol = ecol - j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((erow - j > -1 && ecol - j > -1) &&
					(board[erow - j][ecol - j] == queen))
				{
					srow = erow - j;
					scol = ecol - j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((erow - j > -1 && ecol + j < 8) &&
					(board[erow - j][ecol + j] == queen))
				{
					srow = erow - j;
					scol = ecol + j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				// check (1,0), (0,1), (-1,0), (0,-1)
				if((erow + j < 8) && (board[erow + j][ecol] == queen))
				{
					srow = erow + j;
					scol = ecol;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((ecol + j < 8) && (board[erow][ecol + j] == queen))
				{
					srow = erow;
					scol = ecol + j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((erow - j > -1) && (board[erow - j][ecol] == queen))
				{
					srow = erow - j;
					scol = ecol;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
				if((ecol - j > -1) && (board[erow][ecol - j] == queen))
				{
					srow = erow;
					scol = ecol - j;
					if(is_free_path(board, srow, scol, erow, ecol))
					{
						break;
					}
				}
			}
			re += 3;
			break;
		case 1:
			//need to check only 3 squares
			//check if the pgn[i + 1] is a number or column, then find the queen
			if((pgn[i + 1] - 'a') < 0 || (pgn[i + 1] - 'a') > 7)
			{
				//if true, then pgn[i + 1] is a number aka row
				srow = pgn[i + 1] - '1';
				diff = srow - erow; //the sign doesn't matter
				if(board[srow][ecol - diff] == queen && is_free_path(board, srow, ecol - diff, erow, ecol))
				{
					scol = ecol - diff;
				}
				else if(board[srow][ecol + diff] == queen && is_free_path(board, srow, ecol + diff, erow, ecol))
				{
					scol = ecol + diff;
				}
				else
				{
					scol = ecol;
				}
			}
			else //column
			{
				scol = pgn[i + 1] - 'a';
				diff = scol - ecol; //the sign doesn't matter
				if(board[erow - diff][scol] == queen && is_free_path(board, erow - diff, scol, erow, ecol))
				{
					srow = erow - diff;
				}
				else if(board[erow + diff][scol] == queen && is_free_path(board, erow + diff, scol, erow, ecol))
				{
					srow = erow + diff;
				}
				else
				{
					srow = erow;
				}
			}
			re += 4;
			break;
		case 2:
			scol = pgn[i + 1] - 'a';
			srow = pgn[i + 2] - '1';
			re += 5;
			break;
		default:
			return -1;
	}
	board[srow][scol] = '.';
	board[erow][ecol] = queen;
	return re;
}

/*
* modifies board[][] according to the king move
* returns the number of used regex, e.g. number until beginning of next move
* regex: K(€|C)(€|R)(€|x)CR
* returns 0 if not free, 1 if free
*/
int pgn_king(char board[8][9], const char *pgn, int i, turn_t turn)
{
	int ecol, erow, scol, srow;
	int re, j;
	char king = 'K' + turn * ('a' - 'A'); // 'K' if white, 'k' if black
	int king_path[8][2] = {{1,0}, {1,1}, {0,1}, {-1,1},
							{-1,0}, {-1,-1}, {0,-1}, {1,-1}};
	
	re = 3;
	
	if(pgn[i + 1] == 'x')
	{
		re++;
		i++;
	}
	ecol = pgn[i + 1] - 'a';
	erow = pgn[i + 2] - '1';
	
	for(j = 0; j < 8; j++)
	{
		if(erow + king_path[j][0] < 0 || erow + king_path[j][0] > 8 ||
			ecol + king_path[j][1] < 0 || ecol + king_path[j][1] > 8)
		{
			//outside of the board
			continue;
		}
		if(board[erow + king_path[j][0]][ecol + king_path[j][1]] == king)
		{
			srow = erow + king_path[j][0];
			scol = ecol + king_path[j][1];
			break;
		}
	}
	board[srow][scol] = '.';
	board[erow][ecol] = king;
	return re;
}

/*
* modifies board[][] according to the castle move
* returns the number of used regex, e.g. number until beginning of next move.
* returns 0 if not free, 1 if free
*/
int pgn_castle(char board[8][9], const char *pgn, int i, turn_t turn)
{
	char king = 'K' + turn * ('a' - 'A'); // 'K' if white, 'k' if black;
	char rook = 'R' + turn * ('a' - 'A'); // 'R' if white, 'r' if black;
	int row = turn * 7; //0 if white, 7 if black
	int re;
	if(pgn[i+3] == '-') //long castle
	{
		board[row][4] = '.';
		board[row][0] = '.';
		board[row][2] = king;
		board[row][3] = rook;
		re = 5;
	}
	else //short castle
	{
		board[row][4] = '.';
		board[row][7] = '.';
		board[row][6] = king;
		board[row][5] = rook;
		re = 3;
	}
	return re;
}