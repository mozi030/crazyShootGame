#include"EnemyController.h"
USING_NS_CC;
#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../Model/Constant/Constant.h"

EnemyController::EnemyController(){}

EnemyController* EnemyController::createAnEnemy() {
	Size visibleSize = ParameterManager::getVisibleSize();
	int x = rand() % (int(visibleSize.width) - 100) + 100;
	int y = rand() % (int(visibleSize.height) - 100) + 100;

	//auto aSprite = (EnemyController*)Sprite::createWithSpriteFrameName(Constant::getEnemyFrameName());

	auto aSprite = new EnemyController();
	aSprite->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Constant::getEnemyFrameName()));
	aSprite->autorelease();

	auto aBody = PhysicsBody::createCircle(aSprite->getContentSize().width / 2);
	aBody->setRotationEnable(false);
	aSprite->setPhysicsBody(aBody);
	aSprite->setPosition(x, y);
	aSprite->setAnchorPoint(Vec2(0, 0));
	aSprite->getPhysicsBody()->setContactTestBitmask(0x0000F00F);
	aSprite->getPhysicsBody()->setCategoryBitmask(0x0000F00F);
	auto animation = AnimationCache::getInstance()->getAnimation(Constant::getEnemyAnimationName());
	aSprite->runAction(RepeatForever::create(Animate::create(animation)));
	aSprite->runAction(MoveTo::create(ParameterManager::getEnemyMovingTime() * x / visibleSize.width, Vec2(0,30)));
	aSprite->getPhysicsBody()->getFirstShape()->setTag(Constant::getEnemyTag());

	return aSprite;
}