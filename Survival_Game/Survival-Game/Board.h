#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <random>
#include <ctime>
#include "conio.h"
#include <iostream>
#include <string>

#include "Player.h"
#include "Monster.h"
#include "Trap.h"

class Board
{
private:
	int width;
	int height;
	int trap_count;
	int monster_count;
	std::vector<Trap> trap_vector;
	std::vector<Monster> monster_vector;
	int min;				//min random number for random position
	int rand_x;
	int rand_y;
	Player pl;
	int result; //0 win,  1 lose
public:
	Board();
	void prepare_board();
	void set_width(int);
	void set_height(int);
	void set_initial_positions();
	void create_board();
	int get_result();
	~Board();
};

#endif //BOARD_H