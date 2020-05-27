#include "Game.h"


void Game::set_settings()
{
	std::cout << "Hello, now you will set size of the board. Remember to choose size bigger than zero." << std::endl;

	//input validation
	do
	{
		std::cout << "Set width of the board to: ";
		std::cin >> choice;
		if (choice <= 0)
		{
			std::cout << "I said bigger than 0!" << std::endl;
		}
	} while (choice <= 0);

	game_board.set_width(choice);

	//input validation
	do
	{
		std::cout << "Set height of the board to: ";
		std::cin >> choice;
		if (choice <= 0)
		{
			std::cout << "I said bigger than 0!" << std::endl;
		}
	} while (choice <= 0);

	game_board.set_height(choice);

	Console::clear();

	game_board.prepare_board();
}

void Game::play()
{
	game_board.create_board();
	Console::clear();
}

void Game::end()
{
	if (game_board.get_result() == 0)
	{
		std::cout << "You won! You killed all monsters! Congratulations!" << std::endl;
	}
	else
	{
		std::cout << "You lost! Better luck next time!" << std::endl;
	}
}

