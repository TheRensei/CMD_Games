#include "Trap.h"

void Trap::set_position_x(int new_position_x)
{
	position_x = new_position_x;
}

int Trap::get_position_x()
{
	return position_x;
}

void Trap::set_position_y(int new_position_y)
{
	position_y = new_position_y;
}

int Trap::get_position_y()
{
	return position_y;
}

void Trap::spawn()
{
	Console::setCursorPosition(position_y, position_x);
	std::cout << 'X';
}