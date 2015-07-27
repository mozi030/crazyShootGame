#include"ground.h"
#include"../../../../public/parameterManager/parameterManager.h"
#include"../../../../public/Constant/Constant.h"

Vec2 ground::groundFirstPoint;
Vec2 ground::groundLastPoint;

cocos2d::Node* ground::createBottomGround(){
	Size visibleSize = ParameterManager::getVisibleSize();
	groundFirstPoint = Vec2(0, 75);
	groundLastPoint = Vec2(visibleSize.width, 75);
	auto aNode = ground::create();
	aNode->getPhysicsBody()->getFirstShape()->setTag(Constant::getBottomGroundTag());
	return aNode;
}

bool ground::init(){
	if (!Node::init()) { return false; }
	this->setPhysicsBody(PhysicsBody::createEdgeSegment(groundFirstPoint, groundLastPoint));
	this->getPhysicsBody()->setDynamic(false);
	this->getPhysicsBody()->setContactTestBitmask(0x00000FF0);
	this->getPhysicsBody()->setCategoryBitmask(0x00000FF0);
	return true;
}

ground::ground(){}