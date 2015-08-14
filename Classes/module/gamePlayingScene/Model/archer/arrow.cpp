#include"arrow.h"

#define pi 3.141592654

arrow::arrow() {}

arrow* arrow::createAnArrow(Vec2 beginPoint, Vec2 endedPoint, float percent, int arrowType) {
	Size visibleSize = ParameterManager::getVisibleSize();

	float beginX = beginPoint.x, beginY = beginPoint.y;
	float endX = endedPoint.x, endY = endedPoint.y;

	//箭2的动画
	CCAnimation *arrow_ani = CCAnimation::create();
	for (int i = 0; i < 3; i++){
		char FileName[128] = { 0 };
		sprintf(FileName, "GamePlayingScene/arrow/arrow2_%d.png", i);
		arrow_ani->addSpriteFrameWithFileName(FileName);
	}

	arrow_ani->setDelayPerUnit(0.5f / 3.0f);
	CCAnimate *action2 = CCAnimate::create(arrow_ani);

	//箭3的动画
	CCAnimation *arrow_ani3 = CCAnimation::create();
	for (int i = 0; i < 5; i++){
		char FileName2[128] = { 0 };
		sprintf(FileName2, "GamePlayingScene/arrow/arrow3_%d.png", i);
		arrow_ani3->addSpriteFrameWithFileName(FileName2);
	}

	arrow_ani3->setDelayPerUnit(0.8f / 5.0f);
	CCAnimate *action3 = CCAnimate::create(arrow_ani3);

	//auto arrowSprite = (ArrowController*)Sprite::create(Constant::getArrowPath());
	auto arrowSprite = new arrow();

	int currentLevel = item::getCurrentArcherLevel();
	switch (arrowType) {
	case 1:
		arrowSprite->initWithFile(Constant::getArrow1Path());
		arrowSprite->power = 5 * currentLevel;
		break;
	case 2:
		arrowSprite->initWithFile(Constant::getArrow2Path());
		arrowSprite->runAction(RepeatForever::create(action2));
		//箭的攻击力
		arrowSprite->power = 25 * currentLevel;
		break;
	case 3:
		arrowSprite->initWithFile(Constant::getArrow3Path());
		arrowSprite->runAction(RepeatForever::create(action3));
		arrowSprite->power = 50 * currentLevel;
		break;
	default:
		break;
	}
	arrowSprite->autorelease();

	auto arrowBody = PhysicsBody::createBox(arrowSprite->getContentSize());
	arrowBody->getFirstShape()->setTag(Constant::getArrowTag());
	arrowSprite->setPhysicsBody(arrowBody);

	float angle = -atan((beginY - endY) / (beginX - endX)) / pi * 180;
	if (beginX >= endX) {
		angle += 180;
	}
	arrowSprite->setRotation(angle);

	arrowSprite->setPosition(20, 20);

	float a = ParameterManager::getArrow1MaxVelocity();
	float progressPrecent = percent + 50;
	float arrowVelocityX = progressPrecent / 100 * ParameterManager::getArrow1MaxVelocity() * cos(angle / 180 * pi);
	float arrowVelocityY = progressPrecent / 100 * ParameterManager::getArrow1MaxVelocity() * sin(angle / 180 * pi);
	arrowBody->setVelocity(Vec2(arrowVelocityX, -arrowVelocityY));

	bitmask aBitmask = Constant::getArrowBitmask();
	auto physicsBody = arrowSprite->getPhysicsBody();
	physicsBody->setCategoryBitmask(aBitmask.categoryBitmask); //种类
	physicsBody->setCollisionBitmask(aBitmask.collisionBitmask);
	physicsBody->setContactTestBitmask(aBitmask.contactTestBitmask);
	physicsBody->setGroup(aBitmask.group);

	std::string name = "hello";
	arrowSprite->schedule(CC_CALLBACK_1(arrow::updateTimeToChangeArrowAngle, arrowSprite, arrowSprite, name), 0, CC_REPEAT_FOREVER, 0, "end");

	return arrowSprite;
}

arrow* arrow::createArrowRain(Vec2 beginPoint, Vec2 endedPoint, float percent) {
	Size visibleSize = ParameterManager::getVisibleSize();

	float beginX = beginPoint.x, beginY = beginPoint.y;
	float endX = endedPoint.x, endY = endedPoint.y;

	//箭2
	auto arrowSprite = new arrow();
	arrowSprite->initWithFile("GamePlayingScene/arrow/arrowRain.png");
	arrowSprite->autorelease();
	//arrowSprite->runAction(RepeatForever::create(action2));
	//箭的攻击力
	arrowSprite->power = item::getCurrentArcherLevel() * 1;

	auto arrowBody = PhysicsBody::createBox(arrowSprite->getContentSize());
	arrowBody->getFirstShape()->setTag(Constant::getArrow4Tag());
	arrowSprite->setPhysicsBody(arrowBody);

	float angle = -atan((beginY - endY) / (beginX - endX)) / pi * 180;
	if (beginX >= endX) {
		angle += 180;
	}
	arrowSprite->setRotation(angle);

	arrowSprite->setPosition(beginX, beginY);

	float a = ParameterManager::getArrow1MaxVelocity();
	float progressPrecent = percent + 50;
	float arrowVelocityX = progressPrecent / 100 * ParameterManager::getArrow1MaxVelocity() * cos(angle / 180 * pi);
	float arrowVelocityY = progressPrecent / 100 * ParameterManager::getArrow1MaxVelocity() * sin(angle / 180 * pi);
	arrowBody->setVelocity(Vec2(arrowVelocityX, -arrowVelocityY));

	arrowSprite->getPhysicsBody()->setCategoryBitmask(0x0000000F); //种类
	arrowSprite->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	arrowSprite->getPhysicsBody()->setCollisionBitmask(0x0000000F);
	arrowSprite->getPhysicsBody()->setGroup(-2);

	std::string name = "hello";
	arrowSprite->schedule(CC_CALLBACK_1(arrow::updateTimeToChangeArrowAngle, arrowSprite, arrowSprite, name), 0, CC_REPEAT_FOREVER, 0, "end");

	return arrowSprite;
}

arrow* arrow::createArrowRainTouch(float rotation, Vec2 position){
	auto arrowSprite = new arrow();
	arrowSprite->initWithFile("GamePlayingScene/arrow/arrowRainTouch.png");
	arrowSprite->autorelease();

	arrowSprite->setRotation(rotation);
	arrowSprite->setPosition(position);

	arrowSprite->runAction(FadeOut::create(0.5));

	return arrowSprite;
}

void arrow::updateTimeToChangeArrowAngle(float dt, void* data, std::string name) {
	auto anArrow = ((arrow*)data);
	Vec2 velocity = anArrow->getPhysicsBody()->getVelocity();
	float angle = -atan(velocity.y / velocity.x) / pi * 180;
	if (velocity.x < 0) angle += 180;
	anArrow->setRotation(angle);
}

int arrow::getPower() {
	return power;
}