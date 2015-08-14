#include "Enemy.h"

int Enemy::getShadowNumber(){
	return shadowNumber++;
}

void Enemy::onEnter(){
	Node::onEnter();
}

void Enemy::onExit(){
	Node::onExit();
}

void Enemy::setBlood(int _blood){
	blood = _blood;
}

void Enemy::setParameter(Vec2 initialLocation, int _blood){
	blood = _blood;
	setPosition(initialLocation);

	createProgressTimer();
}

void Enemy::createProgressTimer() {
	Size visibleSize = ParameterManager::getVisibleSize();

	auto progressSprite2 = Sprite::create(Constant::getEnemyBloodBackPath());
	progressSprite2->setPosition(0, 50);
	this->addChild(progressSprite2, 1);

	auto progressSprite1 = Sprite::create(Constant::getEnemyBloodForePath());
	progressTimer = ProgressTimer::create(progressSprite1);
	progressTimer->setPosition(0, 50);
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setMidpoint(Point(0, 1));
	progressTimer->setBarChangeRate(Point(1, 0));
	progressTimer->setPercentage(99.99f);
	this->addChild(progressTimer, 2);
}

int Enemy::getBlood(){
	return blood;
}

int Enemy::getPower(){
	return power;
}

int Enemy::getMode(){
	return mode;
}

ProgressTimer* Enemy::getProgressTimer(){
	return progressTimer;
}

Sprite* Enemy::getEnemySprite(){
	return enemySprite;
}
