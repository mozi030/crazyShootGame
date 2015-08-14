#include"ParameterManager.h"

ArcherParameter::ArcherParameter(){}
ArcherParameter::ArcherParameter(cocos2d::Vec2 _initialPosition) {
	initialPosition = _initialPosition;
}

EnemyParameter::EnemyParameter(){}
EnemyParameter::EnemyParameter(cocos2d::Vec2 _initialPosition, int _blood, int _mode) {
	initialPosition = _initialPosition;
	mode = _mode;
	blood = _blood;
}

EdgeParameter::EdgeParameter(){}
EdgeParameter::EdgeParameter(cocos2d::Vec2 _firstPoint, cocos2d::Vec2 _secondPoint, int _type) {
	firstPoint = _firstPoint;
	secondPoint = _secondPoint;
	type = _type;
}

GameParameterForLevels::GameParameterForLevels(int _levelNum, Size _mapSize, ArcherParameter* _archerParameter, std::vector<EnemyParameter*> _enemyParameter, std::vector<EdgeParameter*> _edgeParameter) {
	levelNum = _levelNum;
	archerParameter = _archerParameter;
	enemyParameter = _enemyParameter;
	edgeParameter = _edgeParameter;
	mapSize = _mapSize;
}

//全局参数

Vec2 ParameterManager::gravity = Vec2(0, -200);
Vec2 ParameterManager::getGravity() {
	return gravity;
}

Size ParameterManager::visibleSize = Size(1024,640);
Size ParameterManager::getVisibleSize() {
	return visibleSize;
}

GameParameterForLevels* ParameterManager::level1GameParameter = NULL;
GameParameterForLevels* ParameterManager::level2GameParameter = NULL;
GameParameterForLevels* ParameterManager::level3GameParameter = NULL;
GameParameterForLevels* ParameterManager::level4GameParameter = NULL;
GameParameterForLevels* ParameterManager::level5GameParameter = NULL;

GameParameterForLevels* ParameterManager::getGameParameterInstance(int _levelNum) {
	switch (_levelNum) {
	case 1:
		//第一关
		if (level1GameParameter == NULL) {
			auto archer = new ArcherParameter(Vec2(80, 120));

			std::vector<EnemyParameter*>enemyParameterVector;
			enemyParameterVector.push_back(new EnemyParameter(Vec2(500, 100), 5, 1));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(600, 100), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1800, 100), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1700, 100), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(900, 130), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1100, 130), 15, 3));

			std::vector<EdgeParameter*>groundParameterVector;  //最后的参数，1是地板，用来站的，2是墙壁
			groundParameterVector.push_back(new EdgeParameter(Vec2(0, 0), Vec2(0, 640), 2));//左墙
			groundParameterVector.push_back(new EdgeParameter(Vec2(2048, 0), Vec2(2048, 640), 2));//右墙
			groundParameterVector.push_back(new EdgeParameter(Vec2(0, 60), Vec2(713, 60), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(803, 93), Vec2(1280, 93), 1));//其他地板2
			groundParameterVector.push_back(new EdgeParameter(Vec2(1407, 63), Vec2(2046, 63), 1));//其他地板3
			groundParameterVector.push_back(new EdgeParameter(Vec2(0, 0), Vec2(2046, 0), 1));//其他地板3
			
			level1GameParameter = new GameParameterForLevels(1, Size(2048, 640), archer, enemyParameterVector, groundParameterVector);
		}
		return level1GameParameter;

	case 2:
		//第二关
		if (level2GameParameter == NULL) {
			auto archer = new ArcherParameter(Vec2(100, 520));

			std::vector<EnemyParameter*>enemyParameterVector;
			enemyParameterVector.push_back(new EnemyParameter(Vec2(350, 420), 10, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(500, 300), 10, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(680, 450), 10, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(900, 500), 10, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1080, 400), 10, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1200, 470), 10, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1430, 470), 10, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1600, 370), 10, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1800, 450), 10, 3));

			std::vector<EdgeParameter*>groundParameterVector;  //最后的参数，1是地板，用来站的，2是墙壁
			groundParameterVector.push_back(new EdgeParameter(Vec2(0, 0), Vec2(0, 640), 2));//左墙
			groundParameterVector.push_back(new EdgeParameter(Vec2(2048, 0), Vec2(2048, 640), 2));//右墙
			groundParameterVector.push_back(new EdgeParameter(Vec2(70, 456), Vec2(244, 456), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(310, 356), Vec2(402, 356), 1));//其他地板2
			groundParameterVector.push_back(new EdgeParameter(Vec2(465, 232), Vec2(573, 232), 1));//其他地板3
			groundParameterVector.push_back(new EdgeParameter(Vec2(625, 370), Vec2(718, 370), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(830, 437), Vec2(923, 437), 1));//其他地板2
			groundParameterVector.push_back(new EdgeParameter(Vec2(1031, 341), Vec2(1123, 341), 1));//其他地板3
			groundParameterVector.push_back(new EdgeParameter(Vec2(1194, 402), Vec2(1321, 402), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(1397, 400), Vec2(1489, 400), 1));//其他地板2
			groundParameterVector.push_back(new EdgeParameter(Vec2(1530, 297), Vec2(1678, 297), 1));//其他地板3
			groundParameterVector.push_back(new EdgeParameter(Vec2(1733, 385), Vec2(1962, 385), 1));//其他地板1

			level2GameParameter = new GameParameterForLevels(2, Size(2048, 640), archer, enemyParameterVector, groundParameterVector);
		}
		return level2GameParameter;

	case 3:
		//第三关
		if (level3GameParameter == NULL) {
			auto archer = new ArcherParameter(Vec2(80, 120));

			std::vector<EnemyParameter*>enemyParameterVector;
			enemyParameterVector.push_back(new EnemyParameter(Vec2(400, 120), 5, 1));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(450, 170), 5, 1));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(700, 170), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(800, 170), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(900, 170), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(300, 400), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(500, 400), 20, 4));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(800, 640), 15, 3));
			//enemyParameterVector.push_back(new EnemyParameter(Vec2(700, 170), 100, 5));

			std::vector<EdgeParameter*>groundParameterVector;  //最后的参数，1是地板，用来站的，2是墙壁
			groundParameterVector.push_back(new EdgeParameter(Vec2(0, 90), Vec2(1280, 90), 1));//地板
			groundParameterVector.push_back(new EdgeParameter(Vec2(0, 95), Vec2(0, 928), 2));//左墙
			groundParameterVector.push_back(new EdgeParameter(Vec2(1280, 95), Vec2(1280, 928), 2));//右墙
			groundParameterVector.push_back(new EdgeParameter(Vec2(600, 148), Vec2(1160, 148), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(260, 378), Vec2(830, 378), 1));//其他地板2
			groundParameterVector.push_back(new EdgeParameter(Vec2(600, 618), Vec2(1180, 618), 1));//其他地板3
			groundParameterVector.push_back(new EdgeParameter(Vec2(935, 300), Vec2(935, 619), 3));//绳子1

			level3GameParameter = new GameParameterForLevels(3, Size(1280, 928), archer, enemyParameterVector, groundParameterVector);
		}
		return level3GameParameter;

	case 4:
		//第四关
		if (level4GameParameter == NULL) {
			auto archer = new ArcherParameter(Vec2(80, 130));

			std::vector<EnemyParameter*>enemyParameterVector;
			enemyParameterVector.push_back(new EnemyParameter(Vec2(400, 430), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(500, 430), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(500, 890), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(600, 890), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(950, 180), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1050, 180), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1300, 270), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1400, 270), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1300, 770), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1400, 770), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(1600, 950), 15, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(80, 300), 20, 4));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(80, 400), 20, 4));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(80, 500), 20, 4));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(80, 600), 20, 4));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(80, 700), 20, 4));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(80, 800), 20, 4));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(80, 900), 20, 4));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(80, 1000), 20, 4));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(80, 1100), 20, 4));

			std::vector<EdgeParameter*>groundParameterVector;  //最后的参数，1是地板，用来站的，2是墙壁
			groundParameterVector.push_back(new EdgeParameter(Vec2(0, 43), Vec2(2046, 43), 1));//地板
			groundParameterVector.push_back(new EdgeParameter(Vec2(347, 180), Vec2(347, 391), 3));//绳子1
			groundParameterVector.push_back(new EdgeParameter(Vec2(59, 390), Vec2(663, 390), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(609, 540), Vec2(609, 869), 3));//绳子1
			groundParameterVector.push_back(new EdgeParameter(Vec2(95, 868), Vec2(700, 868), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(800, 153), Vec2(1213, 153), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(1620, 180), Vec2(1620, 248), 3));//绳子1
			groundParameterVector.push_back(new EdgeParameter(Vec2(1285, 247), Vec2(1892, 247), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(1343, 400), Vec2(1343, 741), 3));//绳子1
			groundParameterVector.push_back(new EdgeParameter(Vec2(1212, 740), Vec2(1868, 740), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(1562, 914), Vec2(1739, 914), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(0, 0), Vec2(0, 640), 2));//左墙
			groundParameterVector.push_back(new EdgeParameter(Vec2(2048, 0), Vec2(2048, 1280), 2));//右墙

			level4GameParameter = new GameParameterForLevels(4, Size(2048, 1280), archer, enemyParameterVector, groundParameterVector);
		}
		return level4GameParameter;

	case 5:
		//第五关
		if (level5GameParameter == NULL) {
			auto archer = new ArcherParameter(Vec2(80, 130));

			std::vector<EnemyParameter*>enemyParameterVector;
			enemyParameterVector.push_back(new EnemyParameter(Vec2(700, 120), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(800, 120), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(300, 120), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(400, 120), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(700, 180), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(800, 180), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(300, 180), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(400, 180), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(700, 250), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(800, 250), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(300, 250), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(400, 250), 10, 2));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(500, 500), 1000, 5)); 

			std::vector<EdgeParameter*>groundParameterVector;  //最后的参数，1是地板，用来站的，2是墙壁
			groundParameterVector.push_back(new EdgeParameter(Vec2(0, 0), Vec2(0, 640), 2));//左墙
			groundParameterVector.push_back(new EdgeParameter(Vec2(1024, 0), Vec2(1024, 640), 2));//右墙
			groundParameterVector.push_back(new EdgeParameter(Vec2(0, 94), Vec2(1022, 94), 1));//其他地板1
			groundParameterVector.push_back(new EdgeParameter(Vec2(276, 216), Vec2(770, 216), 1));//其他地板2
			groundParameterVector.push_back(new EdgeParameter(Vec2(352, 350), Vec2(700, 350), 1));//其他地板3

			level5GameParameter = new GameParameterForLevels(5, Size(1024, 640), archer, enemyParameterVector, groundParameterVector);
		}
		return level5GameParameter;
	default:
		return NULL;
	}
}

LevelParameter* ParameterManager::level1Parameter = NULL;
LevelParameter* ParameterManager::level2Parameter = NULL;
LevelParameter* ParameterManager::level3Parameter = NULL;
LevelParameter* ParameterManager::level4Parameter = NULL;
LevelParameter* ParameterManager::level5Parameter = NULL;
LevelParameter* ParameterManager::levelDefaultParameter = NULL;

LevelParameter* ParameterManager::getLevelParameterInstance(int _levelNum) {
	switch (_levelNum) {
	case 1:
		//level1
		if (level1Parameter == NULL) {
			level1Parameter = new LevelParameter();
			level1Parameter->levelNum = _levelNum;
			level1Parameter->blood = 100;
			level1Parameter->blue = 100;
			level1Parameter->power = 5;
			level1Parameter->levelUpExp = 50;
		}
		return level1Parameter;
	case 2:
		//level2
		if (level2Parameter == NULL) {
			level2Parameter = new LevelParameter();
			level2Parameter->levelNum = _levelNum;
			level2Parameter->blood = 200;
			level2Parameter->blue = 200;
			level2Parameter->power = 10;
			level2Parameter->levelUpExp = 100;
		}
		return level2Parameter;
	case 3:
		//level3
		if (level3Parameter == NULL) {
			level3Parameter = new LevelParameter();
			level3Parameter->levelNum = _levelNum;
			level3Parameter->blood = 300;
			level3Parameter->blue = 300;
			level3Parameter->power = 15;
			level3Parameter->levelUpExp = 150;
		}
		return level3Parameter;
	case 4:
		//level4
		if (level4Parameter == NULL) {
			level4Parameter = new LevelParameter();
			level4Parameter->levelNum = _levelNum;
			level4Parameter->blood = 400;
			level4Parameter->blue = 400;
			level4Parameter->power = 20;
			level4Parameter->levelUpExp = 200;
		}
		return level4Parameter;
	case 5:
		//level5
		if (level5Parameter == NULL) {
			level5Parameter = new LevelParameter();
			level5Parameter->levelNum = _levelNum;
			level5Parameter->blood = 500;
			level5Parameter->blue = 500;
			level5Parameter->power = 25;
			level5Parameter->levelUpExp = 250;
		}
		return level5Parameter;
	default:
		if (levelDefaultParameter == NULL) {
			levelDefaultParameter = new LevelParameter();
			levelDefaultParameter->levelNum = _levelNum;
			levelDefaultParameter->blood = _levelNum * 100;
			levelDefaultParameter->blue = _levelNum * 100;
			levelDefaultParameter->power = _levelNum * 5;
			levelDefaultParameter->levelUpExp = _levelNum * 50;
		}
		return levelDefaultParameter;
	}
}

void ParameterManager::deleteAll() {
	if (level1GameParameter != NULL){
		delete level1GameParameter->archerParameter;
		for (std::vector<EnemyParameter*>::iterator it = level1GameParameter->enemyParameter.begin(); it != level1GameParameter->enemyParameter.end(); it++) {
			delete *it;
		}
		for (std::vector<EdgeParameter*>::iterator it = level1GameParameter->edgeParameter.begin(); it != level1GameParameter->edgeParameter.end(); it++) {
			delete *it;
		}
		delete level1GameParameter;
		level1GameParameter = NULL;
	}
	if (level2GameParameter != NULL){
		delete level2GameParameter->archerParameter;
		for (std::vector<EnemyParameter*>::iterator it = level2GameParameter->enemyParameter.begin(); it != level2GameParameter->enemyParameter.end(); it++) {
			delete *it;
		}
		for (std::vector<EdgeParameter*>::iterator it = level2GameParameter->edgeParameter.begin(); it != level2GameParameter->edgeParameter.end(); it++) {
			delete *it;
		}
		delete level2GameParameter;
		level2GameParameter = NULL;
	}
	if (level3GameParameter != NULL){
		delete level3GameParameter->archerParameter;
		for (std::vector<EnemyParameter*>::iterator it = level3GameParameter->enemyParameter.begin(); it != level3GameParameter->enemyParameter.end(); it++) {
			delete *it;
		}
		for (std::vector<EdgeParameter*>::iterator it = level3GameParameter->edgeParameter.begin(); it != level3GameParameter->edgeParameter.end(); it++) {
			delete *it;
		}
		delete level3GameParameter;
		level3GameParameter = NULL;
	}
	if (level4GameParameter != NULL){
		delete level4GameParameter->archerParameter;
		for (std::vector<EnemyParameter*>::iterator it = level4GameParameter->enemyParameter.begin(); it != level4GameParameter->enemyParameter.end(); it++) {
			delete *it;
		}
		for (std::vector<EdgeParameter*>::iterator it = level4GameParameter->edgeParameter.begin(); it != level4GameParameter->edgeParameter.end(); it++) {
			delete *it;
		}
		delete level4GameParameter;
		level4GameParameter = NULL;
	}
	if (level5GameParameter != NULL){
		delete level5GameParameter->archerParameter;
		for (std::vector<EnemyParameter*>::iterator it = level5GameParameter->enemyParameter.begin(); it != level5GameParameter->enemyParameter.end(); it++) {
			delete *it;
		}
		for (std::vector<EdgeParameter*>::iterator it = level5GameParameter->edgeParameter.begin(); it != level5GameParameter->edgeParameter.end(); it++) {
			delete *it;
		}
		delete level5GameParameter;
		level5GameParameter = NULL;
	}

	if (level1Parameter != NULL) {
		delete level1Parameter;
		level1Parameter = NULL;
	}
	if (level2Parameter != NULL) {
		delete level2Parameter;
		level2Parameter = NULL;
	}
	if (level3Parameter != NULL) {
		delete level3Parameter;
		level3Parameter = NULL;
	}
	if (level4Parameter != NULL) {
		delete level4Parameter;
		level4Parameter = NULL;
	}
	if (level5Parameter != NULL) {
		delete level5Parameter;
		level5Parameter = NULL;
	}
	if (levelDefaultParameter != NULL) {
		delete levelDefaultParameter;
		levelDefaultParameter = NULL;
	}
}

int ParameterManager::currentGameLevel;
int ParameterManager::getCurrentGameLevel() {
	return currentGameLevel;
}
void ParameterManager::setCurrentGameLevel(int _currentLevel) {
	currentGameLevel = _currentLevel;
}/*

int ParameterManager::getUnlockedLevel() {
	return unlockedLevel;
}

void ParameterManager::setUnlockedLevel(int _unlockedLevel) {
	unlockedLevel = _unlockedLevel;
}*/
//地板
float ParameterManager::bottomGroundHeight = 75;
float ParameterManager::getBottomGroundHeight() {
	return bottomGroundHeight;
}

//弓箭
float ParameterManager::arrow1MaxVelocity = 600;
float ParameterManager::getArrow1MaxVelocity() {
	return arrow1MaxVelocity;
}