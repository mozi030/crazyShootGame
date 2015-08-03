#include"ArcherController.h"
#include"../../../../public/Constant/Constant.h"
#include"../../../../public/ParameterManager/ParameterManager.h"


ArcherController* ArcherController::archerController = NULL;

archer* ArcherController::getArcher() {
	return archer_;
}

ArcherController::ArcherController() {}

ArcherController::~ArcherController() {
	if (archerController != NULL) {
		archerController = NULL;
	}
}

ArcherController* ArcherController::getInstance(){
	if (archerController == NULL){
		archerController = ArcherController::create();
	}
	return archerController;
}

bool ArcherController::init() {
	if (!Layer::init()) { return false; }
	archer_ = archer::getInstance();
	archer_->setPosition(ParameterManager::getLevelInstance(ParameterManager::getCurrentLevel())->archerParameter->initialPosition);
	this->addChild(archer_);

	return true;
}


