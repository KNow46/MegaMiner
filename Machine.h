#pragma once

#include "GameObject.h"
#include <map>
#include "Texture.h"

class Machine : public GameObject
{
public:
	enum State { STANDING, FLYING, DRILLING_DOWN, DRILLING_LEFT, DRILLING_RIGHT };

	Machine(int x, int y, int width, int height);

	virtual const Texture& getTexture();

	void setCurrentState(State state);

	State getCurrentState();


private:
	State currentState;


};