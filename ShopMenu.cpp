#include "ShopMenu.h"
#include "InterfaceManager.h"
#include "Button.h"

ShopMenu::ShopMenu() : InterfaceObject(300, 200, 900, 500, "res/textures/shopMenu/1.png")
{
    isVisible = false;
    

    sellAllButton = std::make_shared<Button>(400, 270, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png",
        []() {
            InterfaceManager::getInstance().getMoney()->addMoney(InterfaceManager::getInstance().getStorage()->getItemsValue());
            InterfaceManager::getInstance().getStorage()->erase(); 
        });
    sellAllButton->getAggregatedObjects().push_back(std::make_shared<Text>(405, 300, 400, 40, "Sell all resources", 18));

    aggregatedObjects.push_back(sellAllButton);

    upgradeDrillButton = std::make_shared<Button>(400, 370, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png",
        []()
        {

        });
    aggregatedObjects.push_back(upgradeDrillButton);
    upgradeDrillButton->getAggregatedObjects().push_back(std::make_shared<Text>(440, 400, 340, 40, "Upgrade drill", 18));
 


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

void ShopMenu::setIsVisible(bool isVisible)
{
    this->isVisible = isVisible;
}