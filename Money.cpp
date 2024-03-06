#include "Money.h"
#include "TextureManager.h"
#include <iostream>
#include "InterfaceManager.h"
Money::Money() : InterfaceObject(30, 0, 100, 100, "res/textures/coin/1.png"), money(0)
{
	amountText = std::make_shared<Text>(140, 20, 500, 35, std::to_string(money), 30);


	aggregatedObjects.emplace_back(amountText);
	//InterfaceManager::getInstance().addObject(amountText);
}


void Money::addMoney(int amount)
{
	money += amount;
	amountText->changeText(std::to_string(money));
	totalAccumulatedMoney += amount;
}
void Money::takeMoney(int amount)
{
	money -= amount;
	amountText->changeText(std::to_string(money));
}
int Money::getMoneyAmount()
{
	return money;
}
void Money::update()
{

}
Texture& Money::getTexture()
{
	counter++;
	if (counter < 7)
	{
		return TextureManager::getInstance().getTexture("res/textures/coin/1.png");
	}
	else if (counter < 14)
	{
		return TextureManager::getInstance().getTexture("res/textures/coin/2.png");
	}
	else if (counter < 21)
	{
		return TextureManager::getInstance().getTexture("res/textures/coin/3.png");
	}
	else if (counter < 28)
	{
		return TextureManager::getInstance().getTexture("res/textures/coin/4.png");
	}
	else if (counter < 35)
	{
		return TextureManager::getInstance().getTexture("res/textures/coin/5.png");
	}
	else if (counter < 42)
	{
		return TextureManager::getInstance().getTexture("res/textures/coin/6.png");
	}
	else
	{
		counter = 0;
		return TextureManager::getInstance().getTexture("res/textures/coin/1.png");
	}

}

int Money::getTotalAccumulatedMoney()
{
	return totalAccumulatedMoney;
}

void Money::reset()
{
	money = 0;
	amountText->changeText(std::to_string(money));
	totalAccumulatedMoney = 0;
}
