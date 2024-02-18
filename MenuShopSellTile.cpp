#pragma once
#include "MenuShopSellTile.h"
#include "InterfaceManager.h"
#include "Text.h"
MenuShopSellTile::MenuShopSellTile() :InterfaceObject(400, 270, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png")
{
	aggregatedObjects.push_back(std::make_shared<Text>(410, 305, 340, 40, "Sell all resources", 18));
}
void MenuShopSellTile::onClick()
{
	InterfaceManager::getInstance().getMoney()->addMoney(InterfaceManager::getInstance().getStorage()->getItemsValue());
	InterfaceManager::getInstance().getStorage()->erase();
}