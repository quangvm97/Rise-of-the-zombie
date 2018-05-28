#include "LevelCompleteScene.h"

Scene* LevelCompleteScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LevelCompleteScene::create();

	scene->addChild(layer);


	return scene;
}

bool LevelCompleteScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("res/level up.jpg");
	backgroundSprite->setScale(0.6, 0.6);
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	auto lblComlpt = Label::createWithTTF("Level " + std::to_string(GameController::GetInstance()->curLevel - 1)+ " Complete!",
		"fonts/Marker Felt.ttf",
		64);
	lblComlpt->setPosition(visibleSize.width / 2, 350);
	lblComlpt->setScale(1.2, 1.2);
	lblComlpt->setColor(Color3B::YELLOW);
	lblComlpt->enableGlow(Color4B::RED);
	this->addChild(lblComlpt);

	auto playItem = MenuItemImage::create("res/next level.png", 
		"res/next level2.png", 
		CC_CALLBACK_1(LevelCompleteScene::gotoGameScene, this));
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, 170));
	playItem->setScale(0.5, 0.5);

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);


	this->addChild(menu);
	return true;
}

void LevelCompleteScene::gotoGameScene(Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene));
}