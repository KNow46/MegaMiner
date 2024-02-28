#pragma once
#include "InterfaceObject.h"
#include <memory>
class Slider : public InterfaceObject
{
public:
	Slider(int x, int y, int width, int height);
	void update();
	void onClick();
	float getHandlerPosition();
private:
	bool isHandlerGrabbed;
	std::shared_ptr<InterfaceObject> handler;
;
};