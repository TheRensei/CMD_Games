#include <iostream>
#include "console.h"
#include "Game.h"

using namespace std;
int main()
{
	Game SnL; //creates object of class Game
	SnL.prepare_window();
	SnL.show_title();
	SnL.initialize();
	SnL.starting_pl();
	SnL.main_game_loop();
	SnL.end();
	Console::setCursorPosition(24, 0);
	Console::pause("Press any button to finish...");
	return 0;
}
