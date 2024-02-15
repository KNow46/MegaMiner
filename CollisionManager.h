#pragma once
#include "GameObject.h"
#include <vector>
#include "World.h"
#include <memory>

class CollisionManager
{
public:
	std::shared_ptr<GameObject> checkCollisions(int x, int y)
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
	static CollisionManager& getInstance()
	{
		static CollisionManager instance;
		return instance;
	}
private:

};