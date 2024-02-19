#include "Storage.h"
#include <memory>
#include <iostream>
#include "Text.h"

Storage::Storage() : InterfaceObject(1200, 30, 175, 620, "res/textures/storage.png"), level(1), maxOccupacy(100), slots(8),
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

	maxOccupacyText = std::make_shared<Text>(1290, 32, 200, 50, "/" + std::to_string(maxOccupacy), 15);
	aggregatedObjects.emplace_back(maxOccupacyText);
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
	if(currentOccupacy < maxOccupacy)
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
	for (const auto& item : items)
	{
		valueSum += item.value;
	}
	return valueSum;
}
void Storage::erase()
{

	currentOccupacy = 0;
	aggregatedObjects.clear();
	amountCounters.clear();
	items.clear();
	occupatedSlots = 0;

	maxOccupacyText = std::make_shared<Text>(1290, 32, 200, 50, "/" + std::to_string(maxOccupacy), 15);
	aggregatedObjects.emplace_back(maxOccupacyText);
	for (int i = 0; i < slots; i++)
	{
		std::shared_ptr<Text> text = std::make_shared<Text>(1200, 80 + i * 70, 200, 50, "0", 15);
		aggregatedObjects.emplace_back(text);
		amountCounters.emplace_back(text);
	}
	currentOccupacyText = std::make_shared<Text>(1250, 32, 50, 50, "0", 15);
	aggregatedObjects.emplace_back(currentOccupacyText);

}
