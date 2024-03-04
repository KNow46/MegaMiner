#include "Shop.h"
#include "InterfaceManager.h"
#include "World.h"

#include <memory>

Shop::Shop(int x, int y, int width, int height): GameObject(x,y,width,height, "res/textures/shop.png")
{

}

void Shop::update()
{
	static int optimizationCounter = 0;
	if (optimizationCounter < 10)
	{
		optimizationCounter++;
		return;
	}
	else
	{
		optimizationCounter = 0;
	}

	if (!text)
	{
		text = std::make_shared<Text>(400, 750, 800, 35, "Press tab to open shop", 30);
		text->setIsVisible(false);
		InterfaceManager::getInstance().addObject(text);
	}
	if (isCollidingWithMachine())
	{
		text->setIsVisible(true);
		if (InterfaceManager::getInstance().getShopMenu()->getIsVisible())
		{
			text->changeText("Press tab to close shop");
		}
		else
		{
			text->changeText("Press tab to open shop");
		}
		
	}
	else
	{
		text->setIsVisible(false);
		InterfaceManager::getInstance().getShopMenu()->setIsVisible(false);
	}
}

bool Shop::isCollidingWithMachine()
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