#pragma once

#include "GameObject.h"
#include <map>
#include "Texture.h"
#include "Drill.h"
#include "Animation.h"
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
	
	void setIsGamePaused(bool isPaused);

	Drill &getDrill();

private:
	State currentState;
	Drill drill;
	Animation drilllingRightAnimation;
	Animation drilllingLeftAnimation;
	Animation drilllingDownAnimation;
	Animation drilllingDownLeftAnimation;
	Animation flyingRightAnimation;
	Animation flyingLeftAnimation;
	bool isFacingRight;
	bool isGamePaused; 

	void move();
};