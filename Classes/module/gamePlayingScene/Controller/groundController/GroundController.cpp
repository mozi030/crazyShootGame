#include"GroundController.h"
USING_NS_CC;
#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../../../public/Constant/Constant.h"
#include"../../Model/ground/ground.h"

GroundController* GroundController::groundController = NULL;

GroundController::GroundController() {}

GroundController::~GroundController() {
	groundController = NULL;
}

GroundController* GroundController::getInstance() {
	if (groundController == NULL) {
		groundController = GroundController::create();
	}
	return groundController;
}

bool GroundController::init() {
	if (!Node::init()) { return false; }
	this->addChild(ground::createBottomGround());
	this->addChild(ground::createLeftGround());
	this->addChild(ground::createRightGround());
	this->addChild(ground::createBottomGround1());
	this->addChild(ground::createBottomGround2());
	this->addChild(ground::createBottomGround3());

	return true;
}