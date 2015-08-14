/*
创建一个羊：攻击力为5。（死亡条件：一支普通箭即可击杀）
*/

#include"Enemy4.h"

bool Enemy4::init() {
	if (!Node::init()) { return false; }
	mode = 4;
	shadowNumber = 0;
	attackShadowExist = false;
	power = ParameterManager::getCurrentGameLevel() * 20;

	//敌人的精灵
	Sprite* aEnemy = Sprite::createWithSpriteFrameName("Sheep_4.png");
	aEnemy->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemySheepMove()))));
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
	this->schedule(schedule_selector(Enemy4::setLoc), 1.0f);

	attackSprite = Sprite::createWithSpriteFrameName("Sheep_8.png");
	this->addChild(attackSprite);
	attackSprite->setPosition(Vec2::ZERO);
	attackSprite->setVisible(false);

	return true;
}

void Enemy4::setLoc(float dt){
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

Sprite* Enemy4::createDispearSprite(Vec2 position){
	Sprite* tempS = Sprite::create();
	tempS->setFlippedX(direction);

	tempS->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemySheepDeath())));
	//this->getParent()->removeChildByName(trueNumber);
	tempS->setPosition(position);

	return tempS;
}

int Enemy4::attack(){
	if (attackShadowExist == false){
		auto s = this->getEnemySprite();
		Director::getInstance()->getActionManager()->pauseTarget(s->getParent());
		s->setVisible(false);

		SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
		Vector <SpriteFrame*> temp;
		char name[20];
		memset(name, 0, 20);
		for (int i = 8; i < 13; i++){
			sprintf(name, "Sheep_%d.png", i + 1);
			SpriteFrame* sf = cache->spriteFrameByName(name);
			temp.pushBack(sf);
		}
		currentAttackAction = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(temp, 0.5f)));
		this->schedule(schedule_selector(Enemy4:: AttackEnemy), 2);
		attackSprite->runAction(currentAttackAction);
		attackSprite->setVisible(true);
		attackShadowExist = true;
	}
	attackSprite->setFlippedX(direction);

	return power;
}

void Enemy4::AttackEnemy(float dt){
	archer::getInstance()->attacked(power);
}

void Enemy4::attackCancel(){
	auto s = getEnemySprite();
	Director::getInstance()->getActionManager()->resumeTarget(s->getParent());
	s->setVisible(true);
	//this->getParent()->removeChildByName(trueNumber);
	attackShadowExist = false;

	attackSprite->stopAction(currentAttackAction);
	attackSprite->setVisible(false);
}