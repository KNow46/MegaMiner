#pragma once
#include <vector>
#include <memory>
#include "InterfaceObject.h"
#include "Storage.h"
#include "Text.h"
#include "Money.h"
#include "ShopMenu.h"
#include "FuelTank.h"
#include "Slider.h"
#include "GasStationMenu.h"
#include <GLFW/glfw3.h>
#include "DialogBox.h"
#include "Animation.h"
#include "GameRulesScreen.h"
class InterfaceManager
{
private:
    std::vector<std::shared_ptr<InterfaceObject>> allInterfaceObjects;
    std::shared_ptr<Storage> storage;
    std::shared_ptr<Money> money;
    std::shared_ptr<ShopMenu> shopMenu;
    std::shared_ptr<FuelTank> fuelTank;
    std::shared_ptr<GasStationMenu> gasStationMenu;
    GLFWwindow* window;


    int mouseXpos;
    int mouseYpos;
    bool isGamePaused;

    InterfaceManager() : isGamePaused(true)
    { 
     storage = std::make_shared<Storage>();
     allInterfaceObjects.emplace_back(storage);
    
     money = std::make_shared<Money>();
     allInterfaceObjects.emplace_back(money);

    shopMenu = std::make_shared<ShopMenu>();
     allInterfaceObjects.emplace_back(shopMenu);

     fuelTank = std::make_shared<FuelTank>();
     allInterfaceObjects.emplace_back(fuelTank);

     gasStationMenu = std::make_shared<GasStationMenu>();
     allInterfaceObjects.emplace_back(gasStationMenu);

     allInterfaceObjects.emplace_back(std::make_shared<GameRulesScreen>());
    }

public:
    static InterfaceManager& getInstance()
    {
        static InterfaceManager instance;
        return instance;
    }
    void setIsGamePaused(bool isPaused)
    {
        isGamePaused = isPaused;

        if(isPaused)
            fuelTank->setIsGamePaused(true);
    }
    bool getIsGamePaused()
    {
        return isGamePaused;
    }

    void setWindow(GLFWwindow* window)
    {
        this->window = window;
    }
    GLFWwindow* getWindow()
    {
        return window;
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
        std::shared_ptr<InterfaceObject> objectCopy = object;
        allInterfaceObjects.push_back(objectCopy);
       
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
    std::shared_ptr<FuelTank>& getFuelTank()
    {
        return fuelTank;
    }
    std::shared_ptr<GasStationMenu>& getGasStationMenu()
    {
        return gasStationMenu;
    }
    void handleLeftClick(int xPos, int yPos)
    {
        for (auto it = allInterfaceObjects.rbegin(); it != allInterfaceObjects.rend(); ++it)
        {
            auto& interfaceObject = *it;

            if (interfaceObject->getIsVisible())
            {
                if (xPos > interfaceObject->getX() && xPos < interfaceObject->getX() + interfaceObject->getWidth())
                {
                    if (yPos > interfaceObject->getY() && yPos < interfaceObject->getY() + interfaceObject->getHeight())
                    {
                        interfaceObject->onClick();
                        return; 
                    }
                }
            }
        }
    }
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

    void removeInterfaceObject(int id)
    {
        std::cout << allInterfaceObjects.size() << std::endl;
        for (int i = 0; i < allInterfaceObjects.size(); i++)
        {
            if (allInterfaceObjects[i]->getId() == id)
            {
                allInterfaceObjects.erase(allInterfaceObjects.begin() + i);
                break;
            }
        }
        std::cout << allInterfaceObjects.size() << std::endl;
    }
    void reset()
    {
        storage->reset();
        fuelTank->reset();
        money->reset();
    }
   
};