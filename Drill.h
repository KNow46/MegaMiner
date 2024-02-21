#pragma once

class Drill
{
	int level;
	int power;
public:
	Drill();
	void upgrade();
	int getUpgradeCost();
	int getPower();
	int getLevel();
};