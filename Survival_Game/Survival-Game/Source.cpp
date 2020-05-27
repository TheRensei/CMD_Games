#include <iostream>

#include "Game.h"
#include "console.h"
#include "Player.h"
#include "Board.h"

using namespace std;

int main()
{
	Game one;
	one.set_settings();
	one.play();
	one.end();

	Console::setCursorPosition(10, 0);
	Console::pause("Click...");
	return 0;
}