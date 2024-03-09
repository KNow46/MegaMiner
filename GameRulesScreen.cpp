#include "GameRulesScreen.h"
#include "Global.h"
#include "World.h"
#include "InterfaceManager.h"

GameRulesScreen::GameRulesScreen():InterfaceObject(0,0,windowWidth, windowHeight, "res/textures/gameRulesScreen.png"), currentScreenIndex(0)
{

	createNextScreenButton();
	createPreviousScreenButton();
	createCloseScreenButton();

	screens.emplace_back(std::make_shared<InterfaceObject>(200, 200, 300, 300 , "res/textures/controlsImage.png"));
	screenText.emplace_back(std::make_shared<Text>(600, 200, 800, 500, "-control your ;machine movement;;-open shop", 37));

	screens.emplace_back(std::make_shared<InterfaceObject>(100, 200, 400, 300, "res/textures/shop.png"));
	screenText.emplace_back(std::make_shared<Text>(600, 230, 800, 500, "in shop you can ;buy upgrades for your machine and;sell resources", 35));
	
	screens.emplace_back(std::make_shared<InterfaceObject>(100, 200, 400, 300, "res/textures/gasstation.png"));
	screenText.emplace_back(std::make_shared<Text>(600, 220, 800, 500, "in gas station you ;can buy fuel", 35));

	screens.emplace_back(std::make_shared<InterfaceObject>(100, 200, 400, 300, "res/textures/fueltankonly.png"));
	screenText.emplace_back(std::make_shared<Text>(600, 200, 800, 500, "control fuel amount. ;You lose if it is empty", 33));

	screens.emplace_back(std::make_shared<InterfaceObject>(300, 60, 200, 700, "res/textures/storage.png"));
	screenText.emplace_back(std::make_shared<Text>(600, 210, 800, 500, "-storage for ;mined rescources", 35));

	screens.emplace_back(std::make_shared<Button>(windowWidth/2-150, windowHeight/2-50, 300, 100, "res/textures/start.png", "res/textures/startHovered.png",[this]()
		{
			InterfaceManager::getInstance().removeInterfaceObject(this->id);
			World::getInstance().getMachine()->setIsGamePaused(false);
			InterfaceManager::getInstance().getFuelTank()->setIsGamePaused(false);
			InterfaceManager::getInstance().setIsGamePaused(false);
		}));
	screenText.emplace_back(std::make_shared<Text>(600, 210, 800, 500, "", 35));
	


	for (int i = 1; i < screens.size(); i++)
	{
		screens[i]->setIsVisible(false);
	}
	for (int i = 1; i < screenText.size(); i++)
	{
		screenText[i]->setIsVisible(false);
	}

	for (const auto& screen : screens)
	{
		aggregatedObjects.emplace_back(screen);
	}
	for (const auto& screenText : screenText)
	{
		aggregatedObjects.emplace_back(screenText);
	}

	pageNumber = std::make_shared<Text>(windowWidth / 2 - 100, windowHeight - 200, 600, 50, "page 0/" + std::to_string(screens.size()-1), 30);
	aggregatedObjects.emplace_back(pageNumber);
}
void GameRulesScreen::createScreen(std::string text, std::string imagePath)
{
	std::shared_ptr newScreen = std::make_shared<InterfaceObject>(50, 50, windowWidth - 100, 500, imagePath);
	aggregatedObjects.push_back(newScreen);
	newScreen->setIsVisible(false);
}
void GameRulesScreen::update()
{
	handleAggregatedObjectsHover();
	handleAggregatedObjectsHover();

	static bool wasWorldCreated = false;
	if (!wasWorldCreated)
	{
		World::getInstance().getMachine()->setIsGamePaused(true);
		InterfaceManager::getInstance().setIsGamePaused(true);
		wasWorldCreated = true;
	}
}

void GameRulesScreen::createNextScreenButton()
{
	nextScreenButton = std::make_shared<Button>(windowWidth - 180, windowHeight - 120, 130, 65, "res/textures/arrowRight.png", "res/textures/arrowRightHovered.png",
		[this]() {
			if (this->currentScreenIndex < this->screens.size() - 1)
			{
				this->currentScreenIndex++;
				this->updateScreenVisibility();
			}
			else 
			{
				this->currentScreenIndex = 0;
				this->updateScreenVisibility();
			}
			this->pageNumber->changeText("page " + std::to_string(this->currentScreenIndex) + "/" + std::to_string(this->screens.size() - 1));
		});
	
	aggregatedObjects.emplace_back(nextScreenButton);
}

void GameRulesScreen::createPreviousScreenButton()
{
	previousScreenButton = std::make_shared<Button>(50, windowHeight - 120, 130, 65, "res/textures/arrowLeft.png", "res/textures/arrowLeftHovered.png",
		[this]() {
			if (this->currentScreenIndex > 0)
			{
				this->currentScreenIndex--;
				this->updateScreenVisibility();
			}
			else
			{
				this->currentScreenIndex = this->screens.size() - 1;
				this->updateScreenVisibility();
			}
			this->pageNumber->changeText("page " + std::to_string(this->currentScreenIndex) + "/" + std::to_string(this->screens.size() - 1));
		});
	aggregatedObjects.emplace_back(previousScreenButton);
}

void GameRulesScreen::createCloseScreenButton()
{
	closeButton = std::make_shared<Button>(x + width - 70, y, 50, 50, "res/textures/xButton.png", [this]()
		{
			InterfaceManager::getInstance().removeInterfaceObject(this->id);
			World::getInstance().getMachine()->setIsGamePaused(false);
			InterfaceManager::getInstance().getFuelTank()->setIsGamePaused(false);
			InterfaceManager::getInstance().setIsGamePaused(false);
		});
	aggregatedObjects.emplace_back(closeButton);
}

void GameRulesScreen::updateScreenVisibility()
{
	for (int i = 0; i < this->screens.size(); i++)
	{
		if (i != this->currentScreenIndex)
		{
			this->screens[i]->setIsVisible(false);
		}
		else
		{
			this->screens[i]->setIsVisible(true);
		}
	}
	for (int i = 0; i < this->screenText.size(); i++)
	{
		if (i != this->currentScreenIndex)
		{
			this->screenText[i]->setIsVisible(false);
		}
		else
		{
			this->screenText[i]->setIsVisible(true);
		}
	}
}

