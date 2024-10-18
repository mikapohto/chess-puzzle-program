#include <stdio.h>
#include <stdlib.h>
#include "puzzle_library.h"
#include "pgn_pieces_decoder.h"

#define PUZZLE_TXT_LEN			16
#define DATA_FILE_TXT_LEN		10
#define FILE_NAME_X				8
#define MAX_FILE_NAME_LEN		80
#define FILE_NAME_BUFFER_LEN	100
#define MAX_PUZZLE_FILE_LEN		3000

static const char puzzle_txt[PUZZLE_TXT_LEN] = "/puzzle_000.txt";
static const char data_file_txt[DATA_FILE_TXT_LEN] = "/data.txt";

/*
* This version uses malloc
* the name must end in '\0'
* name len < MAX_FILE_NAME_LEN
*/
puzzle_library_t * load_puzzle_library(char *name)
{
	char c;
	unsigned int i, j;
	int file_name_i;
	int puzzle_file_len;
	FILE *file_ptr = NULL;
	char file_name[FILE_NAME_BUFFER_LEN] = "./";
	puzzle_library_t *puzzle_library_ptr = NULL;
	puzzle_t **puzzle_array_ptr = NULL;
	
	//copy name[:] to file_name[2:]. file_name[0:2] = "./"
	for(file_name_i = 2; name[file_name_i - 2] != 0 && file_name_i < MAX_FILE_NAME_LEN + 2; file_name_i++)
	{
		file_name[file_name_i] = name[file_name_i - 2];
	}
	
	//check if name is too long
	if(file_name_i >= MAX_FILE_NAME_LEN + 2)
	{
		fprintf(stderr, "load_puzzle_library error: puzzle name too long\n");
		return NULL;
	}
	
	//allocate memory for the library struct and the library name
	puzzle_library_ptr = (puzzle_library_t *)malloc(sizeof(puzzle_library_t) * 1);
	if(puzzle_library_ptr == NULL)
	{
		return NULL;
	}
	puzzle_library_ptr->name = (char *)malloc(sizeof(char) * MAX_FILE_NAME_LEN);
	if(puzzle_library_ptr->name == NULL)
	{
		fprintf(stderr, "ERROR puzzle_library_ptr->name malloc fail\n");
		free((void *)puzzle_library_ptr);
	}
	
	//copy the name to the puzzle_lib name buffer
	for(i = 0; i < MAX_FILE_NAME_LEN; i++)
	{
		puzzle_library_ptr->name[i] = name[i];
	}

	//now file_name[] = "./name", add "/data.txt"
	//and turn it to file_name[] = "./name/data.txt"
	for(i = 0; i < DATA_FILE_TXT_LEN; i++, file_name_i++)
	{
		file_name[file_name_i] = data_file_txt[i];
	}
	
	file_name_i -= i; //make file_name_i "point" to the end of the "./name/"
	
	//read the data.txt to puzzle_library_ptr
	file_ptr = fopen(file_name, "r");
	if(file_ptr == NULL)
	{
		fprintf(stderr, "Error load_puzzle_library open %s\n", file_name);
		free((void *)puzzle_library_ptr->name);
		free((void *)puzzle_library_ptr);
		return NULL;
	}
	
	//the data is stored this way: "num_of_puzzles;lowest_time;"
	//load num_of_puzzles
	puzzle_library_ptr->num_of_puzzles = 0;
	for(i = 0; (c = fgetc(file_ptr)) != ';' && c != EOF; i++)
	{
		if(!(c >= '0' && c <= '9'))
		{
			break;
		}
		puzzle_library_ptr->num_of_puzzles *= 10;
		puzzle_library_ptr->num_of_puzzles += c - '0';
	}
		
	//load lowest_time
	puzzle_library_ptr->lowest_time = 0;
	for(i = 0; (c = fgetc(file_ptr)) != ';' && c != EOF; i++)
	{
		if(!(c >= '0' && c <= '9'))
		{
			break;
		}
		puzzle_library_ptr->lowest_time *= 10;
		puzzle_library_ptr->lowest_time += c - '0';
	}
	//done reading the data.txt
	fclose(file_ptr);
	
	//make the file_name[] = "./name/puzzle_000.txt"
	//currently file_name_i is pointing where the name of the puzzle is written
	for(i = 0; i < PUZZLE_TXT_LEN; i++, file_name_i++)
	{
		file_name[file_name_i] = puzzle_txt[i];
	}
	
	//make file_name_i to match where the numbers begin in the file_name
	file_name_i -= FILE_NAME_X;
	
	//allocate array[puzzle_library_ptr->num_of_puzzles] of pointers
	puzzle_array_ptr = (puzzle_t **)malloc(sizeof(puzzle_t *) * puzzle_library_ptr->num_of_puzzles);
	if(puzzle_array_ptr == NULL)
	{
		free((void *)puzzle_library_ptr->name);
		free((void *)puzzle_library_ptr);
		return NULL;
	}
	
	//open all the puzzle files and decode and save them
	for(i = 0; i < puzzle_library_ptr->num_of_puzzles ; i++)
	{
		file_name[file_name_i] = (i % 1000) / 100 + '0';
		file_name[file_name_i + 1] = (i % 100) / 10 + '0';
		file_name[file_name_i + 2] = (i % 10) + '0';
		file_ptr = fopen(file_name, "r");
		if(file_ptr == NULL)
		{
			break;
		}
		//check puzzle length
		fseek(file_ptr, 0, SEEK_END);
		puzzle_file_len = ftell(file_ptr);
		
		if(puzzle_file_len < 0 || puzzle_file_len > MAX_PUZZLE_FILE_LEN)
		{
			 //error, close the file and free the allocated memory
			fprintf(stderr, "ERROR, ftell() == %d\n", puzzle_file_len);
			for(j = 0; j < i; j++)
			{
				free((void *)puzzle_array_ptr[j]->puzzle_pgn);
				free((void *)puzzle_array_ptr[j]);
			}
			free((void *)puzzle_array_ptr);
			free((void *)puzzle_library_ptr->name);
			free((void *)puzzle_library_ptr);
			return NULL;
		}
		
		fseek(file_ptr, 0, SEEK_SET);
		
		//allocate memory
		puzzle_array_ptr[i] = malloc(sizeof(puzzle_t) * 1);
		if(puzzle_array_ptr[i] == NULL)
		{
			fprintf(stderr, "Malloc fail, puzzle_array_ptr[%d] == NULL\n", i);
			//free resources
			for(j = 0; j < i; j++)
			{
				free((void *)puzzle_array_ptr[j]->puzzle_pgn);
				free((void *)puzzle_array_ptr[j]);
			}
			free((void *)puzzle_array_ptr);
			free((void *)puzzle_library_ptr->name);
			free((void *)puzzle_library_ptr);
			return NULL;
		}
		puzzle_array_ptr[i]->puzzle_pgn = malloc(sizeof(char) * (puzzle_file_len + 1));
		if(puzzle_array_ptr[i]->puzzle_pgn == NULL)
		{
			fprintf(stderr, "Malloc fail, puzzle_array_ptr[%d]->puzzle_pgn == NULL\n", i);
			//free resources
			for(j = 0; j < i; j++)
			{
				free((void *)puzzle_array_ptr[j]->puzzle_pgn);
				free((void *)puzzle_array_ptr[j]);
			}
			free((void *)puzzle_array_ptr[i]);
			free((void *)puzzle_array_ptr);
			free((void *)puzzle_library_ptr->name);
			free((void *)puzzle_library_ptr);
			return NULL;
		}
		//copy file to puzzle_pgn
		for(j = 0; j < puzzle_file_len; j++)
		{
			puzzle_array_ptr[i]->puzzle_pgn[j] = fgetc(file_ptr);
		}
		puzzle_array_ptr[i]->puzzle_pgn[j++] = 0;
		if(set_puzzle(puzzle_array_ptr[i]->puzzle_pgn, &puzzle_array_ptr[i]->text_str, puzzle_array_ptr[i], puzzle_file_len) == 0)
		{
			//error
			//free resources
			for(j = 0; j < i + 1; j++)
			{
				free((void *)puzzle_array_ptr[j]->puzzle_pgn);
				free((void *)puzzle_array_ptr[j]);
			}
			free((void *)puzzle_array_ptr);
			free((void *)puzzle_library_ptr->name);
			free((void *)puzzle_library_ptr);
			return NULL;
		}

		//done reading
		fclose(file_ptr);
	}
	puzzle_library_ptr->puzzles = puzzle_array_ptr;
	return puzzle_library_ptr;
}

/*
* The first line of the file is telling where the puzzle begins and whose turn is it, e.g. 27b = turn 27 black
* The second line tells where it ends, e.g. 28b.
* the wanted *puzzle_pgn is of form [(Piece)](start_column)(start_square)(x)[end_column][end_row].
* so the removed characters are: white spaces, turn numbers, checks, mates
* in puzzle_t whites move and blacks move both count as one turn, e.g. 27b = 27 * 2 + 1 = 55 turns.
* returns 1 on success, 0 on error.
*/
int set_puzzle(char *puzzle_pgn, char **pointer_text, puzzle_t *puzzle, int puzzle_file_len)
{
	int i, j;
	int puzzle_pgn_i;
	int mod_pgn_i;
	int turn_n;
	char turn_str[10];
	
	//decode begin turn
	for(puzzle_pgn_i = 0, j = 0; puzzle_pgn_i < puzzle_file_len; puzzle_pgn_i++, j++)
	{
		if(puzzle_pgn[puzzle_pgn_i] == '\n' || puzzle_pgn[puzzle_pgn_i] == '\r' || puzzle_pgn[puzzle_pgn_i] == '\t' || puzzle_pgn[puzzle_pgn_i] == ' ') //white space
		{
			break;
		}
		turn_str[j] = puzzle_pgn[puzzle_pgn_i];
	}
	if(turn_str[j - 1] == 'b')
	{
		puzzle->puzzle_turn = TURN_BLACK;
		puzzle->begin = 1; //add +1 to begin turn because it's blacks turn
	}
	else if(turn_str[j - 1] == 'w')
	{
		puzzle->puzzle_turn = TURN_WHITE;
		puzzle->begin = 0;
	}
	else
	{
		fprintf(stderr, "modify_pgn: puzzle_turn not white nor black\n");
		return 0;
	}
	j -= 2;
	for(turn_n = 0, i = 1; j >= 0 ; j--, i *= 10)
	{
		if(turn_str[j] < '0' || turn_str[j] > '9')
		{
			break;
		}
		turn_n += (turn_str[j] - '0') * i;
	}
	puzzle->begin += turn_n * 2 - 2; //begin is set to 0 or 1 depending on whose turn is it, counting begins 1 in the txt file and 0 in the program
	
	//remove white space
	while(puzzle_pgn[puzzle_pgn_i] == '\n' || puzzle_pgn[puzzle_pgn_i] == '\r' || puzzle_pgn[puzzle_pgn_i] == '\t' || puzzle_pgn[puzzle_pgn_i] == ' ')
	{
		puzzle_pgn_i++;
	}
	
	//decode end turn
	for(j = 0; puzzle_pgn_i < puzzle_file_len; puzzle_pgn_i++, j++)
	{
		if(puzzle_pgn[puzzle_pgn_i] == '\n' || puzzle_pgn[puzzle_pgn_i] == '\r' || puzzle_pgn[puzzle_pgn_i] == '\t' || puzzle_pgn[puzzle_pgn_i] == ' ') //white space
		{
			break;
		}
		turn_str[j] = puzzle_pgn[puzzle_pgn_i];
	}
	if(turn_str[j - 1] == 'b')
	{
		puzzle->end = 1;
	}
	else if(turn_str[j - 1] == 'w')
	{
		puzzle->end = 0;
	}
	else
	{
		fprintf(stderr, "modify_pgn: puzzle not white nor black\n");
		return 0;
	}
	j -= 2;
	for(turn_n = 0, i = 1; j >= 0; j--, i *= 10)
	{
		if(turn_str[j] < '0' || turn_str[j] > '9')
		{
			break;
		}
		turn_n += (turn_str[j] - '0') * i;
	}
	puzzle->end += turn_n * 2 - 2; //end is set to 0 or 1 depending on whose turn is it
	
	//modify the pgn
	mod_pgn_i = 0;
	while(1)
	{
		//remove everything else except viable options
		while((puzzle_pgn[puzzle_pgn_i] >= '0' && puzzle_pgn[puzzle_pgn_i] <= '9') ||
				!((puzzle_pgn[puzzle_pgn_i] >= 'a' && puzzle_pgn[puzzle_pgn_i] <= 'z') || //remove everything else except viable optiuons
					(puzzle_pgn[puzzle_pgn_i] >= 'A' && puzzle_pgn[puzzle_pgn_i] <= 'Z') ||
					puzzle_pgn[puzzle_pgn_i] == '=' || puzzle_pgn[puzzle_pgn_i] == '-' ||
					puzzle_pgn[puzzle_pgn_i] == '*'))
		{
			puzzle_pgn_i++;
			//return if the pgn is ready
			if(puzzle_pgn_i > puzzle_file_len)
			{
				puzzle_pgn[mod_pgn_i++] = 0;
				*pointer_text = NULL;
				return 1;
			}
		}
		
		//optional text at the end of the file
		if(puzzle_pgn[puzzle_pgn_i] == '*')
		{
			puzzle_pgn_i++;
			puzzle_pgn[mod_pgn_i++] = 0;
			*pointer_text = puzzle_pgn + mod_pgn_i;
			while(puzzle_pgn_i < puzzle_file_len && puzzle_pgn[puzzle_pgn_i] != '*')
			{
				puzzle_pgn[mod_pgn_i++] = puzzle_pgn[puzzle_pgn_i++];
			}
			puzzle_pgn[mod_pgn_i++] = 0;
			return 1;
		}
		
		//now inside a real move
		while((puzzle_pgn[puzzle_pgn_i] >= '0' && puzzle_pgn[puzzle_pgn_i] <= '9') ||
				(puzzle_pgn[puzzle_pgn_i] >= 'a' && puzzle_pgn[puzzle_pgn_i] <= 'z') ||
				(puzzle_pgn[puzzle_pgn_i] >= 'A' && puzzle_pgn[puzzle_pgn_i] <= 'Z') ||
				puzzle_pgn[puzzle_pgn_i] == '=' || puzzle_pgn[puzzle_pgn_i] == '-')
		{
			puzzle_pgn[mod_pgn_i++] = puzzle_pgn[puzzle_pgn_i++];
		}
		//outside of the move
		//add a dot
		puzzle_pgn[mod_pgn_i++] = '.';
	}

	return 1; //doesn't get here
}

/*
* saves the puzzle_library to the data.txt
* return 1 on success, 0 on failure.
*/
int save_puzzle_library_t(puzzle_library_t *puzzle_library_ptr)
{
	char file_name[FILE_NAME_BUFFER_LEN] = "./";
	int file_name_i;
	int i;
	FILE *file_ptr;
	
	for(file_name_i = 2; puzzle_library_ptr->name[file_name_i - 2] != 0 && file_name_i < 83; file_name_i++)
	{
		file_name[file_name_i] = puzzle_library_ptr->name[file_name_i - 2];
	}
	
	for(i = 0; i < DATA_FILE_TXT_LEN; i++, file_name_i++)
	{
		file_name[file_name_i] = data_file_txt[i];
	}
	file_ptr = fopen(file_name, "w");
	if(file_ptr == NULL)
	{
		fprintf(stderr, "Error save_puzzle_time open %s\n", file_name);
		return 0;
	}
	fprintf(file_ptr, "%u;%u;", puzzle_library_ptr->num_of_puzzles, puzzle_library_ptr->lowest_time);
	fflush(file_ptr);
	fclose(file_ptr);
	return 1;
}

/*
* Frees the allocated resources in the puzzle_library_t + the library struct
*/
void free_puzzle_library(puzzle_library_t *puzzle_library_ptr)
{
	int i;
	for(i = 0; i < puzzle_library_ptr->num_of_puzzles; i++)
	{
		free((void *)puzzle_library_ptr->puzzles[i]->puzzle_pgn);
		free((void *)puzzle_library_ptr->puzzles[i]);
	}
	free((void *)puzzle_library_ptr->puzzles);
	free((void *)puzzle_library_ptr->name);
	free((void *)puzzle_library_ptr);
}