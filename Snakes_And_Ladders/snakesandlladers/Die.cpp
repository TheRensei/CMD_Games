#include "Die.h"

//Sets number of sides to 6
Die::Die()
{
	sides = 6;
}
//simulates rolling a die by generating random number between 1 - 6
int Die::roll()
{
	rand_roll = rand() % sides + 1;
	return rand_roll;
}

//Sets sides of the die
void Die::set_sides(int count)
{
	sides = count;
}

//Returns sides of a die
int Die::get_sides()
{
	return sides;
}