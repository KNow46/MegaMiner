#pragma once

#include "InterfaceObject.h"
#include "MenuShopSellTile.h"
#include <memory>

class ShopMenu : public InterfaceObject
{
	std::shared_ptr<MenuShopSellTile> sellTile;
public:
	ShopMenu();
	virtual void update();
	void onClick();
};