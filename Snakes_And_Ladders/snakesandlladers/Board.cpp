#include "Board.h"


/*-------------------------------------------------------------------
Default constructor in which arrays for
snakes and ladders are created.
--------------------------------------------------------------------*/
Board::Board()
{
	for (int i = 0; i < 3;i++)
	{
		if (i == 0)
		{
			snake_head[i] = 13;
			snake_tail[i] = 2;
			ladder_top[i] = 17;
			ladder_bot[i] = 4;
		}
		else if (i == 1)
		{
			snake_head[i] = 19;
			snake_tail[i] = 6;
			ladder_top[i] = 18;
			ladder_bot[i] = 7;
		
		}
		else if (i == 2)
		{
			snake_head[i] = 24;
			snake_tail[i] = 3;
			ladder_top[i] = 22;
			ladder_bot[i] = 15;
		}
	}
	//sets length and width of the board
	length = 16;
	width = 36;
}

/*-------------------------------------------------------------------
Function which calculates x and y positions for the board.
Sets the cursor on aproperiate positions and prints the board walls.
--------------------------------------------------------------------*/
void Board::print_board()
{
	for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < length; y++)
			{
				if (x % 7 == 0 && y >= 1)
				{
					Console::setCursorPosition(y, x);
					std::cout << "|";
				}
				else
				{
					Console::setCursorPosition(y, x);
					std::cout << "_";
				}
			}
		}

	//Call functions which prints board numbers
	print_board_num();
}

/*-------------------------------------------------------------------
			Prints numbers on the board and spaces 
		around them allowing colouring whole square
--------------------------------------------------------------------*/
void Board::print_board_num()
{
	num = 25;
	for (int y = 2; y < length; y = y + 3) 
	{
		for (int x = width - 5; x > 2; x = x - 7, num--)
		{
			change_colours(); //calls function to change colours of squares
			if (num < 10)
			{
				Console::setCursorPosition(y - 1, x - 2);
				std::cout << "      ";
				Console::setCursorPosition(y, x - 2);
				std::cout << "  " << num << "   ";
				Console::setCursorPosition(y + 1, x - 2);
				std::cout << "______";
			}
			else
			{
				Console::setCursorPosition(y-1, x - 2);
				std::cout << "      ";
				Console::setCursorPosition(y, x - 2);
				std::cout << "  " << num << "  ";
				Console::setCursorPosition(y+1, x - 2);
				std::cout << "______";
			}
		}
	}
	//sets colours to default for this game
	Console::setColour(Console::WHITE, Console::BLACK);
}

/*-------------------------------------------------------------------
Changes colours of squares for:
	players
	snakes
	ladders
if num (number on the square) is equal to:
	player position
	snakes head or tail
	ladder top or bottom
Player colour have priotity and because of that it will always be on top
so player position will always be visible
-------------------------------------------------------------------*/
void Board::change_colours()
{
	/*----------------------------------------------------
						Player colours
	-----------------------------------------------------*/
	if (pl1.get_position() == pl2.get_position() && num == pl2.get_position())
	{
		Console::setColour(Console::WHITE, Console::YELLOW);
	}
	else if (num == pl1.get_position())
	{
		Console::setColour(Console::WHITE, Console::PURPLE);
	}
	else if (num == pl2.get_position())
	{
		Console::setColour(Console::WHITE, Console::GREEN);
	}
	/*----------------------------------------------------
						Snakes' colours
	-----------------------------------------------------*/

	else if (num == snake_head[0] || num == snake_tail[0])
	{
		Console::setColour(Console::WHITE, Console::RED);
	}
	else if (num == snake_head[1] || num == snake_tail[1])
	{
		Console::setColour(Console::WHITE, Console::RED);
	}
	else if (num == snake_head[2] || num == snake_tail[2])
	{
		Console::setColour(Console::WHITE, Console::RED);
	}
	/*----------------------------------------------------
						Ladders colours
	-----------------------------------------------------*/

	else if (num == ladder_top[0] || num == ladder_bot[0])
	{
		Console::setColour(Console::WHITE, Console::BLUE);
	}
	else if (num == ladder_top[1] || num == ladder_bot[1])
	{
		Console::setColour(Console::WHITE, Console::BLUE);
	}
	else if (num == ladder_top[2] || num == ladder_bot[2])
	{
		Console::setColour(Console::WHITE, Console::BLUE);
	}
	else
	{
		Console::setColour(Console::WHITE, Console::BLACK);
	}
}

/*------------------------------------------------------------------
						Creates players
					sets name for the players
-------------------------------------------------------------------*/
void Board::create_players(std::string pl1_name_input, std::string pl2_name_input)
{
	pl1.set_name(pl1_name_input);
	pl2.set_name(pl2_name_input);
}

/*------------------------------------------------------------------
							Snakes
		If player position is equal to snakes' head:
			print message
			change position of player to snakes' tail
-------------------------------------------------------------------*/
void Board::snakes()
{
	Console::setCursorPosition(19, 0);

	if (pl1.get_position() == snake_head[0])
	{
		std::cout << pl1.get_name() << " stepped on snakes' head (" << snake_head[0] << ")!\nMove to position " << snake_tail[0] <<"!!";
		pl1.set_position(snake_tail[0]);
	}
	if (pl2.get_position() == snake_head[0])
	{
		std::cout << pl2.get_name() << " stepped on snakes' head (" << snake_head[0] << ")!\nMove to position " << snake_tail[0] << "!!";
		pl2.set_position(snake_tail[0]);
	}
	if (pl1.get_position() == snake_head[1])
	{
		std::cout << pl1.get_name() << " stepped on snakes' head (" << snake_head[1] << ")!\nMove to position " << snake_tail[1] << "!!";
		pl1.set_position(snake_tail[1]);
	}
	if (pl2.get_position() == snake_head[1])
	{
		std::cout << pl2.get_name() << " stepped on snakes' head (" << snake_head[1] << ")!\nMove to position " << snake_tail[1] << "!!";
		pl2.set_position(snake_tail[1]);
	}
	if (pl1.get_position() == snake_head[2])
	{
		std::cout << pl1.get_name() << " stepped on snakes' head (" << snake_head[2] << ")!\nMove to position " << snake_tail[2] << "!!";
		pl1.set_position(snake_tail[2]);
	}
	if (pl2.get_position() == snake_head[2])
	{
		std::cout << pl2.get_name() << " stepped on snakes' head (" << snake_head[2] << ")!\nMove to position " << snake_tail[2] << "!!";
		pl2.set_position(snake_tail[2]);
	}
}

/*------------------------------------------------------------------
						Ladders
		If player position is equal to ladder bottom:
			print message
			change position of player to ladder top
-------------------------------------------------------------------*/
void Board::ladders()
{
	if (pl1.get_position() == ladder_bot[0])
	{
		std::cout << pl1.get_name() << " lands of the bottom of a ladder (" << ladder_bot[0] << ")!\nMove to position " << ladder_top[0] << "!!";
		pl1.set_position(ladder_top[0]);
	}
	if (pl2.get_position() == ladder_bot[0])
	{
		std::cout << pl2.get_name() << " lands of the bottom of a ladder (" << ladder_bot[0] << ")!\nMove to position " << ladder_top[0] << "!!";
		pl2.set_position(ladder_top[0]);
	}
	if (pl1.get_position() == ladder_bot[1])
	{
		std::cout << pl1.get_name() << " lands of the bottom of a ladder (" << ladder_bot[1] << ")!\nMove to position " << ladder_top[1] << "!!";
		pl1.set_position(ladder_top[1]);
	}
	if (pl2.get_position() == ladder_bot[1])
	{
		std::cout << pl2.get_name() << " lands of the bottom of a ladder (" << ladder_bot[1] << ")!\nMove to position " << ladder_top[1] << "!!";
		pl2.set_position(ladder_top[1]);
	}
	if (pl1.get_position() == ladder_bot[2])
	{
		std::cout << pl1.get_name() << " lands of the bottom of a ladder (" << ladder_bot[2] << ")!\nMove to position " << ladder_top[2] << "!!";
		pl1.set_position(ladder_top[2]);
	}
	if (pl2.get_position() == ladder_bot[2])
	{
		std::cout << pl2.get_name() << " lands of the bottom of a ladder (" << ladder_bot[2] << ")!\nMove to position " << ladder_top[2] << "!!";
		pl2.set_position(ladder_top[2]);
	}
}
