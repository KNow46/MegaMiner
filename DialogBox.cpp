#include "DialogBox.h"
#include "InterfaceManager.h"
DialogBox::DialogBox(int x, int y, int width, int height) : InterfaceObject(x,y,width,height, "res/textures/shopmenu/1.png")
{
	closeButton = std::make_shared<Button>(x + width - 70, y, 50, 50, "res/textures/xButton.png", [this]()
		{
			InterfaceManager::getInstance().removeInterfaceObject(this->id);
		}
	);
	aggregatedObjects.push_back(closeButton);
}

void DialogBox::onClick()
{
	handleAggregatedObjectsOnClick();
}
