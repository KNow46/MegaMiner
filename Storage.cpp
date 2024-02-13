#include "Storage.h"
Storage::Storage() : InterfaceObject(1200, 50, 130, 600, "res/textures/storage.png"), level(1), maxOccupacy(100), slots(8),
currentOccupacy(0), occupatedSlots(0)
{
}
void Storage::addItem(Item item)
{
	if(currentOccupacy < maxOccupacy)
	{
		items.emplace_back(item);
		aggregatedObjects.emplace_back(new GameObject(1230, 70 + (items.size() - 1) * 70, 70, 70, item.texturePath));
	}
}
