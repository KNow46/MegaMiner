#pragma once
#include <iostream>
#include <functional>
#include "InterfaceObject.h"

class Button : public InterfaceObject {
public:

    Button(int x, int y, int height, int width, std::string texturePath, std::string textureHoveredPath, std::function<void()> onClickAction)
        : InterfaceObject(x, y, height, width, texturePath, textureHoveredPath), onClickAction(onClickAction) {}

   Button(int x, int y, int height, int width, std::string texturePath, std::function<void()> onClickAction)
        : InterfaceObject(x, y, height, width, texturePath), onClickAction(onClickAction) {}

 

    virtual void onClick() override
    {
        if (onClickAction) {
            onClickAction();
        }
    }

private:
    std::function<void()> onClickAction;
};