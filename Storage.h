#pragma once
#include <iostream>
#include <vector>
#include "InterfaceObject.h"
#include "Block.h"

struct Item
{
	enum ItemType{GOLD};
	Item(ItemType itemType)
	{
		this->itemType = itemType;

		if (itemType == GOLD)
		{
			value = 300;
			texturePath = "res/textures/gold.png";
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
public:
	Storage();
	void upgrade();
	bool isStorageFull();
	void addItem(Item item);
	void erase();


};