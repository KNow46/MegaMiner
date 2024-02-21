#pragma once

#include "InterfaceObject.h"
#include "Button.h"

#include <memory>

class ShopMenu : public InterfaceObject
{
	std::shared_ptr<Button> sellAllButton;
	std::shared_ptr<Button> upgradeDrillButton;
	std::shared_ptr<Button> upgradeDrillConfirm;

public:
	ShopMenu();
	virtual void update();
	void onClick();
	void setIsVisible(bool isVisible);
};