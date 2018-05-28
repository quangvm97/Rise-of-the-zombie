#pragma once
#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;
class LevelCompleteScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LevelCompleteScene);

	void gotoGameScene(Ref *sender);

};