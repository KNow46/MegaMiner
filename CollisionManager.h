#pragma once
#include "GameObject.h"
#include <vector>
#include "World.h"
#include <memory>

class CollisionManager
{
public:
	std::shared_ptr<GameObject> checkBlocksCollisions(int x, int y)
	{
		for (const auto& object : World::getInstance().getVisibleBlocks())
		{
			if (x >= object->getX() && x < object->getX() + object->getWidth())
			{
				if (y >= object->getY() && y < object->getY() + object->getHeight())
				{
					return object;
				}
			}
		}
		return nullptr;
		
	}
	std::shared_ptr<Machine> checkMachineCollision(int x, int y)
	{
		
		if (x >= World::getInstance().getMachine()->getX() && x < World::getInstance().getMachine()->getX() + World::getInstance().getMachine()->getWidth())
		{
			if (y >= World::getInstance().getMachine()->getY() && y < World::getInstance().getMachine()->getY() + World::getInstance().getMachine()->getHeight())
			{
				return  World::getInstance().getMachine();
			}
		}
		return nullptr;
	}
	static CollisionManager& getInstance()
	{
		static CollisionManager instance;
		return instance;
	}
private:

};