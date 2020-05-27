#ifndef TRAP_H
#define TRAP_H

#include <iostream>

#include "console.h"


class Trap
{
private:
	int position_x;
	int position_y;
public:
	void set_position_x(int);
	int get_position_x();
	void set_position_y(int);
	int get_position_y();
	void spawn();
};

#endif //TRAP_H