#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "console.h"
#include "Character.h"

class Player : public Character
{
private:
	int score;
public:
	void spawn();
};

#endif //PLAYER_H