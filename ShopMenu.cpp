#include "ShopMenu.h"
#include "InterfaceManager.h"
#include "Button.h"
#include "World.h"
#include "Drill.h"
ShopMenu::ShopMenu() : InterfaceObject(300, 200, 900, 500, "res/textures/shopMenu/1.png")
{
    isVisible = false;
    


    sellAllButton = std::make_shared<Button>(400, 270, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png",
        []() {
            InterfaceManager::getInstance().getMoney()->addMoney(InterfaceManager::getInstance().getStorage()->getItemsValue());
            InterfaceManager::getInstance().getStorage()->erase(); 
        });
    aggregatedObjects.push_back(sellAllButton);
    aggregatedObjects.push_back(std::make_shared<Text>(405, 300, 400, 40, "Sell all resources", 18));

   

    upgradeDrillButton = std::make_shared<Button>(400, 370, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png",
        [this]()
        {
            upgradeDrillConfirm->setIsVisible(true);
        });
    aggregatedObjects.push_back(upgradeDrillButton);
    aggregatedObjects.push_back(std::make_shared<Text>(440, 400, 340, 40, "Upgrade drill", 18));
 

    upgradeDrillConfirm = std::make_shared<Button>(1030, 500, 50, 50, "res/textures/confirm.png",
        [this]()
        {
            
            if (InterfaceManager::getInstance().getMoney()->getMoneyAmount() >= World::getInstance().getMachine()->getDrill().getUpgradeCost())
            {
                InterfaceManager::getInstance().getMoney()->takeMoney(World::getInstance().getMachine()->getDrill().getUpgradeCost());
                World::getInstance().getMachine()->getDrill().upgrade();
                    
                Drill drill = World::getInstance().getMachine()->getDrill();
                std::cout << drill.getLevel() << std::endl;

                    upgradeDrillInfo->changeText("Cost " +
                        std::to_string(drill.getUpgradeCost()) + 
                        ";Power " +
                    std::to_string(drill.getPower()) + " to " +
                    std::to_string(drill.getPower(drill.getLevel() + 1))
                );
            }
        });
    upgradeDrillConfirm->setIsVisible(false);
    aggregatedObjects.push_back(upgradeDrillConfirm);

    Drill drill = World::getInstance().getMachine()->getDrill();

    upgradeDrillInfo = std::make_shared<Text>(830, 500, 500, 500, "Cost " +
        std::to_string(drill.getUpgradeCost()) +
        ";Power " + 
        std::to_string(drill.getPower()) + " to " +
        std::to_string(drill.getPower(drill.getLevel() + 1))
        , 15);
    aggregatedObjects.push_back(upgradeDrillInfo);
}
void ShopMenu::update()
{
    int xPos = InterfaceManager::getInstance().getMouseXpos();
    int yPos = InterfaceManager::getInstance().getMouseYpos();

    for (const auto& gameObject : aggregatedObjects)
    {
        if (std::shared_ptr<InterfaceObject> interfaceObject = std::dynamic_pointer_cast<InterfaceObject>(gameObject) )
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
            if (interfaceObject->getIsVisible())
            {
                if (xPos > interfaceObject->getX() && xPos < interfaceObject->getX() + interfaceObject->getWidth() &&
                    yPos > interfaceObject->getY() && yPos < interfaceObject->getY() + interfaceObject->getHeight())
                {
                    interfaceObject->onClick();
                }
            }
        }
    }
}

void ShopMenu::setIsVisible(bool isVisible)
{
    upgradeDrillConfirm->setIsVisible(false);
    this->isVisible = isVisible;
}