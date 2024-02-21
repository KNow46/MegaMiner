#pragma once

#include "GameObject.h"
#include <map>
#include "Texture.h"
#include "Drill.h"
class Machine : public GameObject
{
public:
	enum State { STANDING, FLYING, FLYING_LEFT, FLYING_RIGHT, DRILLING_DOWN, DRILLING_LEFT, DRILLING_RIGHT, FALLING_DOWN, FALLING_LEFT, FALLING_RIGHT };

	Machine(int x, int y, int width, int height);

	double xSpeed = 8;
	double fallingYSpeed = 8;
	double fallingXSpeed = 8;
	double flyingYspeed = 8;
	double flyingXspeed = 8;

	virtual const Texture& getTexture();

	void setCurrentState(State state);

	State getCurrentState();

	void update();

	Drill &getDrill();

private:
	State currentState;
	Drill drill;


};