#include "Slider.h"
#include "InterfaceManager.h"
#include <GLFW/glfw3.h>

Slider::Slider(int x, int y, int width, int height) : InterfaceObject(x,y, width, height, "res/textures/slider.png"), isHandlerGrabbed(false)
{
	handler = std::make_shared<InterfaceObject>(x, y, height, height, "res/textures/sliderHandler.png");
    aggregatedObjects.push_back(handler);
}

void Slider::update()
{
    GLFWwindow* window = InterfaceManager::getInstance().getWindow();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
    {
        
        if(isHandlerGrabbed)
        {
  
            int xPos = InterfaceManager::getInstance().getMouseXpos();
           
            if(xPos - handler->getWidth() / 2  > x && xPos < x+ width - handler->getWidth() / 2)
            {
                handler->setX(xPos - handler->getWidth() / 2);
            }
            else if (xPos - handler->getWidth() / 2 <= x)
            {
                handler->setX(x);
            }
            else if (!(xPos < x + width - handler->getWidth() / 2))
            {
                handler->setX(x+width - handler->getWidth());
            }
        }   

    }
    else
    {
        isHandlerGrabbed = false;
    }

}

void Slider::onClick()
{
    int xPos = InterfaceManager::getInstance().getMouseXpos();
    int yPos = InterfaceManager::getInstance().getMouseYpos();

   
    if (xPos > handler->getX() && xPos < handler->getX() + handler->getWidth() &&
        yPos > handler->getY() && yPos < handler->getY() + handler->getHeight())
    {
        isHandlerGrabbed = true;
    }
}

float Slider::getHandlerPosition()
{
    int xPos = InterfaceManager::getInstance().getMouseXpos();

    float maxPos = x + width - handler->getWidth();
    float minPos = x;
    int currPos = handler->getX();

    if(maxPos-minPos != 0)
        return (currPos - minPos) / (maxPos - minPos);
}

