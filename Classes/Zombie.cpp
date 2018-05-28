#include "Zombie.h"
#include "GameController.h"
#include "GameScene.h"

Zombie::Zombie()
{
	//create all animation file path
	str[0] = "sprite sheet/WalkAndDead";
	str[1] = "sprite sheet/male_attack";
	str[2] = "sprite sheet/male_idle";
	str[3] = "sprite sheet/female_walk";
	str[4] = "sprite sheet/felmale_attack";
	str[5] = "sprite sheet/felmale_idle";

	acAttack[0] = "Walk";
	acAttack[1] = "Attack";
	acAttack[2] = "Idle";

	
	initZombie();
	
	
}

void Zombie::initZombie()
{	 
	int id = RandomHelper::random_int(0, 5);
 	std::string strPlist = str[id] + ".plist";
	std::string strSpriteSheet = str[id] + ".png";

	//load file
	SpriteFrameCache *frameCache = SpriteFrameCache::sharedSpriteFrameCache();
	frameCache->removeSpriteFrames();
	frameCache->addSpriteFramesWithFile(strPlist);
	
	SpriteBatchNode *spriteSheet = SpriteBatchNode::create(strSpriteSheet);
	this->addChild(spriteSheet);

	//init acion Dead
	Vector<SpriteFrame*> frameDead(12);
	for (int i = 1; i <= 9; i++){
		String *filename = String::createWithFormat("Dead (%d).png", i);
		SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frameDead.pushBack(frame);
	}

	Animation *runAnimDead = Animation::createWithSpriteFrames(frameDead, 0.05);
	actionDead = Repeat::create(Animate::create(runAnimDead), 1);
	actionDead->retain();

	//init action Walk
	Vector<SpriteFrame*> frameWalk(10);
	for (int i = 1; i <= 8; i++)
	{
		std::string tempStr = acAttack[id%3] + " (" + std::to_string(i) +").png";
		SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tempStr);
		frameWalk.pushBack(frame);
	}

	
	Animation *runAnimWalk = Animation::createWithSpriteFrames(frameWalk, 0.07);
	actionWalk = RepeatForever::create(Animate::create(runAnimWalk));
	actionWalk->retain();

	zbSprite = Sprite::createWithSpriteFrameName("Dead (1).png");
	zbSprite->setScale(0.3, 0.3);

	//Random flip
	auto isFlip = RandomHelper::random_int(0, 1);
	if(isFlip)
		zbSprite->setFlippedX(true);
	zbSprite->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(zbSprite);

}




void Zombie::attack()
{
	this->setVisible(true);
	this->removeAllChildren();
	this->initZombie();
	isTouched = false;
	zbSprite->stopAllActions();
	zbSprite->setOpacity(255);
	zbSprite->setScale(0.3,0);
	zbSprite->runAction(actionWalk);
	
	auto delay = DelayTime::create(GameController::GetInstance()->getTimeAppear());
	//action raise up
	auto acScaleUp = ScaleTo::create(0.3, 0.3, 0.3);

	//action dive
	auto acScaleDown = ScaleTo::create(0.3, 0.3, 0);
	
	auto sequence = Sequence::create(acScaleUp,
		delay,
		acScaleDown,
		CallFuncN::create(CC_CALLBACK_0(Zombie::attackCompleted,this)),
		nullptr);
	zbSprite->runAction(sequence);
}

void Zombie::loadAnim()
{

}

void Zombie::kill(GameScene* scene)
{
	if (!isTouched)
	{
		isTouched = true;
		zbSprite->stopAllActions();
		zbSprite->runAction(actionDead);
		auto fade = FadeTo::create(1.0, 0.0);
		auto seq = Sequence::create(DelayTime::create(0.4), fade, nullptr); 
		zbSprite->runAction(seq);	

		//Update score
		scene->updateScore(++GameController::GetInstance()->curScore);

		//check level completed
		auto curLevel = GameController::GetInstance()->curLevel;

		if (GameController::GetInstance()->curScore ==
			GameController::GetInstance()->listLevel[curLevel - 1]->goal)
		{
			GameController::GetInstance()->levelUp();
			auto scene = LevelCompleteScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
		}
	}

}

void Zombie::attackCompleted()
{
	GameController::GetInstance()->lossLife();
}

void Zombie::setPos(float x, float y)
{
	this->setPosition(x, y);
	zbSprite->setPosition(0, 0);  
}

Zombie::~Zombie()
{

}

