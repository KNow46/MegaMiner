#pragma once
#include <vector>
#include "InterfaceObject.h"
#include "Texture.h"


class Text : public InterfaceObject
{
public:

	Text(int x, int y, int width, int height, std::string strText, int fontSize);
	Text(int x, int y, int width, int height, std::string strText, int fontSize, std::string fontPath);

	void changeText(std::string newText);

	int getIntText();

protected:
	void stringTextToTexture();
	std::string fontPath;
	int fontSize;
	std::string strText;
};