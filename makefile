CC = gcc
CFLAGS = -mwindows -Wall -lmingw32 -lSDL2main -lSDL2
SRC_FILES = game_main.c pgn_pieces_decoder.c puzzle_library.c chess_textures_and_draw.c random_gen.c
OUTPUT_NAME = chess_puzzle_program.exe

all:
	$(CC) $(SRC_FILES) $(CFLAGS) -o $(OUTPUT_NAME)
	