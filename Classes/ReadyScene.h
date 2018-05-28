#pragma once
#include "cocos2d.h"
#include "GameScene.h"
using namespace cocos2d;
class ReadyScene : public Layer 
{
public:
	static Scene* createScene();

	virtual bool init();

	void gotoGameScene(Ref *sender);

	CREATE_FUNC(ReadyScene);
};

