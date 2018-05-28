#include "GameOverScene.h"
#include "GameController.h"

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOverScene::create();

	scene->addChild(layer);


	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	GameController::GetInstance()->reset();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("res/game over.jpg");
	backgroundSprite->setScale(1.2, 1.5);
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	auto lblGO = Label::createWithTTF("GAME OVER", "fonts/DeathtoMetal.ttf", 64);
	lblGO->setPosition(visibleSize.width / 2, 300);
	lblGO->setColor(Color3B::BLACK);
	lblGO->setScale(2.5, 2.5);
	this->addChild(lblGO);

	auto playItem = MenuItemImage::create("res/btn restart.png", "res/btn restart2.png",
		CC_CALLBACK_1(GameOverScene::gotoReadyScene, this));
	
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, 150));
	playItem->setScale(0.6, 0.6);

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);
	return true;
}

void GameOverScene::gotoReadyScene(Ref *sender)
{
	auto scene = ReadyScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene));
}