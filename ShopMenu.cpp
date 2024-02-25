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

    drillPhoto = std::make_shared<InterfaceObject>(850, 300, 180, 180, "res/textures/drill.png");
    aggregatedObjects.push_back(drillPhoto);
    drillPhoto->setIsVisible(false);

   storagePhoto = std::make_shared<InterfaceObject>(840, 300, 200, 150, "res/textures/storageUpgrade.png");
   aggregatedObjects.push_back(storagePhoto);
   storagePhoto->setIsVisible(false);


    upgradeDrillButton = std::make_shared<Button>(400, 370, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png",
        [this]()
        {
            Drill drill = World::getInstance().getMachine()->getDrill();
            upgradeInfo->changeText("  Cost: " +
                std::to_string(drill.getUpgradeCost()) +
                ";Power: " +
                std::to_string(drill.getPower()) + " -> " +
                std::to_string(drill.getPower(drill.getLevel() + 1)));

            upgradeConfirm->setIsVisible(true);
            upgradeInfo->setIsVisible(true);
            drillPhoto->setIsVisible(true);
            storagePhoto->setIsVisible(false);

            upgradeConfirm->setOnClickAction([this]()
                {

                    if (InterfaceManager::getInstance().getMoney()->getMoneyAmount() >= World::getInstance().getMachine()->getDrill().getUpgradeCost())
                    {
                        InterfaceManager::getInstance().getMoney()->takeMoney(World::getInstance().getMachine()->getDrill().getUpgradeCost());
                        World::getInstance().getMachine()->getDrill().upgrade();

                        Drill drill = World::getInstance().getMachine()->getDrill();
                        std::cout << drill.getLevel() << std::endl;

                        upgradeInfo->changeText("  Cost: " +
                            std::to_string(drill.getUpgradeCost()) +
                            ";Power: " +
                            std::to_string(drill.getPower()) + " -> " +
                            std::to_string(drill.getPower(drill.getLevel() + 1))
                        );
                    }
                });
        });
    aggregatedObjects.push_back(upgradeDrillButton);
    aggregatedObjects.push_back(std::make_shared<Text>(440, 400, 340, 40, "Upgrade drill", 18));

    upgradeStorageButton = std::make_shared<Button>(400, 470, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png",
        [this]()
        {
            std::shared_ptr<Storage> storage = InterfaceManager::getInstance().getStorage();

            upgradeInfo->changeText("  Cost: " +
                std::to_string(storage->getUpgradeCost()) +
                ";Capacity: " +
                std::to_string(storage->getCapacity()) + " -> " +
                std::to_string(storage->getCapacity(storage->getLevel() + 1)));

            upgradeConfirm->setIsVisible(true);
            upgradeInfo->setIsVisible(true);
            drillPhoto->setIsVisible(false);
            storagePhoto->setIsVisible(true);

            upgradeConfirm->setOnClickAction([this]() {
                if (InterfaceManager::getInstance().getMoney()->getMoneyAmount() >= InterfaceManager::getInstance().getStorage()->getUpgradeCost())
                {
                    InterfaceManager::getInstance().getMoney()->takeMoney(InterfaceManager::getInstance().getStorage()->getUpgradeCost());
                    InterfaceManager::getInstance().getStorage()->upgrade();

                    std::shared_ptr<Storage> storage = InterfaceManager::getInstance().getStorage();
                   

                    upgradeInfo->changeText("  Cost: " +
                        std::to_string(storage->getUpgradeCost()) +
                        ";Capacity: " +
                        std::to_string(storage->getCapacity()) + " -> " +
                        std::to_string(storage->getCapacity(storage->getLevel() + 1)));

                }

                });
        });
    aggregatedObjects.push_back(upgradeStorageButton);
    aggregatedObjects.push_back(std::make_shared<Text>(430, 500, 340, 40, "Upgrade storage", 18));

    upgradeConfirm = std::make_shared<Button>(900, 600, 100, 50, "res/textures/upgrade.png", "res/textures/upgradeHovered.png",
        [this]()
        {
            
            if (InterfaceManager::getInstance().getMoney()->getMoneyAmount() >= World::getInstance().getMachine()->getDrill().getUpgradeCost())
            {
                InterfaceManager::getInstance().getMoney()->takeMoney(World::getInstance().getMachine()->getDrill().getUpgradeCost());
                World::getInstance().getMachine()->getDrill().upgrade();
                    
                Drill drill = World::getInstance().getMachine()->getDrill();
                std::cout << drill.getLevel() << std::endl;

                    upgradeInfo->changeText("  Cost: " +
                        std::to_string(drill.getUpgradeCost()) + 
                        ";Power: " +
                    std::to_string(drill.getPower()) + " -> " +
                    std::to_string(drill.getPower(drill.getLevel() + 1))
                );
            }
        });
    upgradeConfirm->setIsVisible(false);
    aggregatedObjects.push_back(upgradeConfirm);

    Drill drill = World::getInstance().getMachine()->getDrill();

    upgradeInfo = std::make_shared<Text>(830, 500, 500, 500, "  Cost: " +
        std::to_string(drill.getUpgradeCost()) +
        ";Power: " + 
        std::to_string(drill.getPower()) + " -> " +
        std::to_string(drill.getPower(drill.getLevel() + 1))
        , 15);
    aggregatedObjects.push_back(upgradeInfo);
    upgradeInfo->setIsVisible(false);
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
    upgradeConfirm->setIsVisible(false);
    upgradeInfo->setIsVisible(false);
    drillPhoto->setIsVisible(false);
    storagePhoto->setIsVisible(false);

    this->isVisible = isVisible;
}