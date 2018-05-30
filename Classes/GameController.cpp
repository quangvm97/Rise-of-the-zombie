#include "GameController.h"
#include "GameScene.h"

GameController* GameController::s_Instance = 0;


GameController::GameController()
{
	curScore = 0;
	numLife = 3;
	curLevel = 1;
	timeGame = 45;
	timeInterval = 2.0;
	this->initLevel();
	this->initListPosition();
}

GameController* GameController::GetInstance()
{
	if (!s_Instance)
	{
		s_Instance = new GameController();
	}
	return s_Instance;
}

void GameController::init()
{
	//set time appear
	curTimeAppear = listLevel[curLevel - 1]->timeAppear;

	//create 9 zombie and add them to list
	for (int i = 0; i < NUM_ZOMBIE; i++)
	{
		auto newZombie = Zombie::create();
		newZombie->setPos(listPoint.at(i).x, listPoint.at(i).y);
		newZombie->retain();
		listZombie.pushBack(newZombie);
	}
}

void GameController::reset()
{
	numLife = 3;
	curLevel = 1;
	curScore = 0;
}

void GameController::increaseDifficult()
{
	curTimeAppear /= 2;
	timeInterval /= 2;
}

void GameController::setGameScene(GameScene* gameScene)
{
	curGameScene = gameScene;
}

void GameController::initLevel()
{
	int numLevel, num, goal, proba1, proba2, proba3;
	float timeAppear;
	FILE *pFile;
	pFile = fopen("info level.txt", "r");
	//read number level
	fscanf(pFile, "NUM %d", &numLevel);
	for (int i = 0; i < numLevel; i++)
	{
		//read detail of each level
		fscanf(pFile, "%d %f %d %d %d", &goal, &timeAppear, &proba1, &proba2, &proba3);
		listLevel.push_back(new Level(i + 1, goal, timeAppear, proba1, proba2, proba3));
	}

}


void GameController::randomZombie()
{
	//random number zombie attack
	auto level = GameController::GetInstance()->listLevel[curLevel - 1];
	int typeRandom;
	typeRandom = RandomHelper::random_int(1, 10);
	if (typeRandom <= level->arrProbability[0])
		random1Zombie();
	else if (typeRandom <= level->arrProbability[1] + level->arrProbability[0])
		random2Zombie();
	else
		random3Zombie();
}

void GameController::random1Zombie()
{
	int id = RandomHelper::random_int(0, NUM_ZOMBIE - 1);
	listZombie.at(id)->attack();
}

void GameController::random2Zombie()
{
	int id1 = RandomHelper::random_int(0, NUM_ZOMBIE - 1);
	int id2 = id1;
	while (id1 == id2)
	{
		id2 = RandomHelper::random_int(0, NUM_ZOMBIE - 1);
	}
	listZombie.at(id1)->attack();
	listZombie.at(id2)->attack();
}

void GameController::random3Zombie()
{
	int id1 = RandomHelper::random_int(0, NUM_ZOMBIE - 1);
	int id3 = id1, id2 = id1;

	while (id1 == id2)
	{
		id2 = RandomHelper::random_int(0, NUM_ZOMBIE - 1);
	}

	while (id1 == id2 || id1 == id3 || id3 == id2)
	{
		id3 = RandomHelper::random_int(0, NUM_ZOMBIE - 1);
	}

	listZombie.at(id1)->attack();
	listZombie.at(id2)->attack();
	listZombie.at(id3)->attack();
}


void GameController::levelUp()
{
	curLevel++;
	curScore = 0;
	curTimeAppear = listLevel[curLevel - 1]->timeAppear;
	timeInterval = 2.0;
}

float GameController::getTimeAppear()
{
	return curTimeAppear;
}

void GameController::lossLife()
{
	--numLife;
	curGameScene->updteLife(numLife);
	if (!numLife)
	{
		//Game Over
		//reset();
		auto scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
	}
}

void GameController::initListPosition()
{
	//create position of zombie
	listPoint.push_back(Point(Vec2(684, 64)));
	listPoint.push_back(Point(Vec2(645, 231)));
	listPoint.push_back(Point(Vec2(537, 336)));
	listPoint.push_back(Point(Vec2(429, 59)));
	listPoint.push_back(Point(Vec2(477, 220)));
	listPoint.push_back(Point(Vec2(274, 245)));
	listPoint.push_back(Point(Vec2(177, 82)));
	listPoint.push_back(Point(Vec2(381, 343)));
	listPoint.push_back(Point(Vec2(272, 241)));

}


GameController::~GameController()
{

}
