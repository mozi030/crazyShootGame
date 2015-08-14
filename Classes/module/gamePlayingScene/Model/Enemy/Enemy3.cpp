/*
弓箭手：不会移动，但会远程攻击，攻击力为10。（死亡条件：两箭才能击杀）
*/

#include"Enemy3.h"

bool Enemy3::init() {
	if (!Node::init()) { return false; }
	mode = 3;
	shadowNumber = 0;
	attackShadowExist = false;
	power = ParameterManager::getCurrentGameLevel() * 15;

	//敌人精灵
	Sprite* aEnemy = Sprite::createWithSpriteFrameName("ArrowEnemy_9.png");
	aEnemy->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyArrowEnemyAttack()))));
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
	//this->schedule(schedule_selector(Enemy3::setLoc), 1.0f);

	//设置弓箭
	this->schedule(schedule_selector(Enemy3::updateTimeToArrowAttack), 1.6f, CC_REPEAT_FOREVER, 0.8);


	/*attackSprite = Sprite::create();
	this->addChild(attackSprite);
	attackSprite->setPosition(Vec2::ZERO);
	attackSprite->setVisible(false);*/

	return true;
}

void Enemy3::setLoc(float dt){
	Vec2 vc = archer::getInstance()->getPosition();

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
	if (attackShadowExist == false)
		this->runAction(MoveBy::create(1, Point(30 * flag, 0)));
}

Sprite* Enemy3::createDispearSprite(Vec2 position){
	Sprite* tempS = Sprite::create();
	tempS->setFlippedX(enemySprite->isFlippedX());

	tempS->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(Constant::getEnemyArrowEnemyDeath())));
	tempS->setPosition(position);

	return tempS;
}

int Enemy3::attack(){
	if (attackShadowExist == false){

		this->schedule(schedule_selector(Enemy3::AttackEnemy), 2);

		attackShadowExist = true;
	}
	//attackSprite->setFlippedX(direction);
	return 0;
}

void Enemy3::AttackEnemy(float dt) {
	archer::getInstance()->attacked(power);
}

void Enemy3::attackCancel() {
	attackShadowExist = false;
}

void Enemy3::updateTimeToArrowAttack(float dt){
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

	bitmask aBitmask = Constant::getEnemyArrowBitmask();
	auto physicsBody = EnemyArrow->getPhysicsBody();
	physicsBody->setCategoryBitmask(aBitmask.categoryBitmask);
	physicsBody->setCollisionBitmask(aBitmask.collisionBitmask);
	physicsBody->setContactTestBitmask(aBitmask.contactTestBitmask);
	physicsBody->setGroup(aBitmask.group);

	EnemyArrow->getPhysicsBody()->getFirstShape()->setTag(Constant::getEnemyArrowTag());

	EnemyArrow->schedule(CC_CALLBACK_1(Enemy3::updateTimeToChangeArrowAngle, this, EnemyArrow, ""), 0, CC_REPEAT_FOREVER, 0, "end");
}

void Enemy3::updateTimeToChangeArrowAngle(float dt, void* data, std::string name) {
	Vec2 velocity = ((Sprite*)data)->getPhysicsBody()->getVelocity();
	float angle = -atan(velocity.y / velocity.x) / pi * 180;
	if (velocity.x > 0) angle += 180;
	((Sprite*)data)->setRotation(angle);
}