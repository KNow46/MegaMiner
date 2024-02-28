#pragma once

#include "InterfaceObject.h"
#include "Button.h"
#include "Text.h"
#include "Slider.h"
#include <memory>

class GasStationMenu : public InterfaceObject
{
	std::shared_ptr<Slider> slider;
	std::shared_ptr<Button> buyButton;
	std::shared_ptr<Text> totalPrice;
	int price;
	int maxToBuy;
public:
	GasStationMenu();
	void update();
	void onClick();

	void setIsVisible(bool isVisible);
};