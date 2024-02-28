#include "GasStation.h"
#include "InterfaceManager.h"
#include "World.h"

#include <memory>

GasStation::GasStation(int x, int y, int width, int height) : GameObject(x, y, width, height, "res/textures/gasStation.png")
{

}

void GasStation::update()
{
	if (!text)
	{
		text = std::make_shared<Text>(400, 700, 800, 35, "Press tab to buy gas", 30);
		text->setIsVisible(false);
		InterfaceManager::getInstance().addObject(text);
	}
	if (isCollidingWithMachine())
	{
		text->setIsVisible(true);
		if (InterfaceManager::getInstance().getShopMenu()->getIsVisible())
		{
			text->changeText("Press tab to close");
		}
		else
		{
			text->changeText("Press tab to buy gas");
		}

	}
	else
	{
		text->setIsVisible(false);
		InterfaceManager::getInstance().getShopMenu()->setIsVisible(false);
	}
}

bool GasStation::isCollidingWithMachine()
{

	if (World::getInstance().getMachine()->getX() > x && World::getInstance().getMachine()->getX() < x + width)
	{
		if (World::getInstance().getMachine()->getY() > y && World::getInstance().getMachine()->getY() < y + height)
		{
			return true;
		}
	}
	return false;
}