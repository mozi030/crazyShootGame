/*
创建一个哥布林：攻击力为5。（死亡条件：一支普通箭即可击杀）
*/

#include"Enemy1.h"

bool Enemy1::init() {
	if (!Node::init()) { return false; }
	mode = 1;
	shadowNumber = 0;
	attackShadowExist = false;
	power = ParameterManager::getCurrentGameLevel() * 5;

	//敌人的精灵
	Sprite* aEnemy = Sprite::createWithSpriteFrameName("Goblin_1.png");
	aEnemy->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyGoblinMove()))));
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
	this->schedule(schedule_selector(Enemy1::setLoc), 1.0f);

	attackSprite = Sprite::createWithSpriteFrameName("Goblin_6.png");
	this->addChild(attackSprite);
	attackSprite->setPosition(Vec2::ZERO);
	attackSprite->setVisible(false);

	return true;
}

void Enemy1::setLoc(float dt){
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

Sprite* Enemy1::createDispearSprite(Vec2 position){
	Sprite* tempS = Sprite::create();
	tempS->setFlippedX(direction);

	tempS->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyGoblinDeath())));
	//this->getParent()->removeChildByName(trueNumber);
	tempS->setPosition(position);
	
	return tempS;
}

int Enemy1::attack(){
	if (attackShadowExist == false){
		auto s = this->getEnemySprite();
		Director::getInstance()->getActionManager()->pauseTarget(s->getParent());
		s->setVisible(false);

		SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
		Vector <SpriteFrame*> temp;
		char name[20];
		memset(name, 0, 20);
		for (int i = 6; i < 9; i++){
			sprintf(name, "Goblin_%d.png", i + 1);
			SpriteFrame* sf = cache->spriteFrameByName(name);
			temp.pushBack(sf);
		}
		currentAttackAction = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(temp, 0.5f)));
		this->schedule(schedule_selector(Enemy1::AttackArcher), 2);
		attackSprite->runAction(currentAttackAction);
		attackSprite->setVisible(true);
		attackShadowExist = true;
	}
	attackSprite->setFlippedX(direction);

	return power;
}

void Enemy1::AttackArcher(float dt){
	archer::getInstance()->attacked(power);
}

void Enemy1::attackCancel(){
	auto s = getEnemySprite();
	Director::getInstance()->getActionManager()->resumeTarget(s->getParent());
	s->setVisible(true);
	//this->getParent()->removeChildByName(trueNumber);
	attackShadowExist = false;

	attackSprite->stopAction(currentAttackAction);
	attackSprite->setVisible(false);
}