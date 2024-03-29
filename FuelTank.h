#pragma once
#include "InterfaceObject.h"
#include <memory>
class FuelTank : public InterfaceObject
{
private:
	float capacity;
	float currentFuel;
	int level;
	std::shared_ptr<InterfaceObject> fuelLevelImage;
	void onEmptyTank();
	int fuelLevelImgaeMaxWidth;
	bool isGamePaused;
public:
	FuelTank();
	int getLevel();
	float getCapacity();
	float getCapacity(int atLevel);
	void upgrade();
	int getUpgradeCost();
	void fillUp(float amount);
	void update();
	float getCurrentFuel();
	void reset();
	void setIsGamePaused(bool isPaused);
};