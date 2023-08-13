#include "Camera.h"

Camera::Camera(int x, int y, int xPosAtScreen, int yPosAtScreen, int xRange, int yRange)
    : x(x), y(y), xRange(xRange), yRange(yRange), isOn(true), xPosAtScreen(xPosAtScreen), yPosAtScreen(yPosAtScreen)
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

int Camera::getYposAtScreen()
{
    return yPosAtScreen;
}

int Camera::getXposAtScreen()
{
    return xPosAtScreen;
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

void Camera::setXposAtScreen(int x)
{
    this->xPosAtScreen = x;
}

void Camera::setYposAtScreen(int y)
{
    this->yPosAtScreen = y;
}

void Camera::setIsOn(bool isOn)
{
    this->isOn = isOn;
}
