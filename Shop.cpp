#include "Shop.h"
#include "InterfaceManager.h"
#include "World.h"

#include <memory>

Shop::Shop(int x, int y, int width, int height): GameObject(x,y,width,height, "res/textures/shop.png")
{
	text = std::make_shared<Text>(400, 800, 800, 35, "Press tab to open shop", 30);
	text->setIsVisible(false);
	textId = text->getId();
	InterfaceManager::getInstance().addObject(text);
}

void Shop::update()
{
	if (isCollidingWithMachine())
	{
		text->setIsVisible(true);
		
	}
	else
	{
		std::cout << "lalal";
		text->setIsVisible(false);
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