#pragma once
#include "InterfaceObject.h"
#include "Text.h"
#include "Button.h"

class DialogBox : public InterfaceObject
{
public: 
	DialogBox(int x, int y, int width, int height);
	void onClick();
private:
	std::shared_ptr<Text> content;
	std::shared_ptr<Button> closeButton;

};