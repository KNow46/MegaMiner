#pragma once
#include "FuelTank.h"
#include "Global.h"
#include "World.h"
#include "InterfaceManager.h"
#include "GameOverScreen.h"

void FuelTank::onEmptyTank()
{
	InterfaceManager::getInstance().addObject(std::make_shared<GameOverScreen>());
	currentFuel = INT_MAX;
}

FuelTank::FuelTank() :InterfaceObject(50, windowHeight - 150, 555, 130, "res/textures/fuelTank.png"), 
capacity(100), currentFuel(100), level(1), fuelLevelImgaeMaxWidth(450), isGamePaused(false)
{
	fuelLevelImage = std::make_shared<InterfaceObject>(145, windowHeight - 85, fuelLevelImgaeMaxWidth, 54, "res/textures/fuelLevel.png");
	aggregatedObjects.push_back(fuelLevelImage);
}
int FuelTank::getLevel()
{
	return level;
}
float FuelTank::getCapacity()
{
	
	return capacity;
}
float FuelTank::getCapacity(int atLevel)
{
	
	return atLevel * 100;

}
void FuelTank::upgrade()
{
	level++;
	capacity = getCapacity(level);
}

int FuelTank::getUpgradeCost()
{
	return level * 500;
}

void FuelTank::fillUp(float amount)
{
	currentFuel += amount;
}

void FuelTank::update()
{
	if(!isGamePaused)
	{
		if (currentFuel > 0)
		{
			currentFuel -= 0.05;
			fuelLevelImage->setWidth(fuelLevelImgaeMaxWidth * currentFuel / capacity);
		}
		else
		{
			onEmptyTank();
		}
	}
}

float FuelTank::getCurrentFuel()
{
	return currentFuel;
}

void FuelTank::reset()
{
	level = 1;
	capacity = getCapacity(level);
	currentFuel = capacity;
}

void FuelTank::setIsGamePaused(bool isPaused)
{
	isGamePaused = isPaused;
}
