#include "Machine.h"
#include "TextureManager.h"

Machine::Machine(int x, int y, int width, int height)
    : GameObject(x, y, width, height, "res/textures/machine/standing.png"), currentState(STANDING)
{
}

const Texture& Machine::getTexture()
{
    std::string basePath = "res/textures/machine/";

    if (currentState == STANDING)
    {
        return TextureManager::getInstance().getTexture(basePath + "standing.png");
    }
    else if (currentState == FLYING)
    {
        return TextureManager::getInstance().getTexture(basePath + "flying.png");
    }
    else if (currentState == DRILLING_DOWN)
    {
        return TextureManager::getInstance().getTexture(basePath + "drillingDown.png");
    }
    else if (currentState == DRILLING_LEFT)
    {
        return TextureManager::getInstance().getTexture(basePath + "drillingLeft.png");
    }
    else if (currentState == DRILLING_RIGHT)
    {
        return TextureManager::getInstance().getTexture(basePath + "drillingRight.png");
    }
}

void Machine::setCurrentState(State state)
{
    currentState = state;
}

Machine::State Machine::getCurrentState()
{
    return currentState;
}