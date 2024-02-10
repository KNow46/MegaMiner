#include "Machine.h"
#include "TextureManager.h"
#include "CollisionManager.h"

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
    else if (currentState == FLYING_LEFT)
    {
        return TextureManager::getInstance().getTexture(basePath + "flying.png");
    }
    else if (currentState == FLYING_RIGHT)
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
    else if (currentState == FALLING_DOWN)
    {
        return TextureManager::getInstance().getTexture(basePath + "drillingRight.png");
    }
    else if (currentState == FALLING_LEFT)
    {
        return TextureManager::getInstance().getTexture(basePath + "drillingLeft.png");
    }
    else if (currentState == FALLING_RIGHT)
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

void Machine::update()
{
    bool isBlockUnder = true;

    std::shared_ptr<Block> blockUnderMachine1 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x , y + height + fallingYSpeed));
    std::shared_ptr<Block> blockUnderMachine2 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x+width, y + height + fallingYSpeed));

    if (!blockUnderMachine1 && !blockUnderMachine2)
    {
        isBlockUnder = false;
    }
    if (!isBlockUnder && !(currentState == FLYING_LEFT || currentState == FLYING_RIGHT || currentState == FLYING))
    {
        if (currentState == DRILLING_LEFT)
        {
            currentState = FALLING_LEFT;
        }
        else if (currentState == DRILLING_RIGHT)
        {
            currentState = FALLING_RIGHT;
        }
        else
        {
            currentState = FALLING_DOWN;
        }
    }
    else if (currentState == FALLING_DOWN && isBlockUnder)
    {
        currentState = STANDING;
    }
    else if (currentState == DRILLING_RIGHT)
    {
        std::shared_ptr<Block> block = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x + width + xSpeed, y + height/2));
        if (block)
        {

        }
        else
        {
            x += xSpeed;
        }
    }
    else if (currentState == DRILLING_LEFT)
    {
        std::shared_ptr<Block> block = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x - xSpeed, y + height / 2));
        if (block)
        {

        }
        else
        {
            x -= xSpeed;
        }
    }
    else if (currentState == DRILLING_DOWN)/////////////////////
    {
        std::shared_ptr<Block> block = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x + width /2, y + height + fallingYSpeed));
        if (block)
        {

        }
    }
    else if (currentState == FLYING)
    {
        bool isBlockOver = true;

        std::shared_ptr<Block> blockOverMachine1 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x, y-flyingYspeed));
        std::shared_ptr<Block> blockOverMachine2 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x + width, y-flyingYspeed));

        if (!blockOverMachine1 && !blockOverMachine2)
        {
            isBlockOver = false;
        }

        if (!isBlockOver)
        {
            y -= flyingYspeed;
        }
    }
    else if (currentState == FLYING_RIGHT)
    {
        bool isBlockOver = true;
        bool isBlockOnTheRight = true;

        std::shared_ptr<Block> blockOverMachine1 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x, y - flyingYspeed));
        std::shared_ptr<Block> blockOverMachine2 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x + width, y - flyingYspeed));

        std::shared_ptr<Block> blockOnTheRight1 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x + width + flyingXspeed, y));
        std::shared_ptr<Block> blockOnTheRight2 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x + width + flyingXspeed, y + height));

        if (!blockOverMachine1 && !blockOverMachine2)
        {
            isBlockOver = false;
        }
        if (!blockOnTheRight1 && !blockOnTheRight2)
        {
            isBlockOnTheRight = false;
        }
        
        if (!isBlockOver)
        {
            y -= flyingYspeed;
        }
        if (!isBlockOnTheRight)
        {
            x += flyingXspeed;
        }
        
    }
    else if (currentState == FLYING_LEFT)
    {
        bool isBlockOver = true;
        bool isBlockOnTheLeft= true;

        std::shared_ptr<Block> blockOverMachine1 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x, y - flyingYspeed));
        std::shared_ptr<Block> blockOverMachine2 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x + width, y - flyingYspeed));
        
        std::shared_ptr<Block> blockOnTheLeft1 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x - flyingXspeed, y));
        std::shared_ptr<Block> blockOnTheLeft2 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x - flyingXspeed, y + height));

        if (!blockOverMachine1 && !blockOverMachine2)
        {
            isBlockOver = false;
        }
        if (!blockOnTheLeft1 && !blockOnTheLeft2)
        {
            isBlockOnTheLeft = false;
        }

        if (!isBlockOver)
        {
            y -= flyingYspeed;
        }
        if (!isBlockOnTheLeft)
        {
            x -= flyingXspeed;
        }
    }
    if (currentState == FALLING_DOWN)
    {
        y += fallingYSpeed;
    }
    if (currentState == FALLING_RIGHT)
    {
        y += fallingYSpeed;

        bool isBlockOnTheRight = true;

        std::shared_ptr<Block> blockOnTheRight1 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x + width + fallingXSpeed, y));
        std::shared_ptr<Block> blockOnTheRight2 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x + width + fallingXSpeed, y + height));
        
        if (!blockOnTheRight1 && !blockOnTheRight2) 
        {
            isBlockOnTheRight = false;
        }
  
        if(!isBlockOnTheRight)  
        {
            x += fallingXSpeed;
        }
           
    }
    if (currentState == FALLING_LEFT)
    {
        y += fallingYSpeed;

        bool isBlockOnTheLeft = true;

        std::shared_ptr<Block> blockOnTheLeft1 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x - fallingXSpeed, y));
        std::shared_ptr<Block> blockOnTheLeft2 = std::dynamic_pointer_cast<Block>(CollisionManager::getInstance().checkCollisions(x - fallingXSpeed, y + height));

        if (!blockOnTheLeft1 && !blockOnTheLeft2) {
            isBlockOnTheLeft = false;
        }

        if (!isBlockOnTheLeft) {
            x -= fallingXSpeed;
        }
    }
    std::cout << blockUnderMachine1 << std::endl;
}