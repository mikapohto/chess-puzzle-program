The program is intented to be used as a woodpecker method for chess puzzles.
Import your own puzzles (ideally 100-200 puzzles) and try to solve them faster
than previously. The puzzles can contain a short amount of text which is
displayed on the screen. This can used to learn openings etc.
There are files you have to modify to add puzzles for the program:
	-menu_data.txt
		add the name of the new puzzle library between the semicolons. The file
		supports up to 8 puzzle libraries at the same time.
			e.g. puzzles1;puzzles2;;;;;;;
	-puzzle_name/data.txt
		This file tells how many puzzles exists and the lowest time to solve all
		the puzzles. The first number is the number of puzzles, the second
		number is the time.
		e.g. 20;321321;
	-puzzle_name/puzzle_xxx.txt
		This file contains the puzzle pgn, the puzzle starting turn and the end
		turn, and additionally text to be displayed on the screen.
		The first row contains the starting turn and the color e.g. 12w.
		The second row contains the ending turn and the color e.g. 14w.
		Next comes the pgn on multiple rows.
		Finally one can add addition text between two asterisks at the end of
		the file. e.g. *this is text*. Only lowercase letters are recognized.
There is a small library of puzzles included so one can use them as an example.
The sample puzzles are from https://lichess.org/training/themes .

The program can be used with a mouse or with a keyboard.

add SDL2.dll to the folder if you're having difficulties running the program.