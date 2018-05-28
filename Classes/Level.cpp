#include "Level.h"


Level::Level(int number, int goal, float timeAppear, int proba1, int proba2, int proba3)
{
	this->number = number;
	this->goal = goal;
	this->timeAppear = timeAppear;
	arrProbability[0] = proba1;
	arrProbability[1] = proba2;
	arrProbability[2] = proba3;
}


Level::~Level()
{

}
