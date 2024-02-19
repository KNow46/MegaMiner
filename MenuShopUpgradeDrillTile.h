#pragma once
#include "InterfaceObject.h"
#include "Text.h"
#include <memory>
class MenuShopUpgradeDrillTile : public InterfaceObject
{
	std::shared_ptr<InterfaceObject> confirmButton;
	std::shared_ptr<InterfaceObject> drillPhoto;
	std::shared_ptr<Text> upgradeInfo;
public:
	MenuShopUpgradeDrillTile();
	void onClick();
	void setIsVisible(bool isVisible);
	void upgradeWindowClear();
};