#ifndef GAME_H
#define GAME_H

#include <ctime> 
#include <random>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "console.h"
#include "Die.h"
#include "Board.h"
#include <Windows.h> //for sleep function
class Game
{
private:
	/*-----------------------------------------------------------
	pl1_die and pl2_die
		variables which will hold result from throwing a die

	msg_pos_x and msg_pos_y
		variables which will hold positions of some messages in
		initialize and starting_pl functions

	pl1_name_input and pl2_name_input
		strings which will hold player names

	game_goal
		variable which holds goal position of the game
	-------------------------------------------------------*/
	int pl1_die;
	int pl2_die;
	int msg_pos_x;
	int msg_pos_y;
	std::string pl1_name_input;
	std::string pl2_name_input;
	int game_goal;
public:
	Game();
	//Creates object called die_six of Die class allowing use of functions in that class
	Die die_six;
	//Creates object called game_board of Board class allowing use of functions in that class
	Board game_board;
	void prepare_window();
	void show_title();
	void initialize();
	void starting_pl();
	void main_game_loop();
	void print_instr();
	void end();
};
#endif //!GAME_H