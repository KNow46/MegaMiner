#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>

class Camera
{
private:
	int x;
	int y;
	int xOffset;
	int yOffset;
	int xRange;
	int yRange;
	bool isOn;
public:
	Camera(int x, int y, int xOffset, int yOffSet, int xRange, int yRange);

	int getX();
	int getY();
	int getXrange();
	int getYrange();
	int getXoffset();
	int getYoffset();
	bool getIsOn();

	void setX(int x);
	void setY(int y);
	void setXrange(int xRange);
	void setYrange(int yRange);
	void setIsOn(bool isOn);
	void setXOffset(int x);
	void setYOffset(int y);
	void followObject(std::shared_ptr<GameObject>);

};