#include"GroundController.h"
USING_NS_CC;
#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../Model/Constant/Constant.h"

GroundController* GroundController::groundController = nullptr;

GroundController::GroundController() {}

GroundController::~GroundController() {
	groundController = nullptr;
}

GroundController* GroundController::getInstance() {
	//auto poolManager = PoolManager::getInstance();
	//if (!poolManager->getCurrentPool()->isClearing() || !poolManager->isObjectInPools(groundController)) {
//	if (groundController == nullptr){
		groundController = new GroundController();
		groundController->init();
		groundController->autorelease();
		//groundController = (GroundController*)Node::create();
		groundController->initial();
//	}
	return groundController;
}

void GroundController::initial() {
	Size visibleSize = ParameterManager::getVisibleSize();
	groundController->setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2(0, 75), Vec2(visibleSize.width, 75)));

	groundController->getPhysicsBody()->setDynamic(false);
	groundController->getPhysicsBody()->getFirstShape()->setTag(Constant::getGroundTag());
	groundController->getPhysicsBody()->setContactTestBitmask(0x00000FF0);
	groundController->getPhysicsBody()->setCategoryBitmask(0x00000FF0);
}