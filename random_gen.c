#include "random_gen.h"

static void automaton_step(void);

static int cells = 0;

/*
* Init the automaton.
*/
void init_random_gen(uint_type32 seed)
{
	int i;
	cells = 0x80000000;
	for(i = 0; i < seed; i++)
	{
		automaton_step();
	}
}

/*
* Return 32-bit random number.
*/
uint_type32 random_32_bit(void)
{
	uint_type32 n;
	int i;
	
	n = 0;
	for(i = 0; i < 32; i++)
	{
		n = (n << 1) | (cells & 1);
		automaton_step();
	}
	return n;
}

/*
* Calculates the next state of the cells.
*/
static void automaton_step(void)
{
	int a, c;
	
	if((cells & 0x1) != 0)
	{
		a = (cells >> 1) | 0x80000000;
	}
	else
	{
		a = cells >> 1;
	}
	if((cells & 0x80000000) != 0)
	{
		c = (cells << 1) | 0x00000001;
	}
	else
	{
		c = cells << 1;
	}
	
	cells = a ^ (cells | c);
}

/*
* Shuffles the pointers by using Fisher–Yates shuffle.
* Input:
*	list 	- array of pointers
*	n 		- length of the array of pointers
*/
void shuffle_pointers(void **list, int n)
{
	int i;
	uint32_t random_i;
	void *p_tmp;
	
	for(i = n - 1; i > 0; i--)
	{
		random_i = random_32_bit() % (i + 1); //random integer from [0,i]
		p_tmp = list[i];
		list[i] = list[random_i];
		list[random_i] = p_tmp;
	}
}