#include "Board.h"


Board::Board()
{
	//random
	srand(static_cast<unsigned int>(time(0)));
	rand();
}

void Board::prepare_board()
{
	trap_count = height / 1.5;
	monster_count = height / 4;

	trap_vector.resize(trap_count, Trap());
	monster_vector.resize(monster_count, Monster());
}

void Board::set_width(int new_width)
{
	width = new_width * 2;
}

void Board::set_height(int new_height)
{
	height = new_height;
}

void Board::set_initial_positions()
{
	min = 2; //min random number for random position
	rand_x;
	rand_y;

	//generate random position x and y
	std::vector<std::pair<int, int>> random_pos;

	//----------------------------------------------
				//traps
	for (int i = 0; i < trap_vector.size(); i++)
	{
		rand_x = rand() % (width - min) + min;
		rand_y = rand() % (height - min) + min;

		random_pos.push_back(std::make_pair(rand_x, rand_y));
	}

	//check for repetition
	for (int i = 0; i < trap_vector.size(); i++)
	{
		if (i >= 1)
		{
			for (int j = 0; j < i; j++)
			{
				if (random_pos[i].first == random_pos[j].first && random_pos[i].second == random_pos[j].second)
				{
					rand_x = rand() % (width - min) + min;
					random_pos[i].first = rand_x;

					rand_y = rand() % (height - min) + min;
					random_pos[i].second = rand_y;
					j = -1;
				}
			}
		}
	}

	//set trap positions
	for (int i = 0; i < trap_vector.size(); i++)
	{
		trap_vector[i].set_position_x(random_pos[i].first);
		trap_vector[i].set_position_y(random_pos[i].second);
	}

	//------------------------------------------------------
						//monsters
	random_pos.clear(); //clear vector with positions for monster

	for (int i = 0; i < monster_vector.size(); i++)
	{
		rand_x = rand() % (width - min) + min;
		rand_y = rand() % (height - min) + min;

		random_pos.push_back(std::make_pair(rand_x, rand_y));
	}

	//check for repetition
	for (int i = 0; i < monster_vector.size(); i++)
	{
		if (i >= 1)
		{
			for (int j = 0; j < i; j++)
			{
				if (random_pos[i].first == random_pos[j].first && random_pos[i].second == random_pos[j].second)
				{
					rand_x = rand() % (width - min) + min;
					random_pos[i].first = rand_x;

					rand_y = rand() % (height - min) + min;
					random_pos[i].second = rand_y;
					j = -1;
				}
			}
		}
	}

	//check if monster spawned on top of the trap, if yes, change position
	for (int i = 0; i < monster_vector.size(); i++)
	{
		for (int j = 0; j < trap_vector.size();j++)
		{
			if (random_pos[i].first == trap_vector[j].get_position_x() && random_pos[i].second == trap_vector[j].get_position_y())
			{
				rand_x = rand() % (width - min) + min;
				random_pos[i].first = rand_x;

				rand_y = rand() % (height - min) + min;
				random_pos[i].second = rand_y;
				j = -1;
			}
		}
	}

	//set monster positions
	for (int i = 0; i < monster_vector.size(); i++)
	{
		monster_vector[i].set_position_x(random_pos[i].first);
		monster_vector[i].set_position_y(random_pos[i].second);
	}

	random_pos.clear(); //clear vector with positions

	//spawn player
	rand_x = rand() % (width - min) + min;
	rand_y = rand() % (height - min) + min;
	
	//checks if player is going to be spawned on top of the trap or monster, if yes, change position
	for (int j = 0; j < trap_vector.size(); j++)
	{
		if (rand_x == trap_vector[j].get_position_x() && rand_y == trap_vector[j].get_position_y())
		{
			rand_x = rand() % (width - min) + min;
			rand_y = rand() % (height - min) + min;
		}
		if (j < monster_vector.size())
		{	
			if (rand_x == monster_vector[j].get_position_x() && rand_y == monster_vector[j].get_position_y())
			{
				rand_x = rand() % (width - min) + min;
				rand_y = rand() % (height - min) + min;
			}
		}
	}

	pl.set_position_x(rand_x);
	pl.set_position_y(rand_y);

}

void Board::create_board()
{
	//spawn board
	for (int y = 1; y <= height; y++)
	{
		for (int x = 1; x <= width; x++)
		{
			Console::setCursorPosition(y, x);
			
			if (x == 1 || x == width)
			{
				if (y > 0)
				{	
					std::cout << "|";
				}
			}
			else if (y == 1|| y == height)
			{
				std::cout << "--";
			}
		}
	}

	set_initial_positions();

	//spawn monsters and traps at initial positions
	for (int i = 0; i < trap_vector.size(); i++)
	{
		trap_vector[i].spawn();
		if (i < monster_vector.size())
		{
			monster_vector[i].spawn();
		}
	}

	Console::setCursorPosition(pl.get_position_y(), pl.get_position_x());
	std::cout << "C";

	char pl_move = ' ';
	int mon_move = 0;

	while (pl_move != 'q')
	{
		//set previous position for player
		pl.set_prev_position_x();
		pl.set_prev_position_y();

		//get input
		pl_move = _getch();

		//move player
		switch (pl_move)
		{
		case 'w':
			pl.set_position_y(pl.get_position_y() - 1);
			break;
		case '8':
			pl.set_position_y(pl.get_position_y() - 1);
			break;
		case 's':
			pl.set_position_y(pl.get_position_y() + 1);
			break;
		case '2':
			pl.set_position_y(pl.get_position_y() + 1);
			break;
		case 'a':
			pl.set_position_x(pl.get_position_x() - 1);
			break;
		case '4':
			pl.set_position_x(pl.get_position_x() - 1);
			break;
		case 'd':
			pl.set_position_x(pl.get_position_x() + 1);
			break;
		case '6':
			pl.set_position_x(pl.get_position_x() + 1);
			break;
		}

		//spawn player
		if (pl.get_position_x() <= 1 || pl.get_position_x() >= width)
		{
			pl.set_position_x(pl.get_prev_position_x());
		}
		else if (pl.get_position_y() <= 1 || pl.get_position_y() >= height)
		{
			pl.set_position_y(pl.get_prev_position_y());
		}
		else
		{
			pl.spawn();
		}

		//check collision player-trap and player-monster and monster-trap
		for (int i = 0; i < trap_vector.size(); i++)
		{
			if (pl.get_position_x() == trap_vector[i].get_position_x() && pl.get_position_y() == trap_vector[i].get_position_y())
			{
				pl_move = 'q';
			}
			else if (i < monster_vector.size())
			{
				if (pl.get_position_x() == monster_vector[i].get_position_x() && pl.get_position_y() == monster_vector[i].get_position_y())
				{
					pl_move = 'q';
				}
			}
		}

		//move monsters
		for (int i = 0; i < monster_vector.size(); i++)
		{
			//set previous positon for monster
			monster_vector[i].set_prev_position_x();
			monster_vector[i].set_prev_position_y();

			//generate random direction
			mon_move = rand() % 4 + 1;

			//change position
			switch (mon_move)
			{
			case 1:
				monster_vector[i].set_position_y(monster_vector[i].get_position_y() - 1);
				break;
			case 2:
				monster_vector[i].set_position_y(monster_vector[i].get_position_y() + 1);;
				break;
			case 3:
				monster_vector[i].set_position_x(monster_vector[i].get_position_x() - 1);
				break;
			case 4:
				monster_vector[i].set_position_x(monster_vector[i].get_position_x() + 1);
				break;
			}
			

			//check if monster tries to go out of the board, if yes, don't change position, else, change position
			if (monster_vector[i].get_position_x() <= 1 || monster_vector[i].get_position_x() >= width)
			{
				monster_vector[i].set_position_x(monster_vector[i].get_prev_position_x());
			}
			else if (monster_vector[i].get_position_y() <= 1 || monster_vector[i].get_position_y() >= height)
			{
				monster_vector[i].set_position_y(monster_vector[i].get_prev_position_y());
			}
			else
			{
				monster_vector[i].spawn();
			}
		}

		//check collision player-trap and player-monster and monster-trap
		for (int i = 0; i < trap_vector.size(); i++)
		{
			if (pl.get_position_x() == trap_vector[i].get_position_x() && pl.get_position_y() == trap_vector[i].get_position_y())
			{
				pl_move = 'q';
			}
			else if (i < monster_vector.size())
			{
				if (pl.get_position_x() == monster_vector[i].get_position_x() && pl.get_position_y() == monster_vector[i].get_position_y())
				{
					pl_move = 'q';
				}
			}
			for (int j = 0; j < monster_vector.size(); j++)
			{
				if (monster_vector[j].get_position_x() == trap_vector[i].get_position_x() && monster_vector[j].get_position_y() == trap_vector[i].get_position_y())
				{
					monster_vector.erase(monster_vector.begin() + j);
					trap_vector[i].spawn();
				}
			}
		}
	}
}

int Board::get_result()
{
	return result;
}

Board::~Board()
{

}
