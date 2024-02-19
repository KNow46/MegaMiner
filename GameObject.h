#pragma once

#include <string>
#include <iostream>
#include "Texture.h"
#include "TextureManager.h"
#include <vector>
#include <memory>

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
    bool isVisible;
    static int nextId;
    int id;

public:
    GameObject(int x, int y, int width, int height, std::string texturePath);
    ~GameObject();

    virtual void collision(GameObject&) {};

    int getId();
    int getHeight();
    int getWidth();
    int getX();
    int getY();
    void setX(float x);
    void setY(float y);
    bool getIsDestroyed();
    bool getIsVisible();
    virtual void setIsVisible(bool isVisible);
    virtual const Texture& getTexture();

    virtual void update();

    std::vector <std::shared_ptr<GameObject>>& getAggregatedObjects();
};
