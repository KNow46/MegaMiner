#pragma once
#include "Gameobject.h"

class TestObject : public GameObject
{
public:
	
	TestObject(int x, int y, int width, int height, std::string texturePath)
		:GameObject(x, y ,width, height, texturePath)
	{
		aggregatedObjects.emplace_back(std::make_shared<GameObject>(200, 200, 200, 200, "res/textures/board.png"));
	}

};