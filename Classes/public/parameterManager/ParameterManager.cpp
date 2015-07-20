#include"ParameterManager.h"

float ParameterManager::arrowMaxVelocity = 600;
float ParameterManager::enemyMovingTime = 60;
Vec2 ParameterManager::gravity = Vec2(0, -100);

Size ParameterManager::visibleSize = Size(1000,650);

float ParameterManager::getArrowMaxVelocity() {
	return arrowMaxVelocity;
}

float ParameterManager::getEnemyMovingTime() {
	return enemyMovingTime;
}

Vec2 ParameterManager::getGravity() {
	return gravity;
}

Size ParameterManager::getVisibleSize() {
	return visibleSize;
}