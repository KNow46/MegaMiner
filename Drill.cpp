#include "Drill.h"
#include <iostream>
Drill::Drill(): power(1), level(1)
{

}
int Drill::getLevel()
{
	return level;
}
int Drill::getPower()
{
	return power;
}
int Drill::getPower(int atLevel)
{
	if (atLevel == 1)
		return 1;
	if (atLevel == 2)
		return 2;
	if (atLevel == 3)
		return 3;
	if (atLevel == 4)
		return 4;
	if (atLevel == 5)
		return 5;
}
int Drill::getUpgradeCost()
{
	if (level == 1)
		return 500;
	if (level == 2)
		return 1000;
	if (level == 3)
		return 2000;
	if (level == 4)
		return 5000;
	return 99999999;
}
void Drill::upgrade()
{
	level++;
	power = getPower(level);
}