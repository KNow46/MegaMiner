#pragma once
#include <iostream>
#include <vector>
#include "InterfaceObject.h"
#include "Block.h"
#include "Text.h"
#include <memory>

struct Item
{
	enum ItemType{GOLD, DIAMOND};
	Item(ItemType itemType)
	{
		this->itemType = itemType;

		if (itemType == GOLD)
		{
			value = 300;
			texturePath = "res/textures/gold.png";
		}
		if (itemType == DIAMOND)
		{
			value = 1000;
			texturePath = "res/textures/diamond.png";
		}
	};
	ItemType itemType;
	std::string texturePath;
	int value;
};

class Storage : public InterfaceObject
{
	int level;
	int maxOccupacy;
	int currentOccupacy;
	int slots;
	int occupatedSlots;
	std::vector<Item> items;
	std::vector<std::shared_ptr<Text>> amountCounters;
public:
	Storage();
	void upgrade();
	bool isStorageFull();
	void addItem(Item item);
	void erase();


};