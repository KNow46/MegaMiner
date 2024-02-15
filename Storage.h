#pragma once
#include <iostream>
#include <vector>
#include "InterfaceObject.h"
#include "Block.h"
#include "Text.h"
#include <memory>

struct Item
{
	enum ItemType{GOLD, DIAMOND, EMERALD, IRON, MYSTIC};
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
			value = 3000;
			texturePath = "res/textures/diamond.png";
		}
		if (itemType == IRON)
		{
			value = 1000;
			texturePath = "res/textures/iron.png";
		}
		if (itemType == EMERALD)
		{
			value = 100;
			texturePath = "res/textures/emerald.png";
		}
		if (itemType == MYSTIC)
		{
			value = 10000;
			texturePath = "res/textures/mystic.png";
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
	std::shared_ptr<Text> maxOccupacyText;
	std::shared_ptr<Text> currentOccupacyText;
public:
	Storage();
	void upgrade();
	bool isStorageFull();
	void addItem(Item item);
	void erase();


};