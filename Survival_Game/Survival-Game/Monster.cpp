#include "Monster.h"


void Monster::spawn()
{
	Console::setCursorPosition(prev_position_y, prev_position_x);
	std::cout << ' ';
	Console::setCursorPosition(position_y, position_x);
	std::cout << 'M';
}