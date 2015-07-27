#include"EnemyController.h"
USING_NS_CC;
#include "../../Model/Enemy/Enemy.h"
#include"../../../../public/parameterManager/ParameterManager.h"

EnemyController*EnemyController::enemyController = NULL;

EnemyController::EnemyController(){}

EnemyController::~EnemyController(){
	if (enemyController != NULL){
		enemyController = NULL;
	}
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
	auto gameEnemyParameter = ParameterManager::getLevelInstance(ParameterManager::getCurrentLevel())->enemyParameter;
	for (std::vector<EnemyParameter*>::iterator it = gameEnemyParameter.begin(); it != gameEnemyParameter.end(); it++) {
		auto aEnemy = Enemy::create();
		aEnemy->setParameter((*it)->initialPosition.x, (*it)->initialPosition.y, (*it)->blood, (*it)->mode);
		this->addChild(aEnemy);
	}

	return true;
}
