#pragma once

#include "GameObject.h"

class Block : public GameObject
{
protected:
	int hp;
public:
	Block(int x, int y, int width, int height, int hp, std::string texturePath);

	void getHit(int damage);

	int getHp();
	
};
