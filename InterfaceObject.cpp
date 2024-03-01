#include "InterfaceObject.h"
#include "Interfacemanager.h"

InterfaceObject::InterfaceObject(int x, int y, int height, int width, std::string texturePath, std::string textureHoveredPath)
	:GameObject(x, y, height, width, texturePath), isHovered(0), hoverTexture(TextureManager::getInstance().getTexture(textureHoveredPath))
{
}

InterfaceObject::InterfaceObject(int x, int y, int height, int width, std::string texturePath)
	:GameObject(x, y, height, width, texturePath), isHovered(0), hoverTexture(TextureManager::getInstance().getTexture(texturePath))
{
}


void InterfaceObject::handleAgregatedObjectsOnClick()
{
	int xPos = InterfaceManager::getInstance().getMouseXpos();
	int yPos = InterfaceManager::getInstance().getMouseYpos();

		for (const auto& gameObject : aggregatedObjects)
		{
			if (std::shared_ptr<InterfaceObject> interfaceObject = std::dynamic_pointer_cast<InterfaceObject>(gameObject))
			{
				if (interfaceObject->getIsVisible())
				{
					if (xPos > interfaceObject->getX() && xPos < interfaceObject->getX() + interfaceObject->getWidth() &&
						yPos > interfaceObject->getY() && yPos < interfaceObject->getY() + interfaceObject->getHeight())
					{
						interfaceObject->onClick();
					}
				}
			}
		}
}

void InterfaceObject::handleAgregatedObjectsHover()
{
	int xPos = InterfaceManager::getInstance().getMouseXpos();
	int yPos = InterfaceManager::getInstance().getMouseYpos();

	for (const auto& gameObject : aggregatedObjects)
	{
		if (std::shared_ptr<InterfaceObject> interfaceObject = std::dynamic_pointer_cast<InterfaceObject>(gameObject))
		{
			if (interfaceObject->getIsVisible())
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
	}
}

void InterfaceObject::handleAgregatedObjectsUpdate()
{
	for (const auto& gameObject : aggregatedObjects)
	{
		gameObject->update();
	}
}


void InterfaceObject::setIsHovered(bool isHovered)
{
	this->isHovered = isHovered;
}

const Texture& InterfaceObject::getTexture()
{
	if (isHovered == false)
		return texture;
	else
		return hoverTexture;
}
