#include"edge.h"

Vec2 edge::edgeFirstPoint;
Vec2 edge::edgeLastPoint;

Node* edge::createEdge1(Vec2 point1, Vec2 point2) {
	edgeFirstPoint = point1;
	edgeLastPoint = point2;
	auto aNode = edge::create();

	aNode->getPhysicsBody()->getFirstShape()->setTag(Constant::getEdge1Tag());

	bitmask aBitmask = Constant::getEdge1Bitmask();
	auto physicsBody = aNode->getPhysicsBody();
	physicsBody->setCategoryBitmask(aBitmask.categoryBitmask);
	physicsBody->setCollisionBitmask(aBitmask.collisionBitmask);
	physicsBody->setContactTestBitmask(aBitmask.contactTestBitmask);
	physicsBody->setGroup(aBitmask.group);
	return aNode;
}

Node * edge::createEdge2(Vec2 point1, Vec2 point2) {
	edgeFirstPoint = point1;
	edgeLastPoint = point2;
	auto aNode = edge::create();

	aNode->getPhysicsBody()->getFirstShape()->setTag(Constant::getEdge2Tag());

	bitmask aBitmask = Constant::getEdge2Bitmask();
	auto physicsBody = aNode->getPhysicsBody();
	physicsBody->setCategoryBitmask(aBitmask.categoryBitmask);
	physicsBody->setCollisionBitmask(aBitmask.collisionBitmask);
	physicsBody->setContactTestBitmask(aBitmask.contactTestBitmask);
	physicsBody->setGroup(aBitmask.group);
	return aNode;
}

Node * edge::createRope(Vec2 point1, Vec2 point2) {
	edgeFirstPoint = point1;
	edgeLastPoint = point2;
	auto aNode = edge::create();

	aNode->getPhysicsBody()->getFirstShape()->setTag(Constant::getRopeTag());

	bitmask aBitmask = Constant::getRopeBitmask();
	auto physicsBody = aNode->getPhysicsBody();
	physicsBody->setCategoryBitmask(aBitmask.categoryBitmask);
	physicsBody->setCollisionBitmask(aBitmask.collisionBitmask);
	physicsBody->setContactTestBitmask(aBitmask.contactTestBitmask);
	physicsBody->setGroup(aBitmask.group);
	return aNode;
}

bool edge::init(){
	if (!Node::init()) { return false; }
	this->setPhysicsBody(PhysicsBody::createEdgeSegment(edgeFirstPoint, edgeLastPoint));
	this->getPhysicsBody()->setDynamic(false);
	return true;
}

edge::edge(){}