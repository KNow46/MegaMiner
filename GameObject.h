#pragma once
#include <string>
#include <iostream>
#include "Texture.h"
#include "TextureManager.h"
#include <vector>

class GameObject
{
protected:
    bool isDestroyed;
    int height;
    int width;
    Texture& texture;
    int displayPriority;
    double x;
    double y;
    std::vector<std::shared_ptr<GameObject>> aggregatedObjects;
    std::string description;

public:
    GameObject(int x, int y, int width, int height, std::string texturePath)
        :x(x), y(y), height(height), width(width), isDestroyed(false), texture(TextureManager::getInstance().getTexture(texturePath))
    {
    };
    GameObject(int x, int y, int width, int height, std::string texturePath, std::string description)
        :x(x), y(y), height(height), width(width), isDestroyed(false), description(description), texture(TextureManager::getInstance().getTexture(texturePath))
    {
    };

    ~GameObject() {};

    virtual void collision(GameObject&) {};

    int getHeight() { return height; };

    int getWidth() { return width; };

    int getX() { return x; };

    int getY() { return y; };

    void setX(float x) { this->x = x; };

    void setY(float y) { this->y = y; };

    bool getIsDestroyed() { return isDestroyed; };

    virtual const Texture& getTexture() { return texture; };

    void setDescription(std::string description)
    {
        this->description = description;
    }
    std::string getDescription()
    {
        return description;
    }
    virtual void update() {};


    std::vector <std::shared_ptr<GameObject>>& getAggregatedObjects()
    {
        return aggregatedObjects;
    }
};
