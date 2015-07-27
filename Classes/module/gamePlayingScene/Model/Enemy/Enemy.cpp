#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../../../public/Constant/Constant.h"
#include "Enemy.h"
#include "../archer/archer.h"

bool Enemy::init(){
	locX = ParameterManager::getVisibleSize().width;
	locY = ParameterManager::getVisibleSize().height;
	power = 0;
	blood = 0;
	mode = 0;

	return true;
}

void Enemy::setBlood(int _blood){
	blood = _blood;
}

Enemy* Enemy::setParameter(float _locX, float _locY, int _blood, int _mode){
	locX = _locX;
	locY = _locY; 

	blood = _blood;
	mode = _mode;
	setPosition(ccp(_locX, _locY));

	switch (_mode){
	case 1:{
		createEnemyOne();
		break;
	}
	case 2:{
		createEnemyTwo();
		break;
	}
	case 3:{
		createEnemyArrow();
	}
	default:
		
		break;
	}

	return this;
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

void Enemy::createEnemyOne(){
	SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(Constant::getEnemyGoblinPath());

    Sprite* aEnemy = Sprite::createWithSpriteFrameName("Goblin_1.png");
	Vector <SpriteFrame*> temp;
	char name[20];
	memset(name, 0, sizeof(name));
	for (int i = 0; i < 5; i++){
		sprintf(name, "Goblin_%d.png", i + 1);
		SpriteFrame* sf = cache -> spriteFrameByName(name);
		temp.pushBack(sf);
	}
	Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.1f);

	auto Body = PhysicsBody::createBox(aEnemy->getContentSize());
	aEnemy->setPhysicsBody(Body);
	Body->setRotationEnable(false);
	this->addChild(aEnemy, 10);
	aEnemy->getPhysicsBody()->setContactTestBitmask(0x0000F00F);
	aEnemy->getPhysicsBody()->setCategoryBitmask(0x0000F00F);
	//auto animation = AnimationCache::getInstance()->getAnimation(Constant::getEnemyAnimationName());
	Action* ac1 = RepeatForever::create(Animate::create(animation_run));
	ac1->setTag(1);
	Action* ac2 = RepeatForever::create(MoveBy::create(1, Vec2(-30, 0)));
	ac2->setTag(2);
	aEnemy->runAction(ac1);
	aEnemy->runAction(ac2);
	aEnemy->getPhysicsBody()->getFirstShape()->setTag(Constant::getEnemyTag1());
}

void Enemy::createEnemyTwo(){
	SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(Constant::getEnemySoldierPath());


	Sprite* aEnemy = Sprite::createWithSpriteFrameName("Soldier_1.png");
	//Sprite* aEnemy = Sprite::create("image\enemy\Goblin_1.png");
	Vector <SpriteFrame*> temp;
	char name[20];
	memset(name, 0, sizeof(name));
	for (int i = 0; i < 8; i++){
		sprintf(name, "Soldier_%d.png", i + 1);
		SpriteFrame* sf = cache->spriteFrameByName(name);
		temp.pushBack(sf);
	}

	Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.1f);
	auto Body = PhysicsBody::createBox(aEnemy->getContentSize());
	aEnemy->setPhysicsBody(Body);
	Body->setRotationEnable(false);
	this->addChild(aEnemy, 10);
	aEnemy->getPhysicsBody()->setContactTestBitmask(0x0000F00F);
	aEnemy->getPhysicsBody()->setCategoryBitmask(0x0000F00F);
	//auto animation = AnimationCache::getInstance()->getAnimation(Constant::getEnemyAnimationName());
	Action* ac1 = RepeatForever::create(Animate::create(animation_run));
	ac1->setTag(1);
	Action* ac2 = RepeatForever::create(MoveBy::create(1, Vec2(-30, 0)));
	ac2->setTag(2);
	aEnemy->runAction(ac1);
	this->runAction(ac2);
	aEnemy->getPhysicsBody()->getFirstShape()->setTag(Constant::getEnemyTag2());
}

Vec2 position;

void Enemy::createEnemyArrow(){
	SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(Constant::getEnemyArrowEnemyPath());


	Sprite* aEnemy = Sprite::createWithSpriteFrameName("ArrowEnemy_9.png");
	//Sprite* aEnemy = Sprite::create("image\enemy\Goblin_1.png");
	Vector <SpriteFrame*> temp;
	char name[20];
	memset(name, 0, sizeof(name));
	for (int i = 9; i < 16; i++){
		sprintf(name, "ArrowEnemy_%d.png", i + 1);
		SpriteFrame* sf = cache->spriteFrameByName(name);
		temp.pushBack(sf);
	}
	Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.2f);

	auto Body = PhysicsBody::createBox(aEnemy->getContentSize());
	aEnemy->setPhysicsBody(Body);
	Body->setRotationEnable(false);
	Body->setTag(Constant::getEnemyArrowTag());
	this->addChild(aEnemy, 10);
	aEnemy->getPhysicsBody()->setContactTestBitmask(0x0000F00F);
	aEnemy->getPhysicsBody()->setCategoryBitmask(0x0000F00F);
	//auto animation = AnimationCache::getInstance()->getAnimation(Constant::getEnemyAnimationName());
	Action* ac1 = RepeatForever::create(Animate::create(animation_run));
	ac1->setTag(1);
	aEnemy->runAction(ac1);
	//_enemy->runAction(MoveTo::create(10, Vec2(0, 30)));
	aEnemy->getPhysicsBody()->getFirstShape()->setTag(Constant::getEnemyTag3());
	//this->setContentSize(aEnemy->getContentSize());
	position = aEnemy->getPosition();
	//ÉèÖÃ¹­¼ý
	aEnemy->schedule(schedule_selector(Enemy::updateTimeToArrowAttack), 1.6f);
}

void Enemy::updateTimeToArrowAttack(float dt){

	Sprite* EnemyArrow = Sprite::create(Constant::getEnemyArrowPath());
	this->addChild(EnemyArrow);
	auto ArrowBody = PhysicsBody::createBox(EnemyArrow->getContentSize());
	EnemyArrow->setPhysicsBody(ArrowBody);

	EnemyArrow->setPosition(position.x, position.y + 100);
	float angle = atan((locY - 0) / (locX - 0)) / pi * 180;
	EnemyArrow->setRotation(angle);

	float arrowVelocityX = -fabs(EnemyArrow->getPositionX() - archer::getInstance()->getPositionX()) / 1.0;
	float arrowVelocityY = (-fabs(EnemyArrow->getPositionY() - archer::getInstance()->getPositionY()) - 0.5 * 1.0 * 1.0 * ParameterManager::getGravity().y) / 1.0;
	//float arrowVelocityX = ParameterManager::getArrowMaxVelocity() * cos((angle + 180) / 180 * pi) + 10;
	//float arrowVelocityY = ParameterManager::getArrowMaxVelocity() * sin(angle / 180 * pi) + 10;
	ArrowBody->setVelocity(Vec2(arrowVelocityX, arrowVelocityY));

	EnemyArrow->getPhysicsBody()->setContactTestBitmask(0x00000000);
	EnemyArrow->getPhysicsBody()->setCategoryBitmask(0x00000000);
}

Sprite* Enemy::createDispearSprite(int _mode,Vec2 position){
	Sprite* tempS = Sprite::create();
	SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
	char name[20];
	memset(name, 0, sizeof(name));
	Vector <SpriteFrame*> temp;
	switch (_mode)
	{
	case 1:{
		//tempS ->createWithSpriteFrameName("Goblin_1.png");
		for (int i = 10; i < 14; i++){
			sprintf(name, "Goblin_%d.png", i + 1);
			SpriteFrame* sf = cache->getSpriteFrameByName(name);
			temp.pushBack(sf);
		}

		Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.5f);
		tempS->runAction(Animate::create(animation_run));
		tempS->setPosition(position);
		break;
	}
	case 2:{
		//tempS->createWithSpriteFrameName("Soldier_1.png");
		for (int i = 18; i < 23; i++){
			sprintf(name, "Soldier_%d.png", i + 1);
			SpriteFrame* sf = cache->getSpriteFrameByName(name);
			temp.pushBack(sf);
		}

		Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.5f);
		tempS->runAction(Repeat::create(Animate::create(animation_run),1));
		tempS->setPosition(position);
		// this->addChild(s);
		break;
	}
	case 3:{
		//tempS->createWithSpriteFrameName("ArrowEnemy_1.png");
		for (int i = 18; i < 22; i++){
			sprintf(name, "ArrowEnemy_%d.png", i + 1);
			SpriteFrame* sf = cache->getSpriteFrameByName(name);
			temp.pushBack(sf);
		}

		Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.5f);
		tempS->runAction(RepeatForever::create(Animate::create(animation_run)));
		tempS->setPosition(position);
		break;
	}
	default:
		break;
	}
	return tempS;
}

int Enemy::attack(Sprite* s, int _mode){
	switch (_mode)
	{
	case 1:{
			   Action* ac1 = Director::getInstance()->getActionManager()->getActionByTag(1, s);
			   Action* ac2 = Director::getInstance()->getActionManager()->getActionByTag(2, this);
			   s->stopAction(ac1);
			   s->stopAction(ac2);
			   SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
			   Vector <SpriteFrame*> temp = Vector <SpriteFrame*> ::Vector();
			   char name[20];
			   memset(name, 0, 10);
			   for (int i = 6; i < 10; i++){
				   sprintf(name, "Goblin_%d.png", i + 1);
				   SpriteFrame* sf = cache->spriteFrameByName(name);
				   temp.pushBack(sf);
			   }

			   Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.5f);
			   s->runAction(Animate::create(animation_run));
			   break;
	}
	case 2:{
			   Action* ac1 = Director::getInstance()->getActionManager()->getActionByTag(1, s);
			   Action* ac2 = Director::getInstance()->getActionManager()->getActionByTag(2, this);
			   s->stopAction(ac1);
			   s->stopAction(ac2);
			   SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
			   Vector <SpriteFrame*> temp = Vector <SpriteFrame*> ::Vector();
			   char name[20];
			   memset(name, 0, 10);
			   for (int i = 9; i < 17; i++){
				   sprintf(name, "Soldier_%d.png", i + 1);
				   SpriteFrame* sf = cache->spriteFrameByName(name);
				   temp.pushBack(sf);
			   }

			   Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.5f);
			   s->runAction(Animate::create(animation_run));
			   // this->addChild(s);
			   break;
	}
	case 3:{
			   
	}
	default:
		break;
	}
	return power;
}