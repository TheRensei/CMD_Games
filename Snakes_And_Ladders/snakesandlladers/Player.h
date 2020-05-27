#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player
{
private:
	//Players name
	std::string player_name;

	//Players position on the board
	int position;

	//Variable which holds number of players moves until end of the game
	int moves;
public:
	//Default constructor
	Player();

	void set_name(std::string);
	std::string get_name();
	void set_position(int);
	int get_moves();
	int get_position();
};

#endif // !PLAYER_H