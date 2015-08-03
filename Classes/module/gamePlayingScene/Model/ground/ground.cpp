#include"ground.h"
#include"../../../../public/parameterManager/parameterManager.h"
#include"../../../../public/Constant/Constant.h"

Vec2 ground::groundFirstPoint;
Vec2 ground::groundLastPoint;

cocos2d::Node* ground::createBottomGround(){
	Size visibleSize = ParameterManager::getVisibleSize();
	float bottomHeight = ParameterManager::getBottomGroundHeight();
	groundFirstPoint = Vec2(0, 90);
	groundLastPoint = Vec2(1280, 90);
	auto aNode = ground::create();
	aNode->getPhysicsBody()->getFirstShape()->setTag(Constant::getBottomGroundTag());
	aNode->getPhysicsBody()->setCategoryBitmask(0x000000FF);
	aNode->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	aNode->getPhysicsBody()->setCollisionBitmask(0x000000FF);
	aNode->getPhysicsBody()->setGroup(-1);
	return aNode;
}

cocos2d::Node* ground::createLeftGround(){
	Size visibleSize = ParameterManager::getVisibleSize();
	float bottomHeight = ParameterManager::getBottomGroundHeight();
	groundFirstPoint = Vec2(0, 75);
	groundLastPoint = Vec2(0, 928);
	auto aNode = ground::create();
	aNode->getPhysicsBody()->getFirstShape()->setTag(Constant::getLeftGroundTag());
	aNode->getPhysicsBody()->setCategoryBitmask(0x000000F0);
	aNode->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	aNode->getPhysicsBody()->setCollisionBitmask(0x000000F0);
	aNode->getPhysicsBody()->setGroup(-1);
	return aNode;
}

cocos2d::Node* ground::createRightGround(){
	Size visibleSize = ParameterManager::getVisibleSize();
	float bottomHeight = ParameterManager::getBottomGroundHeight();
	groundFirstPoint = Vec2(1280, 75);
	groundLastPoint = Vec2(1280, 928);
	auto aNode = ground::create();
	aNode->getPhysicsBody()->getFirstShape()->setTag(Constant::getLeftGroundTag());
	aNode->getPhysicsBody()->setCategoryBitmask(0x000000F0);
	aNode->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	aNode->getPhysicsBody()->setCollisionBitmask(0x000000F0);
	aNode->getPhysicsBody()->setGroup(-1);
	return aNode;
}

cocos2d::Node* ground::createBottomGround1(){
	Size visibleSize = ParameterManager::getVisibleSize();
	groundFirstPoint = Vec2(272, 378);
	groundLastPoint = Vec2(845, 378);
	auto aNode = ground::create();
	aNode->getPhysicsBody()->getFirstShape()->setTag(Constant::getBottomGroundTag());
	aNode->getPhysicsBody()->setCategoryBitmask(0x000000FF);
	aNode->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	aNode->getPhysicsBody()->setCollisionBitmask(0x000000FF);
	aNode->getPhysicsBody()->setGroup(-1);
	return aNode;
}

cocos2d::Node* ground::createBottomGround2(){
	Size visibleSize = ParameterManager::getVisibleSize();
	groundFirstPoint = Vec2(616, 148);
	groundLastPoint = Vec2(1188, 148);
	auto aNode = ground::create();
	aNode->getPhysicsBody()->getFirstShape()->setTag(Constant::getBottomGroundTag());
	aNode->getPhysicsBody()->setCategoryBitmask(0x000000FF);
	aNode->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	aNode->getPhysicsBody()->setCollisionBitmask(0x000000FF);
	aNode->getPhysicsBody()->setGroup(-1);
	return aNode;
}

cocos2d::Node* ground::createBottomGround3(){
	Size visibleSize = ParameterManager::getVisibleSize();
	groundFirstPoint = Vec2(610, 618);
	groundLastPoint = Vec2(1195, 618);
	auto aNode = ground::create();
	aNode->getPhysicsBody()->getFirstShape()->setTag(Constant::getBottomGroundTag());
	aNode->getPhysicsBody()->setCategoryBitmask(0x000000FF);
	aNode->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	aNode->getPhysicsBody()->setCollisionBitmask(0x000000FF);
	aNode->getPhysicsBody()->setGroup(-1);
	return aNode;
}

bool ground::init(){
	if (!Node::init()) { return false; }
	this->setPhysicsBody(PhysicsBody::createEdgeSegment(groundFirstPoint, groundLastPoint));
	this->getPhysicsBody()->setDynamic(false);
	return true;
}

ground::ground(){}