#pragma once

#include "InterfaceObject.h"
#include "Button.h"

#include <memory>

class ShopMenu : public InterfaceObject
{
	std::shared_ptr<Button> sellAllButton;
	std::shared_ptr<Button> upgradeDrillButton;

public:
	ShopMenu();
	virtual void update();
	void onClick();
	void setIsVisible(bool isVisible);
};