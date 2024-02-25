#pragma once
#include "InterfaceObject.h"
#include <memory>
class FuelTank : public InterfaceObject
{
private:
	float maxFuel;
	float currentFuel;
	int level;
	std::shared_ptr<InterfaceObject> fuelLevelImage;
	void onEmptyTank();
	int fuelLevelImgaeMaxWidth;
public:
	FuelTank();
	int getLevel();
	float getMaxFuel();
	float getMaxFuel(int atLevel);
	void upgrade();
	int getUpgradeCost();
	void fillUp(float amount);
	void update();
};