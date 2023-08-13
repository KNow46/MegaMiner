#pragma once
#include "GameObject.h"
#include <functional>
#include "TextureManager.h"
class InterfaceObject : public GameObject
{
protected:
	bool isHovered;
	Texture& hoverTexture;
public:
	InterfaceObject(int x, int y, int height, int width, std::string texturePath, std::string textureHoveredPath)
		:GameObject(x, y, height, width, texturePath),  isHovered(0), hoverTexture(TextureManager::getInstance().getTexture(textureHoveredPath)) {};
	InterfaceObject(int x, int y, int height, int width, std::string texturePath)
		:GameObject(x, y, height, width, texturePath), isHovered(0), hoverTexture(TextureManager::getInstance().getTexture(texturePath)) {};

	virtual void onClick() { std::cout << "clicked"; };

	void ballCollisionEffect() {};

	
	void setIsHovered(bool isHovered)
	{
		this->isHovered = isHovered;
	}
	virtual const Texture &getTexture()
	{ 
		if (isHovered == false)
			return texture;
		else
			return hoverTexture;
	};
};