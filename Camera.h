#pragma once

class Camera
{
private:
	int x;
	int y;
	int xPosAtScreen;
	int yPosAtScreen;
	int xRange;
	int yRange;
	bool isOn;
public:
	Camera(int x, int y, int xPosAtScreen, int yPosAtScreen, int xRange, int yRange);

	int getX();
	int getY();
	int getXrange();
	int getYrange();
	int getXposAtScreen();
	int getYposAtScreen();
	bool getIsOn();

	void setX(int x);
	void setY(int y);
	void setXrange(int xRange);
	void setYrange(int yRange);
	void setIsOn(bool isOn);
	void setXposAtScreen(int x);
	void setYposAtScreen(int x);

};