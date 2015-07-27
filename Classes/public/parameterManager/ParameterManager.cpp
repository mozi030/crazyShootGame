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

GameParameterForLevels::GameParameterForLevels(int _levelNum, ArcherParameter* _archerParameter, std::vector<EnemyParameter*> _enemyParameter) {
	levelNum = _levelNum;
	archerParameter = _archerParameter;
	enemyParameter = _enemyParameter;
}

//全局参数
int ParameterManager::unlockedLevel = 1;
int ParameterManager::currentLevel = 1;

float ParameterManager::arrow1MaxVelocity = 600;
float ParameterManager::getArrow1MaxVelocity() {
	return arrow1MaxVelocity;
}

//float ParameterManager::enemyMovingTime = 60;
//float ParameterManager::getEnemyMovingTime() {
//	return enemyMovingTime;
//}

Vec2 ParameterManager::gravity = Vec2(0, -100);
Vec2 ParameterManager::getGravity() {
	return gravity;
}

Size ParameterManager::visibleSize = Size(1024,640);
Size ParameterManager::getVisibleSize() {
	return visibleSize;
}

GameParameterForLevels* ParameterManager::level1GameParameter = NULL;

GameParameterForLevels* ParameterManager::getLevelInstance(int _levelNum) {
	switch (_levelNum) {
	case 1:
		if (level1GameParameter == NULL) {
			auto archer = new ArcherParameter(Vec2(100, 200));

			std::vector<EnemyParameter*>enemyParameterVector;
			//enemyParameterVector.push_back(new EnemyParameter(Vec2(800, 200), 3, 1));
			//enemyParameterVector.push_back(new EnemyParameter(Vec2(400, 200), 2, 1));
			//enemyParameterVector.push_back(new EnemyParameter(Vec2(800, 400), 3, 2));
			//enemyParameterVector.push_back(new EnemyParameter(Vec2(400, 400), 2, 2));
			//enemyParameterVector.push_back(new EnemyParameter(Vec2(800, 200), 3, 3));
			//enemyParameterVector.push_back(new EnemyParameter(Vec2(400, 200), 2, 3));
			//enemyParameterVector.push_back(new EnemyParameter(Vec2(800, 400), 3, 3));
			enemyParameterVector.push_back(new EnemyParameter(Vec2(400, 400), 2, 3));

			level1GameParameter = new GameParameterForLevels(1, archer, enemyParameterVector);
		}
		return level1GameParameter;

	case 2:
	case 3:
		return NULL;
	}
}

void ParameterManager::deleteAll() {
	if (level1GameParameter == NULL) return;
	delete level1GameParameter->archerParameter;
	for (std::vector<EnemyParameter*>::iterator it = level1GameParameter->enemyParameter.begin(); it != level1GameParameter->enemyParameter.end(); it++) {
		delete *it;
	}
	delete level1GameParameter;
	level1GameParameter = NULL;
}

int ParameterManager::getCurrentLevel() {
	return currentLevel;
}

void ParameterManager::setCurrentLevel(int _currentLevel) {
	currentLevel = _currentLevel;
}

int ParameterManager::getUnlockedLevel() {
	return unlockedLevel;
}

void ParameterManager::setUnlockedLevel(int _unlockedLevel) {
	unlockedLevel = _unlockedLevel;
}