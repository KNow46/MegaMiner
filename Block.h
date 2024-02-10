#pragma once

#include "GameObject.h"
#include <vector>

enum BlockType
{
	stone
};

class Block : public GameObject
{
public:
	BlockType blockType;
protected:
	int hp;
public:
	Block(int x, int y, int width, int height, int hp, BlockType blockType);

	void getHit(int damage);

	int getHp();
	
	
};
