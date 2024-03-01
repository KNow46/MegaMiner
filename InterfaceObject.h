#pragma once
#include "GameObject.h"
#include <functional>
#include "TextureManager.h"


class InterfaceObject : public GameObject
{
protected:
	bool isHovered;
	Texture& hoverTexture;

	virtual void handleAgregatedObjectsOnClick();
	virtual void handleAgregatedObjectsHover();
	virtual void handleAgregatedObjectsUpdate();

public:
	InterfaceObject(int x, int y, int height, int width, std::string texturePath, std::string textureHoveredPath);
	
	InterfaceObject(int x, int y, int height, int width, std::string texturePath);


	virtual void onClick() {};
	virtual void onHovered() {};
	
	void setIsHovered(bool isHovered);


	virtual const Texture& getTexture();
	
	virtual void update() {};
};