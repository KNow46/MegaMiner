#include "ShopMenu.h"
#include "InterfaceManager.h"
#include "Button.h"
#include "World.h"
#include "Drill.h"
#include "FuelTank.h"
ShopMenu::ShopMenu() : InterfaceObject(300, 200, 900, 500, "res/textures/shopMenu/1.png")
{
    isVisible = false;
    
    sellAllButton = std::make_shared<Button>(400, 250, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png",
        []() {
            InterfaceManager::getInstance().getMoney()->addMoney(InterfaceManager::getInstance().getStorage()->getItemsValue());
            InterfaceManager::getInstance().getStorage()->erase(); 
        });

    aggregatedObjects.push_back(sellAllButton);
    aggregatedObjects.push_back(std::make_shared<Text>(405, 280, 400, 40, "Sell all resources", 18));

    drillPhoto = std::make_shared<InterfaceObject>(850, 300, 180, 180, "res/textures/drill.png");
    aggregatedObjects.push_back(drillPhoto);
    drillPhoto->setIsVisible(false);

   storagePhoto = std::make_shared<InterfaceObject>(840, 300, 200, 150, "res/textures/storageUpgrade.png");
   aggregatedObjects.push_back(storagePhoto);
   storagePhoto->setIsVisible(false);

   fuelTankPhoto = std::make_shared<InterfaceObject>(870, 300, 150, 150, "res/textures/FuelTankOnly.png");
   aggregatedObjects.push_back(fuelTankPhoto);
   fuelTankPhoto->setIsVisible(false);

    createDrillButton();
    createStorageButton();
    createFuelTankButton();


    upgradeConfirm = std::make_shared<Button>(900, 600, 100, 50, "res/textures/upgrade.png", "res/textures/upgradeHovered.png",
        [this](){});
    upgradeConfirm->setIsVisible(false);
    aggregatedObjects.push_back(upgradeConfirm);

    upgradeInfo = std::make_shared<Text>(830, 470, 500, 500,"", 18);
    aggregatedObjects.push_back(upgradeInfo);
    upgradeInfo->setIsVisible(false);
}
void ShopMenu::update()
{
    handleAggregatedObjectsHover();
}

void ShopMenu::onClick()
{
    handleAggregatedObjectsOnClick();
}

void ShopMenu::setIsVisible(bool isVisible)
{
    upgradeConfirm->setIsVisible(false);
    upgradeInfo->setIsVisible(false);
    setPhotosVisibilityFalse();

    this->isVisible = isVisible;
}

void ShopMenu::createStorageButton()
{
    upgradeStorageButton = std::make_shared<Button>(400, 450, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png",
        [this]()
        {
            std::shared_ptr<Storage> storage = InterfaceManager::getInstance().getStorage();

            upgradeInfo->changeText("  Cost: " +
                std::to_string(storage->getUpgradeCost()) +
                ";  Capacity:;   " +
                std::to_string(storage->getCapacity()) + " -> " +
                std::to_string(storage->getCapacity(storage->getLevel() + 1)));

            upgradeConfirm->setIsVisible(true);
            upgradeInfo->setIsVisible(true);
            setPhotosVisibilityFalse();
            storagePhoto->setIsVisible(true);

            upgradeConfirm->setOnClickAction([this, storage]() {
                if (InterfaceManager::getInstance().getMoney()->getMoneyAmount() >= InterfaceManager::getInstance().getStorage()->getUpgradeCost())
                {
                    InterfaceManager::getInstance().getMoney()->takeMoney(InterfaceManager::getInstance().getStorage()->getUpgradeCost());
                    InterfaceManager::getInstance().getStorage()->upgrade();




                    upgradeInfo->changeText("  Cost: " +
                        std::to_string(storage->getUpgradeCost()) +
                        ";  Capacity:;   " +
                        std::to_string(storage->getCapacity()) + " -> " +
                        std::to_string(storage->getCapacity(storage->getLevel() + 1)));

                }

                });
        });
    aggregatedObjects.push_back(upgradeStorageButton);
    aggregatedObjects.push_back(std::make_shared<Text>(430, 480, 340, 40, "Upgrade storage", 18));
}
void ShopMenu::createDrillButton()
{
    upgradeDrillButton = std::make_shared<Button>(400, 350, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png",
        [this]()
        {
            Drill drill = World::getInstance().getMachine()->getDrill();
            upgradeInfo->changeText(";  Cost: " +
                std::to_string(drill.getUpgradeCost()) +
                ";Power: " +
                std::to_string(drill.getPower()) + " -> " +
                std::to_string(drill.getPower(drill.getLevel() + 1)));

            upgradeConfirm->setIsVisible(true);
            upgradeInfo->setIsVisible(true);
            setPhotosVisibilityFalse();
            drillPhoto->setIsVisible(true);

            upgradeConfirm->setOnClickAction([this, drill]()
                {

                    if (InterfaceManager::getInstance().getMoney()->getMoneyAmount() >= World::getInstance().getMachine()->getDrill().getUpgradeCost())
                    {
                        InterfaceManager::getInstance().getMoney()->takeMoney(World::getInstance().getMachine()->getDrill().getUpgradeCost());
                        World::getInstance().getMachine()->getDrill().upgrade();

                        Drill drill = World::getInstance().getMachine()->getDrill();


                        upgradeInfo->changeText(";  Cost: " +
                            std::to_string(drill.getUpgradeCost()) +
                            ";Power: " +
                            std::to_string(drill.getPower()) + " -> " +
                            std::to_string(drill.getPower(drill.getLevel() + 1))
                        );
                    }
                });
        });
    aggregatedObjects.push_back(upgradeDrillButton);
    aggregatedObjects.push_back(std::make_shared<Text>(440, 380, 340, 40, "Upgrade drill", 18));
}
void ShopMenu::createFuelTankButton()
{
    upgradeFuelTankButton = std::make_shared<Button>(400, 550, 350, 90, "res/textures/shopMenu/menuTile.png", "res/textures/shopMenu/menuTileHovered.png",
        [this]()
        {
            std::shared_ptr<FuelTank> fuelTank = InterfaceManager::getInstance().getFuelTank();

            std::cout << fuelTank->getCapacity() << std::endl;

            upgradeInfo->changeText("  Cost: " +
                std::to_string(fuelTank->getUpgradeCost()) +
                ";  Capacity:; " +
                std::to_string(int(fuelTank->getCapacity())) + " -> " +
                std::to_string(int(fuelTank->getCapacity(fuelTank->getLevel() + 1))));

            upgradeConfirm->setIsVisible(true);
            upgradeInfo->setIsVisible(true);
            setPhotosVisibilityFalse();
            fuelTankPhoto->setIsVisible(true);

            upgradeConfirm->setOnClickAction([this, fuelTank]() {
                if (InterfaceManager::getInstance().getMoney()->getMoneyAmount() >= InterfaceManager::getInstance().getFuelTank()->getUpgradeCost())
                {
                    InterfaceManager::getInstance().getMoney()->takeMoney(InterfaceManager::getInstance().getFuelTank()->getUpgradeCost());
                    InterfaceManager::getInstance().getFuelTank()->upgrade();

                    upgradeInfo->changeText("  Cost: " +
                        std::to_string(fuelTank->getUpgradeCost()) +
                        ";  Capacity:; " +
                        std::to_string(int(fuelTank->getCapacity())) + " -> " +
                        std::to_string(int(fuelTank->getCapacity(fuelTank->getLevel() + 1))));
                    std::cout << fuelTank->getCapacity() << std::endl;
                }

                });
        });
    aggregatedObjects.push_back(upgradeFuelTankButton);
    aggregatedObjects.push_back(std::make_shared<Text>(400, 580, 340, 40, "Upgrade fuel tank", 18));
}
void ShopMenu::setPhotosVisibilityFalse()
{
    drillPhoto->setIsVisible(false);
    storagePhoto->setIsVisible(false);
    fuelTankPhoto->setIsVisible(false);
}