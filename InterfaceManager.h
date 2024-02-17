#pragma once
#include <vector>
#include <memory>
#include "InterfaceObject.h"
#include "Storage.h"
#include "Text.h"
#include "Money.h"
class InterfaceManager
{
private:
    std::vector<std::shared_ptr<InterfaceObject>> allInterfaceObjects;
    std::shared_ptr<Storage> storage;
    std::shared_ptr<Money> money;
    InterfaceManager()
    { 
     storage = std::make_shared<Storage>();
     allInterfaceObjects.emplace_back(storage);
    
     money = std::make_shared<Money>();
     allInterfaceObjects.emplace_back(money);
  
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
        std::cout << "zzz";
        allInterfaceObjects.emplace_back(object);
       
    }
    std::vector<std::shared_ptr<InterfaceObject>> &getAllInterfaceObjects()
    {
        return allInterfaceObjects;
    }
    std::vector<std::shared_ptr<InterfaceObject>> &getAllVisibleObjects()
    {
        std::vector<std::shared_ptr<InterfaceObject>> allVisibleObjects;
        std::cout << allInterfaceObjects.size() << std::endl;
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

    void handleLeftClick(int xPos, int yPos)
    {
        for (const auto& interfaceObject : allInterfaceObjects)
        {
            if(xPos > interfaceObject->getX() && xPos < interfaceObject->getX() + interfaceObject->getWidth())
            {
                if (yPos > interfaceObject->getY() && yPos < interfaceObject->getY() + interfaceObject->getHeight())
                {
                    interfaceObject->onClick();
                }
                
            }
        }
    }
    void handleHover(int xPos, int yPos)
    {
        for (const auto& interfaceObject : allInterfaceObjects)
        {
            if (xPos > interfaceObject->getX() && xPos < interfaceObject->getX() + interfaceObject->getWidth() && 
                yPos > interfaceObject->getY() && yPos < interfaceObject->getY() + interfaceObject->getHeight())
            {
                interfaceObject->setIsHovered(true);
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

};