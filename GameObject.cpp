#include "GameObject.h"

int GameObject::nextId = 1;

GameObject::GameObject(int x, int y, int width, int height, std::string texturePath)
    : x(x), y(y), height(height), width(width), isDestroyed(false), texture(TextureManager::getInstance().getTexture(texturePath))
{
    id = nextId++;
    std::cout << id << std::endl;
}

GameObject::~GameObject() {
    nextId--;
}

int GameObject::getHeight() {
    return height;
}

int GameObject::getWidth() {
    return width;
}

int GameObject::getX() {
    return x;
}

int GameObject::getY() {
    return y;
}

void GameObject::setX(float x) {
    this->x = x;
}

void GameObject::setY(float y) {
    this->y = y;
}

bool GameObject::getIsDestroyed() {
    return isDestroyed;
}

const Texture& GameObject::getTexture() {
    return texture;
}

void GameObject::update() {
  
}

std::vector<std::shared_ptr<GameObject>>& GameObject::getAggregatedObjects() {
    return aggregatedObjects;
}
