#pragma once

#include "InterfaceObject.h"
#include "MenuShopSellTile.h"
#include "MenuShopUpgradeDrillTile.h"
#include <memory>

class ShopMenu : public InterfaceObject
{
	std::shared_ptr<MenuShopSellTile> sellTile;
	std::shared_ptr< MenuShopUpgradeDrillTile> upgradeDrillTile;
public:
	ShopMenu();
	virtual void update();
	void onClick();
};