#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "console.h"

class Character
{
protected:
	int health;
	int position_x;
	int position_y;
	int prev_position_x;
	int prev_position_y;
public:
	void set_position_x(int);
	int get_position_x();
	void set_position_y(int);
	int get_position_y();
	void set_prev_position_x();
	int get_prev_position_x();
	void set_prev_position_y();
	int get_prev_position_y();
};

#endif //CHARACTER_H