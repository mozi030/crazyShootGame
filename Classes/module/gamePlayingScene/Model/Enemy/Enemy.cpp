#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../../../public/Constant/Constant.h"
#include "Enemy.h"
#include "../archer/archer.h"

int Enemy::shadowNumber = 0;

int Enemy::getShadowNumber(){
	return shadowNumber++;
}

int j = 0;
void Enemy::onEnter(){
	Node::onEnter();
}

void Enemy::onExit(){
	Node::onExit();
}


bool Enemy::init(){
	locX = ParameterManager::getVisibleSize().width;
	locY = ParameterManager::getVisibleSize().height;
	power = 0;
	blood = 0;
	mode = 0;
	attackShadowExist = 0;

	enemySprite = Sprite::create();

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

	createInitial();

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

ProgressTimer* Enemy::getProgressBar(){
	return progressTimer;
}

Sprite* Enemy::getEnemySprite(){
	return enemySprite;
}

void Enemy::createInitial() {
	Size visibleSize = ParameterManager::getVisibleSize();

	auto progressSprite2 = Sprite::create(Constant::getEnemyBloodBackPath());
	progressSprite2->setPosition(0, 50);
	this->addChild(progressSprite2, 1);

	auto progressSprite1 = Sprite::create(Constant::getEnemyBloodForePath());
	progressTimer = ProgressTimer::create(progressSprite1);
	progressTimer->setPosition(0, 50);
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setMidpoint(Point(0, 1));
	progressTimer->setBarChangeRate(Point(1, 0));
	progressTimer->setPercentage(99.99f);
	this->addChild(progressTimer, 2);

}

void Enemy::createEnemyOne(){
	Sprite* aEnemy = Sprite::createWithSpriteFrameName("Goblin_1.png");
	this->enemySprite = aEnemy;


	auto aBody = PhysicsBody::createBox(aEnemy->getContentSize());
	aBody->setRotationEnable(false);
	this->setPhysicsBody(aBody);
	aBody->setCategoryBitmask(0x000000FF); //种类
	aBody->setContactTestBitmask(0x000000FF);
	aBody->setCollisionBitmask(0x000000FF);
	aBody->setGroup(-3);
	aBody->getFirstShape()->setTag(Constant::getEnemyTag1());

	Action* ac1 = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyGoblinMove())));
	ac1->setTag(1);
	aEnemy->runAction(ac1);


	this->schedule(schedule_selector(Enemy::setLoc), 1.0f);
}

void Enemy::setLoc(float dt){
	log("logJ     %d", j++);
	Vec2 vc = archer::getInstance()->getPosition();



	log("(%f,   %f) ", vc.x, vc.y);
	int flag = 1;
	float Ac_x = vc.x - this->getPosition().x;
	float Ac_y = vc.y - this->getPosition().y;
	if (Ac_x > 0){
		enemySprite->setFlippedX(true);
	}
	else{
		flag = -1;
		enemySprite->setFlippedX(false);
	}
	Action* ac2 = MoveBy::create(1, Point(30 * flag, 0));
	ac2->setTag(2);
	if (attackShadowExist == 0)
		this->runAction(ac2);
	this->addChild(enemySprite);

	/*if (fabs(Ac_x) < 80){
	log("<80\n");
	this->attack(enemySprite, mode);
	}
	else{
	log(">80\n");
	this->attackCancel(enemySprite, mode);
	}*/
}

void Enemy::createEnemyTwo(){
	Sprite* aEnemy = Sprite::createWithSpriteFrameName("Soldier_1.png");
	//Sprite* aEnemy = Sprite::createWithSpriteFrameName("Soldier_1.png");
	Action* ac1 = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemySoldierMove())));
	ac1->setTag(1);

	aEnemy->runAction(ac1);

	this->addChild(aEnemy, 10);

	auto aBody = PhysicsBody::createBox(aEnemy->getContentSize());
	aBody->setRotationEnable(false);
	this->setPhysicsBody(aBody);

	aBody->setCategoryBitmask(0x000000FF); //种类
	aBody->setContactTestBitmask(0x000000FF);
	aBody->setCollisionBitmask(0x000000FF);
	aBody->setGroup(-3);
	aBody->getFirstShape()->setTag(Constant::getEnemyTag2());

	this->enemySprite = aEnemy;
	this->schedule(schedule_selector(Enemy::setLoc), 1.0f);
}

void Enemy::createEnemyArrow(){

	Sprite* aEnemy = Sprite::createWithSpriteFrameName("ArrowEnemy_9.png");
	aEnemy->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyArrowEnemyAttack()))));
	this->addChild(aEnemy, 10);

	auto aBody = PhysicsBody::createBox(aEnemy->getContentSize());
	aBody->setRotationEnable(false);
	this->setPhysicsBody(aBody);

	aBody->setCategoryBitmask(0x000000FF); //种类
	aBody->setContactTestBitmask(0x000000FF);
	aBody->setCollisionBitmask(0x000000FF);
	aBody->setGroup(-3);
	aBody->getFirstShape()->setTag(Constant::getEnemyTag3());
	//设置弓箭
	this->schedule(schedule_selector(Enemy::updateTimeToArrowAttack), 1.6f, CC_REPEAT_FOREVER, 0.8);

	this->enemySprite = aEnemy;
}

void Enemy::updateTimeToArrowAttack(float dt){
	log("Arrow%d! ", j++);
	Sprite* EnemyArrow = Sprite::create(Constant::getEnemyArrowPath());
	this->addChild(EnemyArrow);
	auto ArrowBody = PhysicsBody::createBox(EnemyArrow->getContentSize());
	EnemyArrow->setPhysicsBody(ArrowBody);

	auto archer = archer::getInstance();
	EnemyArrow->setPosition(0, 10);

	Vec2 startPoint = Point(0, 0);
	Vec2 endPoint = Point(archer->getPositionX() - this->getPositionX(), archer->getPositionY() - this->getPositionY());
	if (endPoint.x > 0)
		enemySprite->setFlippedX(true);
	else
		enemySprite->setFlippedX(false);
	float durationTime = (fabs(archer->getPositionX() - this->getPositionX()) + fabs(archer->getPositionY() - this->getPositionY())) / 100;
	float arrowVelocityX = (-(startPoint.x - endPoint.x) - 0.5 * durationTime * durationTime * ParameterManager::getGravity().x) / durationTime;
	float arrowVelocityY = (-(startPoint.y - endPoint.y) - 0.5 * durationTime * durationTime * ParameterManager::getGravity().y) / durationTime;
	ArrowBody->setVelocity(Vec2(arrowVelocityX, arrowVelocityY));
	float angle = -atan(arrowVelocityY / arrowVelocityX) / pi * 180;
	if (arrowVelocityX > 0) angle += 180;
	EnemyArrow->setRotation(angle);

	EnemyArrow->getPhysicsBody()->setCategoryBitmask(0x0000000F); //种类
	EnemyArrow->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	EnemyArrow->getPhysicsBody()->setCollisionBitmask(0x0000000F);
	EnemyArrow->getPhysicsBody()->setGroup(-3);

	EnemyArrow->getPhysicsBody()->getFirstShape()->setTag(Constant::getEnemyArrowTag());

	std::string name = "hello";
	EnemyArrow->schedule(CC_CALLBACK_1(Enemy::updateTimeToChangeArrowAngle, this, EnemyArrow, name), 0, CC_REPEAT_FOREVER, 0, "end");
}

void Enemy::updateTimeToChangeArrowAngle(float dt, void* data, std::string name) {
	Vec2 velocity = ((Sprite*)data)->getPhysicsBody()->getVelocity();
	float angle = -atan(velocity.y / velocity.x) / pi * 180;
	if (velocity.x > 0) angle += 180;
	((Sprite*)data)->setRotation(angle);
}

Sprite* Enemy::createDispearSprite(int _mode, Vec2 position){
	Sprite* tempS = Sprite::create();
	tempS->setFlippedX(enemySprite->isFlippedX());
	switch (_mode)
	{
	case 1:{
		tempS->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyGoblinDeath())));
		this->getParent()->removeChildByName(trueNumber);
		tempS->setPosition(position);
		break;
	}
	case 2:{
		tempS->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemySoldierDeath())));
		this->getParent()->removeChildByName(trueNumber);
		tempS->setPosition(position);
		break;
	}
	case 3:{
		tempS->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyArrowEnemyDeath())));
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
		s->setVisible(false);
		// s->getParent()->pause();
		Director::getInstance()->getActionManager()->pauseTarget(s->getParent());
		if (attackShadowExist == 0){
			Sprite *ss = Sprite::createWithSpriteFrameName("Goblin_6.png");
			SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
			Vector <SpriteFrame*> temp = Vector <SpriteFrame*> ::Vector();
			char name[20];
			memset(name, 0, 20);
			for (int i = 6; i < 9; i++){
				sprintf(name, "Goblin_%d.png", i + 1);
				SpriteFrame* sf = cache->spriteFrameByName(name);
				temp.pushBack(sf);
			}

			Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.5f);
			Action* ac = RepeatForever::create(Animate::create(animation_run));
			ac->setTag(3);
			ss->setPosition(this->getPosition());
			ss->setFlippedX(s->isFlippedX());
			ss->runAction(ac);
			memset(trueNumber, 0, 20);
			sprintf(trueNumber, "%d", this->getShadowNumber());
			this->getParent()->addChild(ss, 10, trueNumber);
			// s->stopAction(Director::getInstance()->getActionManager()->getActionByTag(3, s));
			attackShadowExist = 1;
		}
		this->getParent()->getChildByName(trueNumber)->setPosition(this->getPosition());
		((Sprite*)this->getParent()->getChildByName(trueNumber))->setFlippedX(s->isFlippedX());
		log("attack ok!");
		break;
	}
	case 2:{
		Director::getInstance()->getActionManager()->pauseTarget(s->getParent());
		s->setVisible(false);
		//s->getParent()->pause();
		if (attackShadowExist == 0){
			Sprite *ss = Sprite::createWithSpriteFrameName("Soldier_8.png");
			SpriteFrameCache * cache = SpriteFrameCache::sharedSpriteFrameCache();
			Vector <SpriteFrame*> temp = Vector <SpriteFrame*> ::Vector();
			char name[20];
			memset(name, 0, 20);
			for (int i = 8; i < 17; i++){
				sprintf(name, "Soldier_%d.png", i + 1);
				SpriteFrame* sf = cache->spriteFrameByName(name);
				temp.pushBack(sf);
			}

			Animation* animation_run = Animation::createWithSpriteFrames(temp, 0.5f);
			Action* ac = RepeatForever::create(Animate::create(animation_run));
			ac->setTag(3);
			ss->setPosition(this->getPosition());
			ss->setFlippedX(s->isFlippedX());
			ss->runAction(ac);
			memset(trueNumber, 0, 20);
			sprintf(trueNumber, "%d", this->getShadowNumber());
			this->getParent()->addChild(ss, 10, trueNumber);
			// s->stopAction(Director::getInstance()->getActionManager()->getActionByTag(3, s));
			attackShadowExist = 1;
		}
		this->getParent()->getChildByName(trueNumber)->setPosition(this->getPosition());
		((Sprite*)this->getParent()->getChildByName(trueNumber))->setFlippedX(s->isFlippedX());
		break;
	}
	case 3:{

	}
	default:
		break;
	}
	return power;
}

void Enemy::attackCancel(Sprite* s, int _mode){
	switch (_mode)
	{
	case 1:{
		Director::getInstance()->getActionManager()->resumeTarget(s->getParent());
		// s->getParent()->resume();
		log("sudu    %f", this->getPhysicsBody()->getVelocity());
		s->setVisible(true);
		this->getParent()->removeChildByName(trueNumber);
		attackShadowExist = 0;
		break;
	}
	case 2:{
		Director::getInstance()->getActionManager()->resumeTarget(s->getParent());
		// s->getParent()->resume();
		s->setVisible(true);
		this->getParent()->removeChildByName(trueNumber);
		attackShadowExist = 0;
		break;
	}
	case 3:{

	}
	default:
		break;
	}
}