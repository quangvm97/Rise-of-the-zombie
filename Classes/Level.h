#pragma once
#include<iostream>
class Level
{
public:
	Level(int number, int goal, float timeApprear, int proba1, int proba2, int proba3);
	int arrProbability[3];
	int number;
	int goal;
	float timeAppear;
	~Level();
};

