#pragma once
#include "GameObject.h"
#include "TextureManager.h"
class Animation : public GameObject
{
	std::vector<Texture> animationFrames;
	int framesCount;
	int currentFrame;

public: 
	Animation(int x, int y, int width, int height, std::string folderPath);
	virtual const Texture& getTexture();
};