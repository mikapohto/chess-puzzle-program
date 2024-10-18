#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H

#include <SDL2/SDL.h> //for Uint32
/*
* Simple circular cellular automata random generator based on rule 30 CA.
* Spatially periodic (circular) with a period of 32. Can easily be implemented
* 	to be larger but this is enough for the current program.
* The random bits are picked from the "middle" column of the automaton and the
*	random uint_type32 are composed of the middle column bits.
* More information can be found from https://en.wikipedia.org/wiki/Rule_30 and
* from S. Wolframs work "Random Sequence Generation by Cellular Automata".
*/

typedef Uint32 uint_type32;

void init_random_gen(uint_type32 seed);
uint_type32 random_32_bit(void);
void shuffle_pointers(void **list, int n);

#endif //RANDOM_GEN_H