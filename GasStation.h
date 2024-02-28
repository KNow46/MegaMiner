#pragma once
#include "GameObject.h"
#include "Text.h"
#include <memory>

class GasStation : public GameObject
{
public:
	GasStation(int x, int y, int width, int height);
	void update();
	bool isCollidingWithMachine();
private:

	std::shared_ptr<Text> text;


};