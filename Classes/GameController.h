#pragma once
#include "cocos2d.h"
#include "Zombie.h"
#include"Level.h"
#include<string>
#include<iostream>
#include<GameOverScene.h>

const int NUM_ZOMBIE = 8;

class GameScene;

class GameController
{
	
public:
	int timeGame;
	int curScore;
	int curLevel;
	float curTimeAppear;
	int numLife;
	float timeInterval;
	Vector<Zombie*> listZombie;
	std::vector<Level*> listLevel;
	std::string str[6];
	std::vector<Point> listPoint;
	GameScene* curGameScene;
	
	GameController();

	static GameController* GetInstance();

	void init();
	
	void initLevel();
	
	void initListPosition();
	
	void setGameScene(GameScene* gameScene);

	void randomZombie();

	void random1Zombie();

	void random2Zombie();

	void random3Zombie();
	
	void randomSpriteZombie();
	
	void levelUp();

	void lossLife();

	void reset();

	void increaseDifficult();

	float getTimeAppear();
	
	~GameController();
private:
	static GameController* s_Instance;
};

