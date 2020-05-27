#include "Player.h"

//Default constructor sets initial position of a player to 1 and moves to 0
Player::Player()
{
	position = 1; //sets position to 1
	moves = 0;
}

//Sets name of the player
void Player::set_name(std::string name)
{
	player_name = name; //stores users input in a player_name variable
}

//Returns name of the player
std::string Player::get_name()
{
	return player_name;
}

//Sets position of the player
void Player::set_position(int new_position)
{
	position = new_position; //sets new position of the player
	moves++; //each time function is called moves variable is increased by 1
}

//Returns number of moves of the player
int Player::get_moves()
{
	return moves;
}

//Allows to access players score
int Player::get_position() 
{
	return position; //Returns position of the player
}