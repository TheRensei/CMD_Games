#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include "console.h"
#include "Player.h"


class Board
{
private:

	//sets array (for ladders and snakes )size to 3
	static const int array_size = 3;

	//number of fields on the board
	int num;

	//width and length of the board
	int length;
	int width;
public:
	Board();

	//arrays that hold numbers for displaying where snakes and ladders are
	int snake_head[array_size];
	int snake_tail[array_size];
	int ladder_top[array_size];
	int ladder_bot[array_size];

	//creates two objects for two players of Player class
	//making them public allows use of functions of that class
	Player pl1;
	Player pl2;
	void print_board();
	void print_board_num();
	void change_colours();
	void create_players(std::string, std::string);
	void snakes();
	void ladders();
};

#endif //!BOARD_H