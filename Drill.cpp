#include "Drill.h"
#include <iostream>
Drill::Drill(): power(1), level(1)
{

}
int Drill::getLevel()
{
	return level;
}
void Drill::resetLevel()
{
	level = 1;
	power = getPower(level);
}
int Drill::getPower()
{
	return power;
}
int Drill::getPower(int atLevel)
{
	return atLevel * 1;
}
int Drill::getUpgradeCost()
{
	if (level == 1)
		return 500;
	if (level == 2)
		return 1000;
	if (level == 3)
		return 1500;
	if (level == 4)
		return 2500;
	else
		return level * 1000;
}
void Drill::upgrade()
{
	level++;
	power = getPower(level);
}