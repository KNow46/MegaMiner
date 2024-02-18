#include "ShopMenu.h"
#include "InterfaceManager.h"

ShopMenu::ShopMenu() : InterfaceObject(300, 200, 900, 500, "res/textures/shopMenu/1.png")
{
    isVisible = false;
    
    sellTile = std::make_shared<MenuShopSellTile>();
    aggregatedObjects.push_back(sellTile);
}
void ShopMenu::update()
{
    int xPos = InterfaceManager::getInstance().getMouseXpos();
    int yPos = InterfaceManager::getInstance().getMouseYpos();

    for (const auto& gameObject : aggregatedObjects)
    {
        if (std::shared_ptr<InterfaceObject> interfaceObject = std::dynamic_pointer_cast<InterfaceObject>(gameObject))
        {
            
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
}

void ShopMenu::onClick()
{
    int xPos = InterfaceManager::getInstance().getMouseXpos();
    int yPos = InterfaceManager::getInstance().getMouseYpos();

    for (const auto& gameObject : aggregatedObjects)
    {
        if (std::shared_ptr<InterfaceObject> interfaceObject = std::dynamic_pointer_cast<InterfaceObject>(gameObject))
        {
            if (xPos > interfaceObject->getX() && xPos < interfaceObject->getX() + interfaceObject->getWidth() &&
                yPos > interfaceObject->getY() && yPos < interfaceObject->getY() + interfaceObject->getHeight())
            {
                interfaceObject->onClick();
            }
        }
    }
}