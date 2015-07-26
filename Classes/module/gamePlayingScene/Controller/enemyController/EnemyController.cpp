#include"EnemyController.h"
USING_NS_CC;
#include "../../Model/Enemy/Enemy.h"

EnemyController*EnemyController::enemyController = NULL;

EnemyController::EnemyController(){}

EnemyController::~EnemyController(){
	enemyController = NULL;
}

void EnemyController::EnemyAttacked(cocos2d::Node* enemyNode, Vec2 position) {
	auto enemy = (Enemy*)enemyNode;
	enemy->setBlood(enemy->getBlood() - 1);
	if (enemy->getBlood() == 0) {
		this->addChild(enemy->createDispearSprite(enemy->getMode(), position), 1);

		//enemySprite->removeFromParentAndCleanup(true);
		enemy->removeFromParentAndCleanup(true);
	}
}

EnemyController* EnemyController::getInstance() {
	if (enemyController == NULL) {
		enemyController = EnemyController::create();
	}
	return enemyController;
}

bool EnemyController::init() {

	auto t = Enemy::create();
	auto i = Enemy::create();
	i->setParameter(1000, 200,1, 1);
	t->setParameter(500, 200, 2, 2);
	this->addChild(t);
	this->addChild(i);

	return true;
}
