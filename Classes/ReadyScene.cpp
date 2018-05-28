#include "ReadyScene.h"

USING_NS_CC;


Scene* ReadyScene::createScene()
{
	//'scene' is auto release object
	auto scene = Scene::create();

	//'layer' is auto release object
	auto layer = ReadyScene::create();

	//add layer as a child to scene
	scene->addChild(layer);

	//return scene
	return scene;

}

// on "init" you need to initialize your instance
bool ReadyScene::init()
{

	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	GameController::GetInstance()->init();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//add background
	auto backgroundSprite = Sprite::create("res/menu scene.jpg");
	backgroundSprite->setScale(1.3, 1.3);
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	//add text
	auto label = Label::createWithTTF("RISE OF THE ZOMBIE", "fonts/fofbb_ital.ttf", 60);
	label->setPosition(visibleSize.width / 2, 400);
	label->setColor(Color3B(76,153,0));
	label->setScale(1.1, 1.1);
	label->enableOutline(Color4B::BLACK, 3);
	this->addChild(label);

	auto playItem = MenuItemImage::create("res/button play.png", "res/button play chosed.png", CC_CALLBACK_1(ReadyScene::gotoGameScene, this));
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, 250));
	playItem->setScale(0.6, 0.6);

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	return true;
}


void ReadyScene::gotoGameScene(Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene));
}