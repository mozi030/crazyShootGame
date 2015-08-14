/*
创建一个哥布林：攻击力为5。（死亡条件：一支普通箭即可击杀）
*/

#include"Enemy5.h"
#include"Enemy1.h"
#include"Enemy2.h"
#include"Enemy3.h"
#include"sqlite3\include\sqlite3.h"
#include"Enemy4.h"
#include"../../Controller/enemyController/EnemyController.h"

bool Enemy5::init() {
	//sqlite3*db;
	//std::string a = "sadf";
	//int result = sqlite3_open(a.c_str(), &db);

	if (!Node::init()) { return false; }
	mode = 5;
	shadowNumber = 0;
	attackShadowExist = false;
	UseOfAddBlood = false;
	UseOfAttack = false;
	UseOfCall = false;
	power = ParameterManager::getCurrentGameLevel() * 25;

	//敌人的精灵
	Sprite* aEnemy = Sprite::createWithSpriteFrameName("Boss_17.png");
	ActionInterval* NormalOnce = Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal()));
	Action* Normal = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal())));
	aEnemy->runAction(Normal);
	this->addChild(aEnemy, 10);

	auto aBody = PhysicsBody::createBox(aEnemy->getContentSize());
	aBody->setRotationEnable(false);
	this->setPhysicsBody(aBody);
	aBody->setCategoryBitmask(0x000000FF); //种类
	aBody->setContactTestBitmask(0x000000FF);
	aBody->setCollisionBitmask(0x000000FF);
	aBody->setGroup(-3);
	aBody->getFirstShape()->setTag(Constant::getEnemyTag());

	this->enemySprite = aEnemy;
	//this->schedule(schedule_selector(Enemy5::setLoc), 1.0f);

	attackSprite = Sprite::create();
	this->addChild(attackSprite);
	attackSprite->setPosition(Vec2::ZERO);
	attackSprite->setVisible(false);
	AttackMode =7.5;
	srand((int)time(NULL));
	this->schedule(CC_CALLBACK_1(Enemy5::useAbility, this, Normal, NormalOnce), AttackMode, CC_REPEAT_FOREVER, 0, "useAbility");
	
	return true;
}



void Enemy5::useAbility(float dt, Action* Normal, ActionInterval*NormalOnce){
	/*5.5*/
	Sequence * AttackOnce = Sequence::create(
																	    Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal())),
																		Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal())),
																		Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal())),
																		Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossAttack())),
																		Spawn::create(CallFunc::create(this, callfunc_selector(Enemy5::attackNormal)),
																							  Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal())),
																														 Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal()))
																							   )),
																		NULL);
	Sequence * AttackCall = Sequence::create(
																	Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal())),
																	/*Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossAttack())),
																	Spawn::create(CallFunc::create(this, callfunc_selector(Enemy5::attackNormal)),
																						  Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal())),
																												     Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal()))
																							)),*/
																	 Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossCall())),
																	 Spawn::create(
																							CallFunc::create(this, callfunc_selector(Enemy5::attackCall)),
																							Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal())),
																													   Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossNormal()))
																							 )),
																	 NULL);
	/*Sequence * AttackAddBlood = Sequence::create(NormalOnce, 
																	 NormalOnce,
																	 NormalOnce,
																	 Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossAttack())), 
																	// Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossCall())),
																	// Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossCall())), 
																	 NULL);*/
	if (this->getProgressTimer()->getPercentage() > 51.0f){
		if (!getUseOfAttack()){
			this->enemySprite->stopAction(Normal);
			setUseOfAttack(true);
		}
		this->enemySprite->runAction(AttackOnce);
	}
	else if (this->getProgressTimer()->getPercentage() <= 50.0f){
		if (!getUseOfAttack()){
			this->enemySprite->stopAction(Normal);
			setUseOfAttack(true);
		}
		this->enemySprite->runAction(AttackCall);
	}
	else{

	}
}

void Enemy5::attackNormal(){	
	Vec2 archerLoc = archer::getInstance()->getPosition();
	Sprite* Attack = Sprite::createWithSpriteFrameName("BossAttack_1.png");
	Attack->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossAttackReal())),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, Attack)),//执行完成后立刻销毁该对象
		NULL));
	for (int i = 0; i < 100; i++){
		float PositionX = rand() % 1024;
		log("%f", PositionX);
	}

	
	float PositionX = rand() % 1024;
	float PositionY = archer::getInstance()->getPositionY() - 80;
	float archerPositionX = archer::getInstance()->getPositionX();
	enemyLoc1 = Vec2(PositionX,  archer::getInstance()->getPositionY() - 80);
	Attack->setAnchorPoint(Vec2(0.5, 0));
	Attack->setPosition(Vec2(PositionX, PositionY));
	this->getParent()->addChild(Attack);


	Attack->scheduleOnce(CC_CALLBACK_1(Enemy5::DelayAttack, this, enemyLoc1, Attack), 1.5f, "DelayAttack");
	/*if (this->getProgressTimer()->getPercentage() <= 50.0f){
		AttackMode = 20;
		//this->schedule(CC_CALLBACK_1(Enemy5::useAbility, this, Normal, NormalOnce), AttackMode, CC_REPEAT_FOREVER, 0, "useAbility");
	}*/
}

void Enemy5::DelayAttack(float dt, Vec2 _enemyLoc1, Sprite* Attack){
	Vec2 archerLoc = archer::getInstance()->getPosition();
	log("enemyLocX:%f   archerLoc.x:%f   Size:%f", enemyLoc1.x, archer::getInstance()->getPositionX(), Attack->getContentSize().width);
	log("Result:%f\n", fabs(enemyLoc1.x - archerLoc.x) - Attack->getContentSize().width / 2);
	if (fabs(enemyLoc1.x - archerLoc.x) <= Attack->getContentSize().width / 2){
		archer::getInstance()->attacked(30);
	}
}


void Enemy5::attackCall(){
	Vec2 archerLoc = archer::getInstance()->getPosition();
	Sprite* Attack = Sprite::createWithSpriteFrameName("BossAttack_31.png");
	Attack->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyBossAttackCall())),
		CallFunc::create(CC_CALLBACK_0(Enemy5::addEnemy, this)),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, Attack)),//执行完成后立刻销毁该对象
		NULL));
	srand((int)time(0));
	enemyLoc2 = Vec2(rand() % 800, archer::getInstance()->getPositionY() - 40);
	//enemyLoc2 = Vec2(rand() % 800, archer::getInstance()->getPositionY() - 40);
	Attack->setAnchorPoint(Vec2(0.5, 0));
	Attack->setPosition(enemyLoc2);
	this->getParent()->addChild(Attack);
}

void Enemy5::addEnemy(){
	Enemy *aEnemy = NULL;
	Vec2 smallEnmeyPosition = enemyLoc2;
	int  _blood = 15;
	srand((int)time(0));	
	int  _mode = 0;
	while (_mode == 0){
		_mode = rand() % 5;
	}
	switch (_mode){
	case 1:
		aEnemy = Enemy1::create();
		aEnemy->setParameter(smallEnmeyPosition, _blood);
		this->getParent()->addChild(aEnemy);
		break;
	case 2:
		aEnemy = Enemy2::create();
		aEnemy->setParameter(smallEnmeyPosition, _blood);
		this->getParent()->addChild(aEnemy);
		break;
	case 3:
		aEnemy = Enemy3::create();
		aEnemy->setParameter(smallEnmeyPosition, _blood);
		this->getParent()->addChild(aEnemy);
		break;
	case 4:
		aEnemy = Enemy4::create();
		aEnemy->setParameter(smallEnmeyPosition, _blood);
		this->getParent()->addChild(aEnemy);
		break;
	default:
		break;
	}
	EnemyController::getInstance()->AddAenemy();
}

void Enemy5::attackAddBlood(){

}

bool Enemy5::getUseOfAddBlood(){
	return UseOfAddBlood;
}

bool Enemy5::getUseOfCall(){
	return UseOfCall;
}

bool Enemy5::getUseOfAttack(){
	return UseOfAttack;
}

void Enemy5::setgetUseOfAddBlood(bool _set){
	UseOfAddBlood = _set;
}

void Enemy5::setUseOfCall(bool _set){
	UseOfCall = _set;
}

void Enemy5::setUseOfAttack(bool _set){
	UseOfAttack = _set;
}

void Enemy5::setLoc(float dt){
	Vec2 vc = archer::getInstance()->getPosition();

	int flag = 1;
	float Ac_x = vc.x - this->getPosition().x;
	float Ac_y = vc.y - this->getPosition().y;
	if (Ac_x > 0){
		direction = true;
	}
	else{
		direction = false;
		flag = -1;
	}
	enemySprite->setFlippedX(direction);
	if (attackShadowExist == false)
		this->runAction(MoveBy::create(1, Point(30 * flag, 0)));
}

Sprite* Enemy5::createDispearSprite(Vec2 position){
	Sprite* tempS = Sprite::create();
	tempS->setFlippedX(direction);

	tempS->runAction(FadeOut::create(5));
	//this->getParent()->removeChildByName(trueNumber);
	tempS->setPosition(position);

	return tempS;
}

int Enemy5::attack(){
	if (attackShadowExist == false){
		auto s = this->getEnemySprite();
		Director::getInstance()->getActionManager()->pauseTarget(s->getParent());
		s->setVisible(false);

		Animation *running = Animation::create();
		for (int i = 0; i < 17; i++){
			char FileName[128] = { 0 };
			sprintf(FileName, "GamePlayingScene/enemy/Boss/fly/fly-%d.png", i);
			running->addSpriteFrameWithFileName(FileName);
		}
		running->setDelayPerUnit(2.0f / 17.0f);

		currentAttackAction = RepeatForever::create(Animate::create(running));
		this->schedule(schedule_selector(Enemy5::AttackEnemy), 2);
		attackSprite->runAction(currentAttackAction);
		attackSprite->setVisible(true);
		attackShadowExist = true;
	}
	attackSprite->setFlippedX(!direction);

	return power;
}

void Enemy5::AttackEnemy(float dt){
	archer::getInstance()->attacked(power);
}

void Enemy5::attackCancel(){
	auto s = getEnemySprite();
	Director::getInstance()->getActionManager()->resumeTarget(s->getParent());
	s->setVisible(true);
	//this->getParent()->removeChildByName(trueNumber);
	attackShadowExist = false;

	attackSprite->stopAction(currentAttackAction);
	attackSprite->setVisible(false);
}