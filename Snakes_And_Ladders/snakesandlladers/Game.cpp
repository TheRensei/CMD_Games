#include "Game.h"

/*--------------------------------------------------------
					Default Constructor
Setts initial positions for messages for starting player function
			msg_pos_x
			msg_pox_y
Sets variable game_goal to 25
----------------------------------------------------------*/
Game::Game()
{
	msg_pos_x = 2;
	msg_pos_y = 10;
	game_goal = 25;
}

/*--------------------------------------------------------
		setWindowTitle - changes window title
		setTextBufferSize - changes window size
		setColour - changes colours in the console
----------------------------------------------------------*/
void Game::prepare_window()
{
	Console::setWindowTitle("Snakes and Ladders: The video game");
	Console::setTextBufferSize(22, 52);
	Console::setColour(Console::WHITE, Console::BLACK);
}

/*----------------------------------------------------------
		Initializes game by creating players and
		allows random generator to be used
-----------------------------------------------------------*/
void Game::initialize()
{
	/*--------------------------------------------------------------
	-Srand is needed to use in generating random numbers
	-rand() have to be called once before actual use because
	of the bug in visual studio
	---------------------------------------------------------------*/
	srand(static_cast<int>(time(0)));
	rand();

	/*--------------------------------------------------------------
				Creates Players
	--------------------------------------------------------------*/
	Console::setCursorPosition(msg_pos_x, 1);
	std::cout << "Player names have to be shorter than 10 characters!"; 

	//asks for player 1 name
	Console::setCursorPosition(msg_pos_x+=1, msg_pos_y);
	std::cout << "Enter Player 1 name: ";
	std::cin >> pl1_name_input;
	
	//input validation for player name, it have to be shorter than 10 characters
	while (pl1_name_input.length() > 10)
	{
		std::cout << "Name was too long. Enter it again: ";
		std::cin >> pl1_name_input;
	}
	Console::clear();

	//asks for players 2 name
	Console::setCursorPosition(msg_pos_x += 1, msg_pos_y);
	std::cout << "Enter Player 2 name: ";
	std::cin >>pl2_name_input;

	//input validation for player name, it have to be shorter than 10 characters
	while (pl2_name_input.length() > 10)
	{
		std::cout << "Name was too long. Enter it again: ";
		std::cin >> pl1_name_input;
	}
	Console::clear();

	//Prints messages showing what names did user choose
	Console::setCursorPosition(msg_pos_x += 1, msg_pos_y);
	std::cout << "Player 1 name set to: " << pl1_name_input;

	Console::setCursorPosition(msg_pos_x += 1, msg_pos_y);
	std::cout << "Player 2 name set to: " << pl2_name_input;
	Console::pause("");
	Console::clear();

	//sends names of the players to game_board class
	game_board.create_players(pl1_name_input, pl2_name_input);

}

/*-----------------------------------------------------------------
	Reads title from the file and prints it on the screen
-------------------------------------------------------------------*/
void Game::show_title()
{
	std::string line;

	std::ifstream title_file("title.txt"); 

	//sets colours for the title
	Console::setColour(Console::GREEN, Console::BLACK);

	//if file got succesfully opened then reads from file to line string and prints it on the screen
	if (title_file.is_open())
	{
		while (getline(title_file, line))
		{
			std::cout << line << '\n';
			Sleep(100); //slows printing title on the screen for better effect
		}
		//closes the file after reading ends
		title_file.close();
	}
	//else if file couldn't be opened prints this message
	else
	{
		std::cout << "Unable to open title file!"; 
	}

	//after title has beed printed on the screen changes colours to normal
	Console::setColour(Console::WHITE, Console::BLACK);
	
	Console::pause("");
	Console::clear();
}

/*----------------------------------------------------------------
				Determines starting player
Die roll is simulated by calling roll() funcion from die class
		and assigning it to the player_die variable.
			Console is paused after each message
-----------------------------------------------------------------*/
void Game::starting_pl()
{
	Console::setCursorPosition(msg_pos_x -= 4, msg_pos_y);
	std::cout << "Each player have to roll a die." << std::endl;

	Console::setCursorPosition(msg_pos_x += 2, msg_pos_y-6);
	std::cout << "Player with higher score will start the game." << std::endl;
	Console::pause("");

	Console::setCursorPosition(msg_pos_x += 2, msg_pos_y);
	pl1_die =  die_six.roll(); //die roll
	std::cout << game_board.pl1.get_name() << " rolls " << pl1_die << std::endl;
	Console::pause("");

	Console::setCursorPosition(msg_pos_x += 2, msg_pos_y);
	pl2_die = die_six.roll(); //die roll
	std::cout << game_board.pl2.get_name() << " rolls " << pl2_die << std::endl;
	Console::pause("");

	/*-----------------------------------------------------------------
	In case of both players rolled the same number
	rolls again until they rolled diffirent numbers
	-------------------------------------------------------------------*/

	while (pl1_die == pl2_die)
	{
		Console::setCursorPosition(msg_pos_x += 2, msg_pos_y);
		std::cout << "Players have to roll again." << std::endl;
		Console::pause("");

		Console::setCursorPosition(msg_pos_x += 2, msg_pos_y);
		pl1_die = die_six.roll();
		std::cout << game_board.pl1.get_name() << " rolls " << pl1_die << std::endl;
		Console::pause("");

		Console::setCursorPosition(msg_pos_x += 2, msg_pos_y);
		pl2_die = die_six.roll();
		std::cout << game_board.pl2.get_name() << " rolls " << pl2_die << std::endl;
		Console::pause("");
	}

}

/*--------------------------------------------------------------
		Checks results from starting_pl function. 
		Chcecks which player had higher score and runs 
					approperiate loop
----------------------------------------------------------------*/
void Game::main_game_loop()
{
	if (pl1_die > pl2_die)
	{
		Console::setCursorPosition(msg_pos_x += 2, msg_pos_y);
		std::cout << game_board.pl1.get_name() << " starts first!" << std::endl;
		Console::pause("");
		Console::clear();

		Console::setCursorPosition(10, 15);
		std::cout << "The game starts!";
		Console::pause("");

		/*------------------------------------------------------------------
										Game Loop
		--------------------------------------------------------------------*/
		while (game_board.pl1.get_position() != game_goal && game_board.pl2.get_position() != game_goal)
		{
			//Prints board
			game_board.print_board();
			
			//Prints instructions
			print_instr();
			Console::pause("");

			/*-------------------------------------------------------------------------
										Player 1 Movement
			--------------------------------------------------------------------------*/
			//Simulates die roll
			pl1_die = die_six.roll();
			Console::setCursorPosition(17, 9);
			
			//Prints message saying displaying of roll
			std::cout << game_board.pl1.get_name() << " rolls " << pl1_die << "!" << std::endl;
			

			//Sets new position by adding result from rolling a die to current position
			game_board.pl1.set_position(game_board.pl1.get_position() + pl1_die);

			//If player position is bigger than game_goal then player doesn't move
			if (game_board.pl1.get_position() > game_goal)
			{
				std::cout << "and stays on current position.";
				
				//If new position is bigger than game_goal it subtracts result from rolling a die from current position
				game_board.pl1.set_position(game_board.pl1.get_position() - pl1_die);
			}
			else
			{
				Console::setCursorPosition(18, 6);
				std::cout << "and moves to " << game_board.pl1.get_position() << '!' << std::endl;
			}
			Console::pause("");
			Console::clear();

			//Prints Board
			game_board.print_board();

			//Prints instructions
			print_instr();

			//Checks for snakes
			game_board.snakes();

			//Checks for ladders
			game_board.ladders();

			Console::pause("");
			Console::clear();

			//Prints board
			game_board.print_board();
			
			//Prints instructions
			print_instr();
			
			//if player 1 position is not equal to game_goal let player 2 move
			//it stops from moving player 2 after player 1 reached goal
			if (game_board.pl1.get_position() != game_goal)
			{
				/*-------------------------------------------------------------------------
											Player 2 Movement
				--------------------------------------------------------------------------*/
				//Simulates die roll
				pl2_die = die_six.roll();
				Console::setCursorPosition(17, 9);

				//Prints message saying displaying of roll
				std::cout << game_board.pl2.get_name() << " rolls " << pl2_die << "!" << std::endl;

				//Sets new position by adding result from rolling a die to current position
				game_board.pl2.set_position(game_board.pl2.get_position() + pl2_die);


				//If player position is bigger than game_goal then player doesn't move
				if (game_board.pl2.get_position() > game_goal)
				{
					std::cout << "and stays on current position";
					//If new position is bigger than game_goal it subtracts result from rolling a die from current position
					game_board.pl2.set_position(game_board.pl2.get_position() - pl2_die);
				}
				else
				{
					Console::setCursorPosition(18, 6);
					std::cout << "and moves to " << game_board.pl2.get_position() << '!' << std::endl;
				}


				Console::pause("");
				Console::clear();

				//Prints Board
				game_board.print_board();

				//Prints instructions
				print_instr();

				//Checks for snakes
				game_board.snakes();

				//Checks for ladders
				game_board.ladders();

				Console::pause("");
				Console::clear();
			}

		}

	}

	else if (pl2_die > pl1_die)
	{
		Console::setCursorPosition(msg_pos_x = msg_pos_x + 2, 10);
		std::cout << game_board.pl2.get_name() << " starts first!" << std::endl;
		Console::pause("");
		Console::clear();

		Console::setCursorPosition(10, 15);
		std::cout << "The game starts!";
		Console::pause("");
		/*------------------------------------------------------------------
									Game Loop
		--------------------------------------------------------------------*/
		while (game_board.pl1.get_position() != game_goal && game_board.pl2.get_position() != game_goal)
		{
			//Prints board
			game_board.print_board();

			//Prints instructions
			print_instr();
			Console::pause("");

			/*-------------------------------------------------------------------------
										Player 2 Movement
			--------------------------------------------------------------------------*/
			//Simulates die roll
			pl2_die = die_six.roll();
			Console::setCursorPosition(17, 9);

			//Prints message saying displaying of roll
			std::cout << game_board.pl2.get_name() << " rolls " << pl2_die << "!" << std::endl;

			//Sets new position by adding result from rolling a die to current position
			game_board.pl2.set_position(game_board.pl2.get_position() + pl2_die);

			//If player position is bigger than game_goal then player doesn't move
			if (game_board.pl2.get_position() > game_goal)
			{
				std::cout << "and stays on current position";
				//If new position is bigger than game_goal it subtracts result from rolling a die from current position
				game_board.pl2.set_position(game_board.pl2.get_position() - pl2_die);
			}
			else
			{
				Console::setCursorPosition(18, 6);
				std::cout << "and moves to " << game_board.pl2.get_position() << '!' << std::endl;
			}

			Console::pause("");
			Console::clear();

			//Prints Board
			game_board.print_board();

			//Prints instructions
			print_instr();

			//Checks for snakes
			game_board.snakes();

			//Checks for ladders
			game_board.ladders();

			Console::pause("");
			Console::clear();

			//Prints board
			game_board.print_board();

			//Prints instructions
			print_instr();

			//if player 2 position is not equal to game_goal let player 1 move
			//it stops from moving player 1 after player 2 reached goal

			if (game_board.pl2.get_position() != game_goal)
			{
				/*-------------------------------------------------------------------------
											Player 1 Movement
				--------------------------------------------------------------------------*/
				//Simulates die roll
				pl1_die = die_six.roll();
				Console::setCursorPosition(17, 9);

				//Prints message saying displaying of roll
				std::cout << game_board.pl1.get_name() << " rolls " << pl1_die << "!" << std::endl;


				//Sets new position by adding result from rolling a die to current position
				game_board.pl1.set_position(game_board.pl1.get_position() + pl1_die);

				//If player position is bigger than game_goal then player doesn't move
				if (game_board.pl1.get_position() > game_goal)
				{
					std::cout << "and stays on current position.";

					//If new position is bigger than game_goal it subtracts result from rolling a die from current position
					game_board.pl1.set_position(game_board.pl1.get_position() - pl1_die);
				}
				else
				{
					Console::setCursorPosition(18, 6);
					std::cout << "and moves to " << game_board.pl1.get_position() << '!' << std::endl;
				}
				Console::pause("");
				Console::clear();

				//Prints Board
				game_board.print_board();

				//Prints instructions
				print_instr();

				//Checks for snakes
				game_board.snakes();

				//Checks for ladders
				game_board.ladders();

				Console::pause("");
				Console::clear();
			}
		}
	}
}

/*-----------------------------------------------------------
Right side instructions:
Player indicators
Snake indicators
Ladder indicators
-------------------------------------------------------------*/
void Game::print_instr()
{
	/*--------------------------------------------------------
							Players
	----------------------------------------------------------*/
	Console::setCursorPosition(1, 37);
	std::cout << "Players: ";
	Console::setCursorPosition(3, 37);
	Console::setColour(Console::WHITE, Console::YELLOW);
	std::cout << "  ";
	Console::setColour(Console::WHITE, Console::BLACK);
	std::cout << " - Both";

	Console::setCursorPosition(4, 37);
	Console::setColour(Console::WHITE, Console::PURPLE);
	std::cout << "  ";
	Console::setColour(Console::WHITE, Console::BLACK);
	std::cout << " - " << game_board.pl1.get_name();

	Console::setCursorPosition(5, 37);
	Console::setColour(Console::WHITE, Console::GREEN);
	std::cout << "  ";
	Console::setColour(Console::WHITE, Console::BLACK);
	std::cout << " - " << game_board.pl2.get_name();

	/*--------------------------------------------------------
							Snakes
	----------------------------------------------------------*/
	Console::setCursorPosition(7, 37);
	std::cout << "Snakes: "; 
	Console::setColour(Console::WHITE, Console::RED);
	std::cout << "  ";
	Console::setColour(Console::WHITE, Console::BLACK);

	Console::setCursorPosition(9, 37);
	Console::setColour(Console::WHITE, Console::RED);
	std::cout << game_board.snake_head[0] << "-" << game_board.snake_tail[0];
	Console::setColour(Console::WHITE, Console::BLACK);
	std::cout << "-Snake 1";

	Console::setCursorPosition(10, 37);
	Console::setColour(Console::WHITE, Console::RED);
	std::cout << game_board.snake_head[1] << "-" << game_board.snake_tail[1];
	Console::setColour(Console::WHITE, Console::BLACK);
	std::cout << "-Snake 2";

	Console::setCursorPosition(11, 37);
	Console::setColour(Console::WHITE, Console::RED);
	std::cout << game_board.snake_head[2] << "-" << game_board.snake_tail[2];
	Console::setColour(Console::WHITE, Console::BLACK);
	std::cout << "-Snake 3";

	/*--------------------------------------------------------
							Ladders
	----------------------------------------------------------*/
	Console::setCursorPosition(13, 37);
	std::cout << "Ladders: ";
	Console::setColour(Console::WHITE, Console::BLUE);
	std::cout << "  ";
	Console::setColour(Console::WHITE, Console::BLACK);

	Console::setCursorPosition(15, 37);
	Console::setColour(Console::WHITE, Console::BLUE);
	std::cout << game_board.ladder_bot[0] << "-" << game_board.ladder_top[0];
	Console::setColour(Console::WHITE, Console::BLACK);
	std::cout << "-Ladder 1";

	Console::setCursorPosition(16, 37);
	Console::setColour(Console::WHITE, Console::BLUE);
	std::cout << game_board.ladder_bot[1] << "-" << game_board.ladder_top[1];
	Console::setColour(Console::WHITE, Console::BLACK);
	std::cout << "-Ladder 2";

	Console::setCursorPosition(17, 37);
	Console::setColour(Console::WHITE, Console::BLUE);
	std::cout << game_board.ladder_bot[2] << "-" << game_board.ladder_top[2];
	Console::setColour(Console::WHITE, Console::BLACK);
	std::cout << "-Ladder 3";
}

/*---------------------------------------------------------------
Win check and message
If player is on position 25 then prints a message
Create log file if doesn't exist
Update log file if one already exists
----------------------------------------------------------------*/

void Game::end()
{
	/*------------------------------------------------------------
	Creates log file with time and date of the game
	Log structure:
	Time and Date
	Players:
			'Player 1 name'
			'Player 2 name'
	Won: 'Player 1 name' in 'number of moves' moves.
	Lost: 'Player 2 name'
	-------------------------------------------------------------*/
	time_t now = time(0);
	errno_t ctime_s(char *buffer, rsize_t bufsz, const time_t *time); //converts given time since epoch to a callendar local time and the to a textual representation
	char date[26]; //creates char array of size 26 that will hold date and time
	ctime_s(date, sizeof date, &now);

	std::fstream log;
	//opens or crates if doesn't exist log file
	log.open("log.txt", std::fstream::app);
	log << "----------------------------------\n";
	log << date;
	log << "Players: \n";
	log << "	" << game_board.pl1.get_name() << '\n';
	log << "	" << game_board.pl2.get_name() << '\n';

	//Prints messages indicating winning player and adds entry in log file with information of wining and losing player
	if (game_board.pl1.get_position() == game_goal)
	{
		game_board.print_board();
		Console::setCursorPosition(18, 0);
		std::cout << game_board.pl1.get_name() << " won in " << game_board.pl1.get_moves() << " moves!!!" << std::endl;;
		log << "Won: " << game_board.pl1.get_name() << " in " << game_board.pl1.get_moves() << " moves.\n";
		log << "Lost: " << game_board.pl2.get_name() << '\n';
	}
	if (game_board.pl2.get_position() == game_goal)
	{
		game_board.print_board();
		Console::setCursorPosition(18, 0);
		std::cout << game_board.pl2.get_name() << " won in " << game_board.pl2.get_moves() << " moves!!!" << std::endl;
		log << "Won: " << game_board.pl2.get_name() << " in " << game_board.pl2.get_moves() << " moves.\n";
		log << "Lost: " << game_board.pl1.get_name() << '\n';
	}
}