#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>

#include "Character.h"

class Monster :
	public Character
{
public:
	void spawn();
};

#endif //MONSTER_H