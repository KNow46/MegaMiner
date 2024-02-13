#include "Camera.h"

Camera::Camera(int x, int y, int xOffset, int yOffset, int xRange, int yRange)
    : x(x), y(y), xRange(xRange), yRange(yRange), isOn(true), xOffset(xOffset), yOffset(yOffset)
{
}

int Camera::getX()
{
    return x;
}

int Camera::getY()
{
    return y;
}

int Camera::getXrange()
{
    return xRange;
}

int Camera::getYrange()
{
    return yRange;
}

int Camera::getYoffset()
{
    return yOffset;
}

int Camera::getXoffset()
{
    return xOffset;
}

bool Camera::getIsOn()
{
    return isOn;
}

void Camera::setX(int x)
{
    this->x = x;
}

void Camera::setY(int y)
{
    this->y = y;
}

void Camera::setXrange(int xRange)
{
    this->xRange = xRange;
}

void Camera::setYrange(int yRange)
{
    this->yRange = yRange;
}

void Camera::setXOffset(int x)
{
    this->xOffset = x;
}

void Camera::setYOffset(int y)
{
    this->yOffset = y;
}

void Camera::setIsOn(bool isOn)
{
    this->isOn = isOn;
}

void Camera::followObject(std::shared_ptr<GameObject> object)
{
    this->x = object->getX() + this->xOffset;
    this->y = object->getY()+ this->yOffset;
}
