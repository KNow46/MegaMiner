#pragma once
#include "GameObject.h"
#include <vector>

class CollisionManager
{
private:
	std::vector<std::shared_ptr<GameObject>> gameObjects;
public:
	void checkCollisions()
	{
		for (int i = 0; i < gameObjects.size() - 1; i++)
		{
			for (int j = i + 1; j < gameObjects.size(); i++)
			{
				//if(gameObjects[i]->getX)
			}
		}
	}
};