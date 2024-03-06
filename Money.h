#pragma once
#include "InterfaceObject.h"
#include "Texture.h"
#include "Text.h"
#include <memory>
class Money: public InterfaceObject
{
	int money;
	int counter = 0;
	std::shared_ptr<Text>amountText;
	int totalAccumulatedMoney = 0;
	
public:
	
	Money();
	int getMoneyAmount();
	void addMoney(int amount);
	void takeMoney(int amount);
	void update();
	Texture& getTexture();
	int getTotalAccumulatedMoney();
	void reset();
};