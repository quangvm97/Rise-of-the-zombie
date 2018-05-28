#pragma once
#include <cocos2d.h>
#include <string>

USING_NS_CC;

class GameController;
class GameScene;

class Zombie : public Node 
{

public:

	Action* actionDead;
	Action* actionWalk;
	Action* actionIdle;
	Sprite* zbSprite;
	float time_attack;
	std::string str[6];
	std::string acAttack[3];
	bool isTouched;//Avoid double click in sprite when it dead
	static float appear_time;
	//auto gameControl;

	Zombie();
	static Zombie* Zombie::create()
	{
		Zombie* zb = new Zombie();
		return zb;
		CC_SAFE_RELEASE(zb);
	};

	void initZombie();
	
	void loadAnim();
	
	void createAction();
	
	void attack();
	
	//when user missed zombie
	void attackCompleted();
	
	//zombie die
	void kill(GameScene* scene);
	
	void setPos(float x, float y);
	
	~Zombie();
};

