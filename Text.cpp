#include "Text.h"
#include <math.h>

Text::Text(int x, int y, int width, int height, std::string strText, int fontSize)
	: InterfaceObject(x, y, width, height, "res/textures/empty.png"), fontPath("res/textures/ansi"), fontSize(fontSize), strText(strText)
{
	stringTextToTexture();
}

Text::Text(int x, int y, int width, int height, std::string strText, int fontSize, std::string fontPath)
	: InterfaceObject(x, y, width, height, "res/textures/empty.png"), fontPath(fontPath), fontSize(fontSize), strText(strText)
{
	stringTextToTexture();
}

void Text::changeText(std::string newText)
{
	std::cout << aggregatedObjects.size() << std::endl;
	for (int i = aggregatedObjects.size(); i > 0; i--)
	{
		aggregatedObjects.pop_back();
		
	}
	std::cout << aggregatedObjects.size() << std::endl;
	strText = newText;
	stringTextToTexture();
	std::cout << std::endl << std::endl;
}



void Text::stringTextToTexture()
{
	for (int i = 0; i < strText.length(); i++)
	{
		double positionX = x + (i * fontSize) % width;
		int line = floor(i * fontSize / width);

		double positionY = y + line * fontSize * 2;

		if (strText[i] == ' ')
		{
			aggregatedObjects.emplace_back(new GameObject(positionX, positionY, fontSize * 0.9, fontSize * 1.8,
				"res/textures/empty.png"));
			continue;
		}
		if (strText[i] == '/')
		{
			aggregatedObjects.emplace_back(new GameObject(positionX, positionY, fontSize * 0.9, fontSize * 1.8,
				"res/textures/ansi/backslash.png"));
			continue;
		}

		aggregatedObjects.emplace_back(new GameObject(positionX, positionY, fontSize * 0.9, fontSize * 1.8, 
			fontPath + "/" + strText[i] + ".png"));

	}
}

int Text::getIntText()
{
	int integer = 0;

	for (int i = 0; i < strText.length(); i++)
	{
		integer += (strText[i] - '0') * pow(10, strText.length() - i - 1);
	}
	return integer;
}