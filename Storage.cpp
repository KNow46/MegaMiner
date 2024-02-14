#include "Storage.h"
#include <memory>
#include <iostream>
#include "Text.h"

Storage::Storage() : InterfaceObject(1200, 50, 130, 600, "res/textures/storage.png"), level(1), maxOccupacy(100), slots(8),
currentOccupacy(0), occupatedSlots(0)
{
	
	for(int i = 0; i < slots; i++)
	{
		std::shared_ptr<Text> text = std::make_shared<Text>(1200, 80 + i*70, 50, 50, "0", 15);
		text->setDescription("storageAmountCounterSlot" + std::to_string(i));
		aggregatedObjects.emplace_back(text);
		amountCounters.emplace_back(text);
	}
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
			aggregatedObjects.emplace_back(new GameObject(1230, 70 + (items.size() - 1) * 70, 70, 70, item.texturePath, "item"));
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
	}
}
