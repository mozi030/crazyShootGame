#include"EnemyController.h"

EnemyController*EnemyController::enemyController = NULL;

EnemyController::EnemyController(){}

EnemyController::~EnemyController(){
	if (enemyController != NULL){
		enemyController->removeFromParentAndCleanup(true);
		enemyController = NULL;
	}
}

EnemyController* EnemyController::getInstance() {
	if (enemyController == NULL) {
		enemyController = EnemyController::create();
	}
	return enemyController;
}

bool EnemyController::init() {
	auto gameEnemyParameter = ParameterManager::getGameParameterInstance(ParameterManager::getCurrentGameLevel())->enemyParameter;
	totalEnemyNum = gameEnemyParameter.size();

	for (std::vector<EnemyParameter*>::iterator it = gameEnemyParameter.begin(); it != gameEnemyParameter.end(); it++) {
		Enemy* aEnemy = NULL;
		switch ((*it)->mode) {
		case 1:
			aEnemy = Enemy1::create();
			aEnemy->setParameter((*it)->initialPosition, ParameterManager::getCurrentGameLevel() * (*it)->blood);
			this->addChild(aEnemy);
			break;
		case 2:
			aEnemy = Enemy2::create();
			aEnemy->setParameter((*it)->initialPosition, ParameterManager::getCurrentGameLevel() * (*it)->blood);
			this->addChild(aEnemy);
			break;
		case 3:
			aEnemy = Enemy3::create();
			aEnemy->setParameter((*it)->initialPosition, ParameterManager::getCurrentGameLevel() * (*it)->blood);
			this->addChild(aEnemy);
			break;
		case 4:
			aEnemy = Enemy4::create();
			aEnemy->setParameter((*it)->initialPosition, ParameterManager::getCurrentGameLevel() * (*it)->blood);
			this->addChild(aEnemy);
			break;
		case 5:
			aEnemy = Enemy5::create();
			aEnemy->setParameter((*it)->initialPosition, ParameterManager::getCurrentGameLevel() * (*it)->blood);
			this->addChild(aEnemy);
			break;
		default:
			break;
		}
		allEnemy.pushBack(aEnemy);
	}

	return true;
}

void EnemyController::EnemyAttacked(cocos2d::Node* enemyNode, cocos2d::Node* archerArrowNode) {
	auto enemy = (Enemy*)enemyNode;
	int damage = ((arrow*)archerArrowNode)->getPower();

	float f = enemy->getProgressTimer()->getPercentage();
	//Blood 是INT型需要强制类型转换
	int initialBlood = enemy->getBlood();
	int currentBlood = initialBlood - damage;
	if (currentBlood <= 0) currentBlood = 0;
	enemy->getProgressTimer()->setPercentage(f * currentBlood / initialBlood);
	enemy->setBlood(currentBlood);

	//受伤动画
	string s = CCString::createWithFormat("%d", damage)->_string;
	for (int i = 0; i < s.length(); i++) {
		char FileName[128] = { 0 };
		sprintf(FileName, "GamePlayingScene/enemy/number/num_%c.png", s[i]);
		auto number = Sprite::create(FileName);
		number->setPosition(Vec2(enemy->getContentSize().width / 2 + i * 30, enemy->getContentSize().height + 15));
		enemy->addChild(number, 1);
		auto move = JumpTo::create(0.8, Vec2(enemy->getContentSize().width / 2 + i * 30, enemy->getContentSize().height + 65), 50, 1);
		auto fadeout = FadeOut::create(1.0);
		auto action = Sequence::create(move, fadeout, NULL);
		number->runAction(action);
	}
	if (currentBlood <= 0) {
		totalEnemyNum--;
		for (Vector<Enemy*> ::iterator it = allEnemy.begin(); it != allEnemy.end(); it++){
			if (*it == enemy){
				allEnemy.erase(it);
				break;
			}
		}
		Vec2 point = enemy->getPosition();
		auto archer_ = archer::getInstance();
		archer_->killEnemy(enemy->getMode());
		if (enemy->getMode() == 1) {
			this->addChild(((Enemy1*)enemy)->createDispearSprite(point), 1);
		}
		else if (enemy->getMode() == 2) {
			this->addChild(((Enemy2*)enemy)->createDispearSprite(point), 1);
		}
		else if (enemy->getMode() == 3) {
			this->addChild(((Enemy3*)enemy)->createDispearSprite(point), 1);
		}
		else if (enemy->getMode() == 4) {
			this->addChild(((Enemy4*)enemy)->createDispearSprite(point), 1);
		}
		else if (enemy->getMode() == 5) {
			//this->addChild(((Enemy5*)enemy)->createDispearSprite(point), 1);
		}
		enemy->removeFromParentAndCleanup(true);
	}
}

void EnemyController::Attack(cocos2d::Node* enemyNode, cocos2d::Node* _archer) {
	Enemy* enemy = (Enemy*)enemyNode;
	if (enemy->getMode() == 1) {
		enemy = (Enemy1*)enemy;
	}
	else if (enemy->getMode() == 2) {
		enemy = (Enemy2*)enemy;
	}
	else if (enemy->getMode() == 3) {
		enemy = (Enemy3*)enemy;
	}
	else if (enemy->getMode() == 4) {
		enemy = (Enemy4*)enemy;
	}
	else if (enemy->getMode() == 5) {
		enemy = (Enemy5*)enemy;
	}

	enemy->schedule(CC_CALLBACK_1(EnemyController::UpdateControl, this, enemyNode, _archer), "UpdateControl");
}

void EnemyController::UpdateControl(float dt, cocos2d::Node*enemyNode, cocos2d::Node*_archer){
	Enemy* enemy = (Enemy*)enemyNode;
	if (enemy->getMode() == 1) {
		enemy = (Enemy1*)enemy;
	}
	else if (enemy->getMode() == 2) {
		enemy = (Enemy2*)enemy;
	}
	else if (enemy->getMode() == 3) {
		enemy = (Enemy3*)enemy;
	}
	else if (enemy->getMode() == 4) {
		enemy = (Enemy4*)enemy;
	}
	else if (enemy->getMode() == 5) {
		enemy = (Enemy5*)enemy;
	}
	auto Archer = (archer*)_archer;
	float distanceX = fabs(enemyNode->getPosition().x - _archer->getPosition().x);
	float distanceY = fabs(enemyNode->getPosition().y - _archer->getPosition().y);

	if (enemy->getMode() <= 4) {
		if ((distanceX < 90) && (distanceY < 100)){
			enemy->attack();
		}
		else{
			enemy->attackCancel();
		}
	}
	else {
		if ((distanceX < 285 / 2) && (distanceY < 239 / 2)){
			enemy->attack();
		}
		else{
			enemy->attackCancel();
		}
	}

}

void EnemyController::AttackCancel(cocos2d::Node* enemyNode, cocos2d::Node* archer) {
	Enemy* enemy = (Enemy*)enemyNode;
	if (enemy->getMode() == 1) {
		enemy = (Enemy1*)enemy;
	}
	else if (enemy->getMode() == 2) {
		enemy = (Enemy2*)enemy;
	}
	else if (enemy->getMode() == 3) {
		enemy = (Enemy3*)enemy;
	}
	else if (enemy->getMode() == 4) {
		enemy = (Enemy4*)enemy;
	}

	enemy->attackCancel();
}

void EnemyController::Turn(cocos2d::Node* enemyNode){
	Enemy* enemy = (Enemy*)enemyNode;
	if (enemy->getMode() == 1) {
		enemy = (Enemy1*)enemy;
	}
	else if (enemy->getMode() == 2) {
		enemy = (Enemy2*)enemy;
	}
	else if (enemy->getMode() == 3) {
		enemy = (Enemy3*)enemy;
	}
	else if (enemy->getMode() == 4) {
		enemy = (Enemy4*)enemy;
	}

	Sprite* stemp = enemy->getEnemySprite();
	if (stemp->isFlippedX())
		stemp->setFlippedX(false);
	else
		stemp->setFlippedX(true);
}

void EnemyController::gameEndedAndRemove() {
	for (int i = 0; i < allEnemy.size(); i++) {
		allEnemy.at(i)->removeFromParentAndCleanup(true);
	}
	this->pause();
}

void EnemyController::AddAenemy(){
	totalEnemyNum++;
}