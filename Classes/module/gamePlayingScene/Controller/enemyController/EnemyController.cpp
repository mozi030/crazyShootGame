#include"EnemyController.h"
USING_NS_CC;
#include "../../Model/Enemy/Enemy.h"
#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../Model/archer/archer.h"


EnemyController*EnemyController::enemyController = NULL;

EnemyController::EnemyController(){}

EnemyController::~EnemyController(){
	if (enemyController != NULL){
		enemyController = NULL;
	}
}

void EnemyController::EnemyAttacked(cocos2d::Node* enemyNode) {
	auto enemy = (Enemy*)enemyNode;
	float f = enemy->getProgressBar()->getPercentage();
	//Blood 是INT型需要强制类型转换
	float b = enemy->getBlood();
	enemy->getProgressBar()->setPercentage((b - 1) / b*f);
	enemy->setBlood(enemy->getBlood() - 1);
	if (enemy->getBlood() == 0) {
		Vec2 point = enemy->getPosition();
		this->addChild(enemy->createDispearSprite(enemy->getMode(), point), 1);

		enemy->removeFromParentAndCleanup(true);
	}
}
void EnemyController::UpdateControl(float dt, cocos2d::Node*enemyNode, cocos2d::Node*_archer){

	auto enemy = (Enemy*)enemyNode;
	auto Archer = (archer*)_archer;
	float d = fabs(enemyNode->getPosition().x - _archer->getPosition().x);
	//log("logI    %f", d);
	if (d < 80){
		enemy->attack(enemy->getEnemySprite(), enemy->getMode());
	}
	else{
		//	log("Scheduler%d is pause!", enemy->getMode());
		enemy->attackCancel(enemy->getEnemySprite(), enemy->getMode());
		//enemy->unschedule("UpdateControl");
	}
}



void EnemyController::Attack(cocos2d::Node* enemyNode, cocos2d::Node* _archer) {
	auto enemy = (Enemy*)enemyNode;
	enemy->schedule(CC_CALLBACK_1(EnemyController::UpdateControl, this, enemyNode, _archer), "UpdateControl");
	//log("Schedule%d OK!", enemy->getMode());
	//	enemy->attack(enemy->getEnemySprite(), enemy->getMode());
	//float d = archer::getInstance()->getContentSize().width;

}

void EnemyController::AttackCancel(cocos2d::Node* enemyNode, cocos2d::Node* archer) {
	auto enemy = (Enemy*)enemyNode;
	enemy->attackCancel(enemy->getEnemySprite(), enemy->getMode());
}

void EnemyController::Turn(cocos2d::Node* enemyNode){
	auto enemy = (Enemy*)enemyNode;
	Sprite* stemp = enemy->getEnemySprite();
	if (stemp->isFlippedX())
		stemp->setFlippedX(false);
	else
		stemp->setFlippedX(true);
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
