#pragma once

#include "GameObject.h"
#include <vector>

enum BlockType
{
	STONE,
	GOLD,
	DIAMOND
};

class Block : public GameObject
{
public:
	BlockType blockType;
protected:
	int hp;
public:
	Block(int x, int y, int width, int height, BlockType blockType);

	void hit(int damage);

	int getHp();
	
	
};
