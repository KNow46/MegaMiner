#pragma once
#include "GameObject.h"
#include <functional>
#include "TextureManager.h"


class InterfaceObject : public GameObject
{
protected:
	bool isHovered;
	Texture& hoverTexture;

	virtual void handleAggregatedObjectsOnClick();
	virtual void handleAggregatedObjectsHover();
	virtual void handleAggregatedObjectsUpdate();

public:
	InterfaceObject(int x, int y, int height, int width, std::string texturePath, std::string textureHoveredPath);
	
	InterfaceObject(int x, int y, int height, int width, std::string texturePath);


	virtual void onClick() { handleAggregatedObjectsOnClick(); }
	virtual void onHovered() {};
	
	void setIsHovered(bool isHovered);


	virtual const Texture& getTexture();
	
	virtual void update() {
		handleAggregatedObjectsHover();
		handleAggregatedObjectsUpdate();
	};
};