#pragma once
#include "MenuShopUpgradeDrillTile.h"
#include "InterfaceManager.h"
#include "Text.h"
MenuShopUpgradeDrillTile::MenuShopUpgradeDrillTile() :InterfaceObject(400, 370, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png")
{
	aggregatedObjects.push_back(std::make_shared<Text>(460, 400, 340, 40, "Upgrade drill", 18));

	confirmButton = std::make_shared<InterfaceObject>(1030, 520, 50, 50, "res/textures/confirm.png");
	confirmButton->setIsVisible(false);
	aggregatedObjects.push_back(confirmButton);

	upgradeInfo = std::make_shared<Text>(700, 350, 1500, 500, "nanananan opis przedmiotu;kolejna linijka opisu; i jeszcze kolejna", 20);
	aggregatedObjects.push_back(upgradeInfo);

}
void MenuShopUpgradeDrillTile::onClick()
{
	confirmButton->setIsVisible(true);
}
void MenuShopUpgradeDrillTile::setIsVisible(bool isVisible)
{
	this->isVisible = isVisible;
	if (!isVisible)
	{
		confirmButton->setIsVisible(false);
	}
}
void MenuShopUpgradeDrillTile::upgradeWindowClear()
{
	confirmButton->setIsVisible(false);
}