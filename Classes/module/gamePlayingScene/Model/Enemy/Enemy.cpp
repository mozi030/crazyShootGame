#include "Enemy.h"


Enemy::Enemy(){
	locX = ParameterManager::getVisibleSize().width;
	locY = ParameterManager::getVisibleSize().height;
	power = 0;
	blood = 0;
	mode = 0;
}

void Enemy::setBlood(int _blood){
	blood = _blood;
}

Enemy* Enemy::createEnemy(float _locX, float _locY, int _blood, int _mode){	
	locX = _locX;
	locY = _locY;

	blood = _blood;
	mode = _mode;
	setPosition(ccp(_locX, _locY));

	switch (_mode){
	case 1:{
			   createEnemyOne(this);//this 指针是指的是调用CreateEnemy的那个对象
			   break;
	}
	case 2:{
			   createEnemyTwo(this);
			   break;
	}
	case 3:{
			   createEnemyArrow(this);
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

void Enemy::createEnemyOne(Enemy*_enemy){
	_enemy->blood = 1;
	_enemy->power = 5;
	
	SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(Constant::getEnemyGoblinPath());


    Sprite* aEnemy = Sprite::createWithSpriteFrameName("Goblin_1.png");
	//Sprite* aEnemy = Sprite::create("image\enemy\Goblin_1.png");
	Vector <SpriteFrame*> temp = Vector <SpriteFrame*> ::Vector();
	char name[20];
	memset(name, 0, 10);
	for (int i = 0; i < 5; i++){
		sprintf(name, "Goblin_%d.png", i + 1);
		SpriteFrame* sf = cache -> spriteFrameByName(name);
		temp.pushBack(sf);
	}

	Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.1f);
	auto Body = PhysicsBody::createBox(aEnemy->getContentSize());
	aEnemy->setPhysicsBody(Body);
	Body->setRotationEnable(false);
	_enemy->addChild(aEnemy, 10);
	aEnemy->getPhysicsBody()->setContactTestBitmask(0x0000F00F);
	aEnemy->getPhysicsBody()->setCategoryBitmask(0x0000F00F);
	//auto animation = AnimationCache::getInstance()->getAnimation(Constant::getEnemyAnimationName());
	Action* ac1 = RepeatForever::create(Animate::create(animation_run));
	ac1->setTag(1);
	Action* ac2 = MoveTo::create(20, Vec2(0, 30));
	ac2->setTag(2);
	aEnemy->runAction(ac1);
	_enemy->runAction(ac2);
	aEnemy->getPhysicsBody()->getFirstShape()->setTag(Constant::getEnemyTag1());
}

void Enemy::createEnemyTwo(Enemy*_enemy){
	blood = 2;
	power = 10;
	SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(Constant::getEnemySoldierPath());


	Sprite* aEnemy = Sprite::createWithSpriteFrameName("Soldier_1.png");
	//Sprite* aEnemy = Sprite::create("image\enemy\Goblin_1.png");
	Vector <SpriteFrame*> temp = Vector <SpriteFrame*> ::Vector();
	char name[20];
	memset(name, 0, 10);
	for (int i = 0; i < 8; i++){
		sprintf(name, "Soldier_%d.png", i + 1);
		SpriteFrame* sf = cache->spriteFrameByName(name);
		temp.pushBack(sf);
	}

	Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.1f);
	auto Body = PhysicsBody::createBox(aEnemy->getContentSize());
	aEnemy->setPhysicsBody(Body);
	Body->setRotationEnable(false);
	_enemy->addChild(aEnemy, 10);
	aEnemy->getPhysicsBody()->setContactTestBitmask(0x0000F00F);
	aEnemy->getPhysicsBody()->setCategoryBitmask(0x0000F00F);
	//auto animation = AnimationCache::getInstance()->getAnimation(Constant::getEnemyAnimationName());
	Action* ac1 = RepeatForever::create(Animate::create(animation_run));
	ac1->setTag(1);
	Action* ac2 = MoveTo::create(20, Vec2(0, 30));
	ac2->setTag(2);
	aEnemy->runAction(ac1);
	_enemy->runAction(ac2);
	aEnemy->getPhysicsBody()->getFirstShape()->setTag(Constant::getEnemyTag2());
}

void Enemy::createEnemyArrow(Enemy* _enemy){
	blood = 2;
	power = 10;
	SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(Constant::getEnemyArrowEnemyPath());


	Sprite* aEnemy = Sprite::createWithSpriteFrameName("ArrowEnemy_9.png");
	//Sprite* aEnemy = Sprite::create("image\enemy\Goblin_1.png");
	Vector <SpriteFrame*> temp = Vector <SpriteFrame*> ::Vector();
	char name[20];
	memset(name, 0, 10);
	for (int i = 9; i < 16; i++){
		sprintf(name, "ArrowEnemy_%d.png", i + 1);
		SpriteFrame* sf = cache->spriteFrameByName(name);
		temp.pushBack(sf);
	}

	Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.2f);

	auto Body = PhysicsBody::createBox(aEnemy->getContentSize());
	aEnemy->setPhysicsBody(Body);
	Body->setRotationEnable(false);
	_enemy->addChild(aEnemy, 10);
	aEnemy->getPhysicsBody()->setContactTestBitmask(0x0000F00F);
	aEnemy->getPhysicsBody()->setCategoryBitmask(0x0000F00F);
	//auto animation = AnimationCache::getInstance()->getAnimation(Constant::getEnemyAnimationName());
	Action* ac1 = RepeatForever::create(Animate::create(animation_run));
	ac1->setTag(1);
	aEnemy->runAction(ac1);
	//_enemy->runAction(MoveTo::create(10, Vec2(0, 30)));
	aEnemy->getPhysicsBody()->getFirstShape()->setTag(Constant::getEnemyTag3());
	_enemy->setContentSize(aEnemy->getContentSize());
	//设置弓箭
	this->schedule(schedule_selector(Enemy::updateTimeToArrowAttack), 1.0f);
}

void Enemy::updateTimeToArrowAttack(float dt){

	Sprite* EnemyArrow = Sprite::create("image/EnemyArrow.png");
	this->addChild(EnemyArrow);
	auto ArrowBody = PhysicsBody::createBox(EnemyArrow->getContentSize());
	EnemyArrow->setPhysicsBody(ArrowBody);

	//EnemyArrow->setPosition(0, 100);
	float angle = atan((locY - 0) / (locX - 0)) / pi * 180;
	EnemyArrow->setRotation(angle);

	float a = ParameterManager::getArrowMaxVelocity();
	float arrowVelocityX = -(EnemyArrow ->getPositionX()+this->getPositionX())/ dt;
	float arrowVelocityY = (EnemyArrow ->getPositionY()+this->getPositionY() - 0.5*dt*dt*ParameterManager::getGravity().y)/dt;
	//float arrowVelocityX = ParameterManager::getArrowMaxVelocity() * cos((angle + 180) / 180 * pi) + 10;
	//float arrowVelocityY = ParameterManager::getArrowMaxVelocity() * sin(angle / 180 * pi) + 10;
	ArrowBody->setVelocity(Vec2(arrowVelocityX, arrowVelocityY));

	EnemyArrow->getPhysicsBody()->setContactTestBitmask(0x0000F0F0);
	EnemyArrow->getPhysicsBody()->setCategoryBitmask(0x0000F0F0);
}

Sprite* Enemy::death(Sprite* s, int _mode){
	Sprite* tempS = Sprite::create();
	tempS->setPosition(s->getPosition()+this->getPosition());
	switch (_mode)
	{
	case 1:{
			   tempS ->createWithSpriteFrameName("Goblin_1.png");
			   Action* ac1 = Director::getInstance()->getActionManager()->getActionByTag(1, s);
			   Action* ac2 = Director::getInstance()->getActionManager()->getActionByTag(2, this);
			   s->stopAction(ac1);
			   s->stopAction(ac2);
			   SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
			   Vector <SpriteFrame*> temp = Vector <SpriteFrame*> ::Vector();
			   char name[20];
			   memset(name, 0, 10);
			   for (int i = 10; i < 14; i++){
				   sprintf(name, "Goblin_%d.png", i + 1);
				   SpriteFrame* sf = cache->spriteFrameByName(name);
				   temp.pushBack(sf);
			   }

			   Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.5f);
			   tempS->runAction(Animate::create(animation_run));
			   tempS->setPosition(this->getPosition());
			   break;
	}
	case 2:{
			   tempS->createWithSpriteFrameName("Soldier_1.png");
			   Action* ac1 = Director::getInstance()->getActionManager()-> getActionByTag(1, s);
			   Action* ac2 = Director::getInstance()->getActionManager()->getActionByTag(2, this);
			   s->stopAction(ac1);
			   s->stopAction(ac2);
			   SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
			   Vector <SpriteFrame*> temp = Vector <SpriteFrame*> ::Vector();
			   char name[20];
			   memset(name, 0, 10);
			   for (int i = 18; i < 23; i++){
				   sprintf(name, "Soldier_%d.png", i + 1);
				   SpriteFrame* sf = cache->spriteFrameByName(name);
				   temp.pushBack(sf);
			   }

			   Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.5f);
			   tempS->runAction(Animate::create(animation_run));
			  // this->addChild(s);
			   break;
	}
	case 3:{
			   tempS->createWithSpriteFrameName("ArrowEnemy_1.png");
			   Action* ac1 = Director::getInstance()->getActionManager()->getActionByTag(1, s);
			   s->stopAction(ac1);
			   SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
			   Vector <SpriteFrame*> temp = Vector <SpriteFrame*> ::Vector();
			   char name[20];
			   memset(name, 0, 10);
			   for (int i = 18; i < 22; i++){
				   sprintf(name, "ArrowEnemy_%d.png", i + 1);
				   SpriteFrame* sf = cache->spriteFrameByName(name);
				   temp.pushBack(sf);
			   }

			   Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.5f);
			   s->runAction(RepeatForever::create(Animate::create(animation_run)));
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