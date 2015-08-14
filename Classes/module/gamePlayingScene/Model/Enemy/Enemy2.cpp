/*
创建一个战士战士：近战攻击，攻击力为10。（死亡条件：两箭才能击杀）
*/

#include"Enemy2.h"

bool Enemy2::init() {
	if (!Node::init()) { return false; }
	mode = 2;
	shadowNumber = 0;
	attackShadowExist = false;
	power = ParameterManager::getCurrentGameLevel() * 10;

	//敌人的精灵
	Sprite* aEnemy = Sprite::createWithSpriteFrameName("Soldier_1.png");
	aEnemy->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemySoldierMove()))));
	this->addChild(aEnemy, 10);

	auto aBody = PhysicsBody::createBox(aEnemy->getContentSize());
	aBody->setRotationEnable(false);
	this->setPhysicsBody(aBody);

	bitmask aBitmask = Constant::getEnemyBitmask();
	aBody->setCategoryBitmask(aBitmask.categoryBitmask);
	aBody->setCollisionBitmask(aBitmask.collisionBitmask);
	aBody->setContactTestBitmask(aBitmask.contactTestBitmask);
	aBody->setGroup(aBitmask.group);

	aBody->getFirstShape()->setTag(Constant::getEnemyTag());

	this->enemySprite = aEnemy;
	this->schedule(schedule_selector(Enemy2::setLoc), 1.0f);

	attackSprite = Sprite::create();
	this->addChild(attackSprite);
	attackSprite->setPosition(Vec2::ZERO);
	attackSprite->setVisible(false);

	return true;
}

void Enemy2::UpdateTimeToAttack(float dt){
	Vec2 vc = archer::getInstance()->getPosition();
	float Ac_x = vc.x - this->getPosition().x;
	float Ac_y = vc.y - this->getPosition().y;
	log("distance : %f ,  %f", Ac_x, Ac_y);

	if (fabs(Ac_y) < 50 && fabs(Ac_x) > 90){

		Boob();
	}

	if (vc.x < this->getPositionX()){
		this->enemySprite->setFlippedX(false);
	}
	else{
		this->enemySprite->setFlippedX(true);
	}
}
void Enemy2::Boob(){
	Sprite* Boob = Sprite::create(Constant::getEnemyBoobPath());
	Vec2 vc = archer::getInstance()->getPosition();

	this->addChild(Boob);
	auto BoobBody = PhysicsBody::createBox(Boob->getContentSize());
	Boob->setPhysicsBody(BoobBody);

	BoobBody->setVelocity(Vec2(-300, 0));
	if (vc.x < this->getPositionX()){
		Boob->setFlippedX(false);
		log("Boob true");
		BoobBody->setVelocity(Vec2(-300, 0));
	}
	else{
		Boob->setFlippedX(true);
		log("Boob False");
		BoobBody->setVelocity(Vec2(300, 0));
	}
	Boob->getPhysicsBody()->setCategoryBitmask(0x0000000F); //种类
	Boob->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	Boob->getPhysicsBody()->setCollisionBitmask(0x0000000F);
	Boob->getPhysicsBody()->setGroup(-3);
	Boob->getPhysicsBody()->setGravityEnable(false);

	Boob->getPhysicsBody()->getFirstShape()->setTag(Constant::getEnemyArrowTag());
}

void Enemy2::setLoc(float dt){
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

Sprite* Enemy2::createDispearSprite(Vec2 position){
	Sprite* tempS = Sprite::create();
	tempS->setFlippedX(direction);

	tempS->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemySoldierDeath())));
	//this->getParent()->removeChildByName(trueNumber);
	tempS->setPosition(position);

	return tempS;
}

int Enemy2::attack(){
	if (attackShadowExist == false){
		auto s = this->getEnemySprite();
		Director::getInstance()->getActionManager()->pauseTarget(s->getParent());
		s->setVisible(false);

		SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
		Vector <SpriteFrame*> temp;
		char name[20];
		memset(name, 0, 20);
		for (int i = 8; i < 17; i++){
			sprintf(name, "Soldier_%d.png", i + 1);
			SpriteFrame* sf = cache->spriteFrameByName(name);
			temp.pushBack(sf);
		}
		currentAttackAction = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(temp, 0.5f)));
		attackSprite->runAction(currentAttackAction);
		attackSprite->setVisible(true);
		attackShadowExist = true;
	}
	attackSprite->setFlippedX(direction);

	return power;
}

void Enemy2::attackCancel(){
	auto s = getEnemySprite();
	Director::getInstance()->getActionManager()->resumeTarget(s->getParent());
	s->setVisible(true);
	//this->getParent()->removeChildByName(trueNumber);
	attackShadowExist = false;

	attackSprite->stopAction(currentAttackAction);
	attackSprite->setVisible(false);
}