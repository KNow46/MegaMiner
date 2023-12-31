#pragma once

#include "GameObject.h"
#include <map>
#include "Texture.h"

class Machine : public GameObject
{
public:
	enum State { STANDING, FLYING, FLYING_LEFT, FLYING_RIGHT, DRILLING_DOWN, DRILLING_LEFT, DRILLING_RIGHT, FALLING_DOWN, FALLING_LEFT, FALLING_RIGHT };

	Machine(int x, int y, int width, int height);

	double xSpeed = 2;
	double fallingYSpeed = 2;
	double fallingXSpeed = 2;
	double flyingYspeed = 2;
	double flyingXspeed = 2;

	virtual const Texture& getTexture();

	void setCurrentState(State state);

	State getCurrentState();

	void update();


private:
	State currentState;


};