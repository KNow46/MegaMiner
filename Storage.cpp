#include "Storage.h"
#include <memory>
#include <iostream>
#include "Text.h"

Storage::Storage() : InterfaceObject(1200, 30, 175, 620, "res/textures/storage.png"), level(1), capacity(5), slots(8),
currentOccupacy(0), occupatedSlots(0)
{
	
	for(int i = 0; i < slots; i++)
	{
		std::shared_ptr<Text> text = std::make_shared<Text>(1200, 80 + i*70, 50, 50, "0", 15);
		aggregatedObjects.emplace_back(text);
		amountCounters.emplace_back(text);
	}
	currentOccupacyText = std::make_shared<Text>(1250, 32, 50, 50, "0", 15);
	aggregatedObjects.emplace_back(currentOccupacyText);

	capacityText = std::make_shared<Text>(1290, 32, 200, 50, "/" + std::to_string(capacity), 15);
	aggregatedObjects.emplace_back(capacityText);
}
void Storage::addItem(Item item)
{
	int itemIndex = -1;
	for (int i = 0; i < occupatedSlots; i++)
	{

		if (items[i].itemType == item.itemType)
		{
			itemIndex = i;
			break;
		}
	}
	if(currentOccupacy < capacity)
	{
		if(itemIndex == -1)
		{
			items.emplace_back(item);
			aggregatedObjects.emplace_back(new GameObject(1262, 70 + (items.size() - 1) * 70, 70, 70, item.texturePath));
			amountCounters[occupatedSlots]->changeText("1");
			occupatedSlots++;
			currentOccupacy++;
			
		}
		else
		{
			int currAmount = amountCounters[itemIndex]->getIntText();
			
			amountCounters[itemIndex]->changeText(std::to_string(currAmount + 1));
			currentOccupacy++;
		}
		currentOccupacyText->changeText(std::to_string(currentOccupacy));
	}
}
int Storage::getItemsValue()
{
	int valueSum = 0;

	for (int i = 0; i < occupatedSlots; i++)
	{
		valueSum += items[i].value * amountCounters[i]->getIntText();
	}

	return valueSum;
}
void Storage::reset()
{
	level = 1;
	capacity = getCapacity(level);
	erase();
}
void Storage::erase()
{

	currentOccupacy = 0;
	aggregatedObjects.clear();
	amountCounters.clear();
	items.clear();
	occupatedSlots = 0;

	capacityText = std::make_shared<Text>(1290, 32, 200, 50, "/" + std::to_string(capacity), 15);
	aggregatedObjects.emplace_back(capacityText);
	for (int i = 0; i < slots; i++)
	{
		std::shared_ptr<Text> text = std::make_shared<Text>(1200, 80 + i * 70, 200, 50, "0", 15);
		aggregatedObjects.emplace_back(text);
		amountCounters.emplace_back(text);
	}
	currentOccupacyText = std::make_shared<Text>(1250, 32, 50, 50, "0", 15);
	aggregatedObjects.emplace_back(currentOccupacyText);

}
int Storage::getCapacity(int atLevel)
{
	if (atLevel == 1)
		return 5;
	if (atLevel == 2)
		return 10;
	if (atLevel == 3)
		return 15;
	if (atLevel == 4)
		return 20;
	if (atLevel == 5)
		return 25;
}
int Storage::getCapacity()
{
	return capacity;
}
int Storage::getUpgradeCost()
{
	if (level == 1)
		return 500;
	if (level == 2)
		return 1000;
	if (level == 3)
		return 2000;
	if (level == 4)
		return 5000;
	return 99999999;
}
void Storage::upgrade()
{
	level++;
	capacity = getCapacity(level);
	capacityText->changeText("/" + std::to_string(capacity));
}
int Storage::getLevel()
{
	return level;
}