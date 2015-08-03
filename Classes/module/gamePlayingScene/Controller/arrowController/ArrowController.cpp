#include"ArrowController.h"
#include"../../Model/archer/archer.h"
USING_NS_CC;
#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../../../public/Constant/Constant.h"
#include"../progressTimeController/ProgressTimeController.h"

#define pi 3.141592654

ArrowController::ArrowController() {}

ArrowController* ArrowController::createAnArrow(float x_Begin, float y_Begin, float xEnd, float yEnd) {
	Size visibleSize = ParameterManager::getVisibleSize();
	Size archerSize = Size(100, 100);

	float xBegin = x_Begin;
	float yBegin = y_Begin;

	//auto arrowSprite = (ArrowController*)Sprite::create(Constant::getArrowPath());
	auto arrowSprite = new ArrowController();
	arrowSprite->initWithFile(Constant::getArrowPath());
	arrowSprite->autorelease();

	auto arrowBody = PhysicsBody::createBox(arrowSprite->getContentSize());
	arrowBody->getFirstShape()->setTag(Constant::getArrowTag());
	arrowSprite->setPhysicsBody(arrowBody);

	float angle = -atan((yBegin - yEnd) / (xBegin - xEnd)) / pi * 180;
	if (xBegin >= xEnd) {
		angle += 180;
	}
	arrowSprite->setRotation(angle);

	arrowSprite->setPosition(xBegin, yBegin);

	float a = ParameterManager::getArrow1MaxVelocity();
	float arrowVelocityX = ProgressTimeController::getInstance()->getProgressTimer()->getPercentage() / 100 * ParameterManager::getArrow1MaxVelocity() * cos(angle / 180 * pi) + 100;
	float arrowVelocityY = ProgressTimeController::getInstance()->getProgressTimer()->getPercentage() / 100 * ParameterManager::getArrow1MaxVelocity() * sin(angle / 180 * pi) - 100;
	arrowBody->setVelocity(Vec2(arrowVelocityX, -arrowVelocityY));

	arrowSprite->getPhysicsBody()->setCategoryBitmask(0x0000000F); //种类
	arrowSprite->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	arrowSprite->getPhysicsBody()->setCollisionBitmask(0x0000000F);
	arrowSprite->getPhysicsBody()->setGroup(-2);

	std::string name = "hello";
	arrowSprite->schedule(CC_CALLBACK_1(ArrowController::updateTimeToChangeArrowAngle, arrowSprite, arrowSprite, name), 0, CC_REPEAT_FOREVER, 0, "end");

	return arrowSprite;
}

void ArrowController::updateTimeToChangeArrowAngle(float dt, void* data,std::string name) {
	auto anArrow = ((ArrowController*)data);
	Vec2 velocity = anArrow->getPhysicsBody()->getVelocity();
	float angle = -atan(velocity.y / velocity.x) / pi * 180;
	if (velocity.x < 0) angle += 180;
	anArrow->setRotation(angle);
}