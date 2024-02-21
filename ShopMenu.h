#pragma once

#include "InterfaceObject.h"
#include "Button.h"
#include "Text.h"
#include <memory>

class ShopMenu : public InterfaceObject
{
	std::shared_ptr<Button> sellAllButton;
	std::shared_ptr<Button> upgradeDrillButton;
	std::shared_ptr<Button> upgradeDrillConfirm;
	std::shared_ptr<Text> upgradeDrillInfo;

public:
	ShopMenu();
	virtual void update();
	void onClick();
	void setIsVisible(bool isVisible);
};