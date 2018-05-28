#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"

USING_NS_CC;
using namespace CocosDenshion;
Vector<Zombie*> listZombies;
Scene* GameScene::createScene()
{
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
  
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
	
	//share control with GameController
	GameController::GetInstance()->setGameScene(this);

	//init background
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto backgroundSprite = Sprite::create("res/main scene.jpg");
	backgroundSprite->setScale(1.3, 1.5);
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);
	
	//init label level, score, time count down and goal
	int curLevel = GameController::GetInstance()->curLevel;

	auto lblLevel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	lblLevel->setColor(Color3B::GREEN);
	lblLevel->enableShadow();
	lblLevel->setString("Level "+ std::to_string(curLevel));
	lblLevel->setPosition(30, 530);
	lblLevel->setAnchorPoint(Vec2(0.0, 0.5));
	this->addChild(lblLevel);


	lblScore = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 24);
	lblScore->setColor(Color3B::GREEN);
	lblScore->enableShadow();
	lblScore->setPosition(30, 430);
	lblScore->setAnchorPoint(Vec2(0.0, 0.5));
	this->addChild(lblScore);


	int curGoal = GameController::GetInstance()->listLevel[curLevel - 1]->goal;
	lblGoal = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	lblGoal->setString("Goal: "+std::to_string(curGoal));
	lblGoal->setColor(Color3B::GREEN);
	lblGoal->enableShadow();
	lblGoal->setPosition(30, 480);
	lblGoal->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lblGoal);

	timeCountDown = GameController::GetInstance()->timeGame;
	lblTimeCountDown = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	lblTimeCountDown->setString("Time: 0 : "+ std::to_string(GameController::GetInstance()->timeGame));
	lblTimeCountDown->setColor(Color3B::GREEN);
	lblTimeCountDown->enableShadow();
	lblTimeCountDown->setPosition(380, 515);
	lblTimeCountDown->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lblTimeCountDown);

	//init heart
	for (int i = 0; i < GameController::GetInstance()->numLife; i++)
	{
		vecHeart.pushBack(Sprite::create("res/heart.png"));
		vecHeart.at(i)->setPosition(660 + i * 33, 515);
		vecHeart.at(i)->setScale(0.2, 0.2);
		this->addChild(vecHeart.at(i));
	}

	//init zombie
	this->initZombie();
	
	//Update time random zombie
	this->schedule(SEL_SCHEDULE(&GameScene::update), GameController::GetInstance()->timeInterval);

	//Update time count down
	this->schedule(SEL_SCHEDULE(&GameScene::countDown), 1.0);
	
	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	
	//set listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
}

void GameScene::initZombie()
{
	//init all zombie
	for (int i = 0; i < NUM_ZOMBIE; i++)
	{
		auto zombie = GameController::GetInstance()->listZombie.at(i);
		this->addChild(zombie,10);
		zombie->setVisible(false);
	}

}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	//("Touch: %d %d", touch->getLocation().x, touch->getLocation().y)
	auto listZombie = GameController::GetInstance()->listZombie;
	for (int i = 0; i < NUM_ZOMBIE; i++)
	{
		if (listZombie.at(i)->zbSprite->getBoundingBox().containsPoint
			(listZombie.at(i)->convertToNodeSpace(touch->getLocation())))
		{
			listZombie.at(i)->kill(this);
		}
	}
	return true;
}


void GameScene::update(float dt)
{
	GameController::GetInstance()->randomZombie();

}

void GameScene::countDown(float dt)
{
	int time = --timeCountDown;
	//update time UI
	lblTimeCountDown->setString("Time: 0 : " + std::to_string(time));
	
	//increase difficult: reduce time interval, time appear
	if (timeCountDown == 20)
		GameController::GetInstance()->increaseDifficult();

	//Game Over
	if (time == 0)
	{
		auto scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.7, scene));
	}
}

void GameScene::updateScore(int score)
{
	lblScore->setString("Score: " + std::to_string(score));
}
	

void GameScene::updteLife(int life)
{
	vecHeart.at(life)->setVisible(false);
}



void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    
}

