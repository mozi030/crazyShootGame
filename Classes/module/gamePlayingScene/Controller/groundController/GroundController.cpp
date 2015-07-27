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

	return true;
}