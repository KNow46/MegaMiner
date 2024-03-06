#include "GameOverScreen.h"
#include "Global.h"
#include "Button.h"
#include "InterfaceManager.h"
#include <memory>
#include "World.h"
#include "Text.h"
GameOverScreen::GameOverScreen(): InterfaceObject(0,0, windowWidth, windowHeight, "res/textures/gameOver.png")
{
	std::shared_ptr<Button> resetButton = std::make_shared<Button>(windowWidth / 2 - 130, 700, 300, 60, 
		"res/textures/tryAgain.png", "res/textures/tryAgainHovered.png",
		[this]()
		{
			World::getInstance().reset();
			InterfaceManager::getInstance().reset();
			InterfaceManager::getInstance().removeInterfaceObject(this->id);
		});
	aggregatedObjects.push_back(resetButton);

	int pointsAmount = InterfaceManager::getInstance().getMoney()->getTotalAccumulatedMoney();
	int pointsLenght = std::to_string(pointsAmount).length();

	std::shared_ptr<Text> points = std::make_shared<Text>(windowWidth / 2 - pointsLenght * 15, 610, 1000, 100, std::to_string(pointsAmount), 30);
	aggregatedObjects.emplace_back(points);


	
}

