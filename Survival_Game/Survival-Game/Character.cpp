#include "Character.h"

//current position
void Character::set_position_x(int new_x)
{
	position_x = new_x;
}

int Character::get_position_x()
{
	return position_x;
}

void Character::set_position_y(int new_y)
{
	position_y = new_y;
}

int Character::get_position_y()
{
	return position_y;
}

//previous position
void Character::set_prev_position_x()
{
	prev_position_x = position_x;
}

int Character::get_prev_position_x()
{
	return prev_position_x;
}

void Character::set_prev_position_y()
{
	prev_position_y = position_y;
}

int Character::get_prev_position_y()
{
	return prev_position_y;
}