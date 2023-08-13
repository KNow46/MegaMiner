#pragma once
#include <vector>
#include <memory>
#include "InterfaceObject.h"
class InterfaceManager
{
private:
    std::vector<std::shared_ptr<InterfaceObject>> allInterfaceObjects;

    InterfaceManager()
    {
        allInterfaceObjects.emplace_back(std::make_shared<InterfaceObject>(300, 300, windowWidth / 2, windowWidth / 2, "res/textures/board.png", "res/textures/xWon.png"));
    }

public:
    static InterfaceManager& getInstance()
    {
        static InterfaceManager instance;
        return instance;
    }

    std::vector<std::shared_ptr<InterfaceObject>> &getAllInterfaceObjects()
    {
        return allInterfaceObjects;
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

};