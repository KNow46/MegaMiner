#include "GasStationMenu.h"
#include "InterfaceManager.h"
#include "Button.h"
#include "World.h"
#include "Drill.h"
#include "FuelTank.h"
GasStationMenu::GasStationMenu() : InterfaceObject(300, 200, 900, 500, "res/textures/shopMenu/1.png"), price(5), totalPrice(0), maxToBuy(0)
{
   isVisible = false;

    slider = std::make_shared<Slider>(400, 250, 300, 70);
    aggregatedObjects.push_back(slider);

   buyButton = std::make_shared<Button>(450, 500, 200, 100, "res/textures/buy.png", "res/textures/buyHovered.png",
        [this]() 
       {
           int boughtAmount = totalPrice->getIntText() / price;
           InterfaceManager::getInstance().getFuelTank()->fillUp(boughtAmount);
           InterfaceManager::getInstance().getMoney()->takeMoney(boughtAmount * price);
       });
   aggregatedObjects.push_back(buyButton);

   totalPrice = std::make_shared<Text>(500, 400, 500, 500, "0", 20);
   aggregatedObjects.push_back(totalPrice);
    
   aggregatedObjects.push_back(std::make_shared<InterfaceObject>(850, 300, 180, 260, "res/textures/barrel.png"));
}
void GasStationMenu::update()
{
    int xPos = InterfaceManager::getInstance().getMouseXpos();
    int yPos = InterfaceManager::getInstance().getMouseYpos();

    for (const auto& gameObject : aggregatedObjects)
    {
        if (std::shared_ptr<InterfaceObject> interfaceObject = std::dynamic_pointer_cast<InterfaceObject>(gameObject))
        {

            interfaceObject->update();

            if (xPos > interfaceObject->getX() && xPos < interfaceObject->getX() + interfaceObject->getWidth() &&
                yPos > interfaceObject->getY() && yPos < interfaceObject->getY() + interfaceObject->getHeight())
            {
                interfaceObject->setIsHovered(true);
                interfaceObject->onHovered();

            }
            else
            {
                interfaceObject->setIsHovered(false);
            }
        }
    }
    totalPrice->changeText(std::to_string(int(slider->getHandlerPosition() * maxToBuy)));
    
}

void GasStationMenu::onClick()
{
    handleAggregatedObjectsOnClick();
}

void GasStationMenu::setIsVisible(bool isVisible)
{
    this->isVisible = isVisible;

    float handlerPosition = slider->getHandlerPosition();

    maxToBuy = (InterfaceManager::getInstance().getFuelTank()->getCapacity() - InterfaceManager::getInstance().getFuelTank()->getCurrentFuel()) * price;
    if (maxToBuy > InterfaceManager::getInstance().getMoney()->getMoneyAmount())
    {
        maxToBuy = InterfaceManager::getInstance().getMoney()->getMoneyAmount();
    }

    int tankCapacity = InterfaceManager::getInstance().getFuelTank()->getCapacity();

    totalPrice->changeText(std::to_string(int(handlerPosition * maxToBuy)));

}

