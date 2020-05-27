#ifndef GAME_H
#define GAME _H
#include "Board.h"


class Game
{
private:
	Board game_board;
	int choice;
public:
	void set_settings();
	void play();
	void end();
};

#endif // !GAME_H