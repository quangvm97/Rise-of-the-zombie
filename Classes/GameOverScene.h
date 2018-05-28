#pragma once
#include "cocos2d.h"
#include "ReadyScene.h"
USING_NS_CC;

class GameController;

class GameOverScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameOverScene);

	void gotoReadyScene(Ref *sender);

};