#include"EnemyController.h"
USING_NS_CC;
/*#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../Model/Constant/Constant.h"*/
#include "../../Model/Enemy/Enemy.h"

EnemyController::EnemyController(){

	
}

EnemyController* EnemyController::createAnEnemy() {

	auto  s = new  EnemyController();
	/*Size visibleSize = ParameterManager::getVisibleSize();
	//int x = rand() % (int(visibleSize.width) - 100) + 100;
	//int y = rand() % (int(visibleSize.height) - 100) + 100;
	int x = 300;
	int y = 200;
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


	return aSprite;*/
	auto t = new Enemy();
	auto i = new Enemy();
	i->createEnemy(1000, 200, 1, 1);
	t->createEnemy(500, 200, 2,2);
	s->addChild(t);
	s->addChild(i);

	return s;
}
