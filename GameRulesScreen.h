#pragma once

#include "InterfaceObject.h"
#include "Button.h"
#include "Text.h"
class GameRulesScreen : public InterfaceObject
{
	int currentScreenIndex;
	std::vector<std::shared_ptr<InterfaceObject>> screens;
	std::vector<std::shared_ptr<Text>> screenText;
	std::shared_ptr<Button> nextScreenButton;
	std::shared_ptr<Button> previousScreenButton;
	std::shared_ptr<Button> closeButton;
	std::shared_ptr<Text> pageNumber;

	void createNextScreenButton();
	void createPreviousScreenButton();
	void createCloseScreenButton();
	void createScreen(std::string text, std::string imagePath);
	void update();
	void updateScreenVisibility();

public:
	GameRulesScreen();

	friend class Button;
};