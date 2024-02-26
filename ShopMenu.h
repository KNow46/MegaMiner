#pragma once

#include "InterfaceObject.h"
#include "Button.h"
#include "Text.h"
#include <memory>

class ShopMenu : public InterfaceObject
{
	std::shared_ptr<Button> sellAllButton;
	std::shared_ptr<Button> upgradeDrillButton;
	std::shared_ptr<Button> upgradeStorageButton;
	std::shared_ptr<Button> upgradeFuelTankButton;

	std::shared_ptr<Button> upgradeConfirm;

	std::shared_ptr<Text> upgradeInfo;

	std::shared_ptr<InterfaceObject> drillPhoto;
	std::shared_ptr<InterfaceObject> storagePhoto;
	std::shared_ptr<InterfaceObject> fuelTankPhoto;
public:
	ShopMenu();
	virtual void update();
	void onClick();
	void setIsVisible(bool isVisible);
};