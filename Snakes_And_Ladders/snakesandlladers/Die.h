#ifndef DIE_H
#define DIE_H

#include <random>

class Die
{
private:
	//number of sides of die
	int sides;
	int rand_roll;
public:
	//default contructor
	Die();
	int roll();
	void set_sides(int);
	int get_sides();
};
#endif // !DIE_H