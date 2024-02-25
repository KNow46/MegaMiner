#pragma once
#include <vector>
#include <memory>
#include "InterfaceObject.h"
#include "Storage.h"
#include "Text.h"
#include "Money.h"
#include "ShopMenu.h"
#include "FuelTank.h"

class InterfaceManager
{
private:
    std::vector<std::shared_ptr<InterfaceObject>> allInterfaceObjects;
    std::shared_ptr<Storage> storage;
    std::shared_ptr<Money> money;
    std::shared_ptr<ShopMenu> shopMenu;
    std::shared_ptr<FuelTank> fuelTank;

    int mouseXpos;
    int mouseYpos;

    InterfaceManager()
    { 
     storage = std::make_shared<Storage>();
     allInterfaceObjects.emplace_back(storage);
    
     money = std::make_shared<Money>();
     allInterfaceObjects.emplace_back(money);

    shopMenu = std::make_shared<ShopMenu>();
     allInterfaceObjects.emplace_back(shopMenu);

     fuelTank = std::make_shared<FuelTank>();
     allInterfaceObjects.emplace_back(fuelTank);
  
    }

public:
    static InterfaceManager& getInstance()
    {
        static InterfaceManager instance;
        return instance;
    }

    std::shared_ptr<InterfaceObject> getObjectById(int id)
    {
        for (const auto & interfaceObject : allInterfaceObjects)
        {
            if (interfaceObject->getId() == id)
            {
                return interfaceObject;
            }
        }
        return nullptr;
    }
    void addObject(std::shared_ptr<InterfaceObject> object)
    {
        allInterfaceObjects.emplace_back(object);
       
    }
    std::vector<std::shared_ptr<InterfaceObject>> &getAllInterfaceObjects()
    {
        return allInterfaceObjects;
    }
    std::vector<std::shared_ptr<InterfaceObject>> &getAllVisibleObjects()
    {
        std::vector<std::shared_ptr<InterfaceObject>> allVisibleObjects;
        for (const auto& interfaceObject : allInterfaceObjects)
        {
            if (interfaceObject->getIsVisible())
            {
                allVisibleObjects.push_back(interfaceObject);
            }
        }
       // std::cout << allVisibleObjects.size() << std::endl;
        return allVisibleObjects;
    }
    std::shared_ptr<Storage>& getStorage()
    {
        return storage;
    }

    std::shared_ptr<ShopMenu>& getShopMenu()
    {
        return shopMenu;
    }
    std::shared_ptr<Money>& getMoney()
    {
        return money;
    }
    void handleLeftClick(int xPos, int yPos)
    {
        for (const auto& interfaceObject : allInterfaceObjects)
        {
            if (interfaceObject->getIsVisible())
            {

                if (xPos > interfaceObject->getX() && xPos < interfaceObject->getX() + interfaceObject->getWidth())
                {
                    if (yPos > interfaceObject->getY() && yPos < interfaceObject->getY() + interfaceObject->getHeight())
                    {
                        interfaceObject->onClick();
                        break;
                    }

                }
            }
        }
    }
    /*void handleLeftClickRecursively(int xPos, int yPos, std::vector<std::shared_ptr<InterfaceObject>>)
    {
        for (const auto& interfaceObject : allInterfaceObjects)
        {
            if (interfaceObject->getAggregatedObjects().size() == 0)
            {
                if (xPos > interfaceObject->getX() && xPos < interfaceObject->getX() + interfaceObject->getWidth())
                {
                    if (yPos > interfaceObject->getY() && yPos < interfaceObject->getY() + interfaceObject->getHeight())
                    {
                        interfaceObject->onClick();
                        break;
                    }

                }
            }
            else
            {
                handleLeftClickRecursively(xPos, yPos, interfaceObject->getAggregatedObjects());
            }
        }
    }*/
    void handleHover(int xPos, int yPos)
    {
        mouseXpos = xPos;
        mouseYpos = yPos;

        for (const auto& interfaceObject : allInterfaceObjects)
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
    void update()
    {
        for (const auto& object: allInterfaceObjects)
        {
            object->update();
        }
    }
    int getMouseXpos()
    {
        return mouseXpos;
    }
    int getMouseYpos()
    {
        return mouseYpos;
    }

};