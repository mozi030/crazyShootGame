#include"archerController.h"
#include"../../Model/Constant/Constant.h"
archerController* archerController::archer = NULL;

archerController::archerController() {}

archerController::~archerController() {
	archer = NULL;
}

archerController* archerController::getInstance(){
	//auto poolManager = PoolManager::getInstance();
	//if (!poolManager->getCurrentPool()->isClearing() || !poolManager->isObjectInPools(archer)) {
	if (archer == NULL){
		archer = new archerController();
		archer->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Constant::getArcherFrameName()));
		archer->autorelease();
		//archer = (archerController*)Sprite::createWithSpriteFrameName(Constant::getArcherFrameName());
		archer->initial();
	}
	return archer;
}

void archerController::initial() {
	auto aBody = PhysicsBody::createCircle(archer->getContentSize().height / 2);
	aBody->setRotationEnable(false);
	archer->setPhysicsBody(aBody);
	archer->setPosition(20, 100);
	archer->setAnchorPoint(Vec2(0.5, 0.5));
	archer->getPhysicsBody()->setContactTestBitmask(0x0000000F);
	//archerSprite->getPhysicsBody()->setCollisionBitmask(0x0000000F);
	archer->getPhysicsBody()->setCategoryBitmask(0x0000000F);
	archer->getPhysicsBody()->getFirstShape()->setTag(Constant::getArcherTag());
}