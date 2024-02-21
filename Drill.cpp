#include "Drill.h"

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
	if (level == 1)
		power = 2;
	if (level == 2)
		power = 3;
	if (level == 3)
		power = 4;
	if (level == 4)
		power = 5;
	if (level == 5)
		power = 6;
	level++;
}