#pragma once
#include "GameObject.h"
#include "Text.h"

class Shop : public GameObject
{
public:
	Shop(int x, int y, int width, int height);
	void update();
	bool isCollidingWithMachine();
private:
	int textId;
	std::shared_ptr<Text> text;


};