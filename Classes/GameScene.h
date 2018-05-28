#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Zombie.h"
#include "GameController.h"
#include "LevelCompleteScene.h"


using namespace cocos2d;

class GameOverScene;

class GameScene : public cocos2d::Scene
{
public:

	Action *actionDead;
	Action *actionWalk;
	Label *lblScore;
	Label *lblGoal;
	Label *lblLevel;
	Label *lblTimeCountDown;
	float timeCountDown;
	Vector<Sprite*>vecHeart;
	
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	//Check when user touch in screen
	bool onTouchBegan(Touch *touch, Event *unused_event);
	
	void GameScene::onEnter();
	
	//Update random zombie
	void update(float dt);

	//time count down
	void countDown(float dt);
	
	//initialize zombie
	void initZombie();

	//update score
	void updateScore(int score);

	//update live
	void updteLife(int life);

	void test();

    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // GameScene
