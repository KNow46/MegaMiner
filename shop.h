#pragma once
#include "GameObject.h"

class Shop : public GameObject
{
public:
	Shop(int x, int y, int width, int height);
	void update();

};