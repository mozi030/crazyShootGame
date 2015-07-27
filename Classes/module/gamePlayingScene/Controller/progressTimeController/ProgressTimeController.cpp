#include"ProgressTimeController.h"
#include"../../../../public/Constant/Constant.h"
#include"../../../../public/parameterManager/ParameterManager.h"

ProgressTimeController* ProgressTimeController::progressTimeController = NULL;

ProgressTimeController::ProgressTimeController(){}

ProgressTimeController::~ProgressTimeController(){
	progressTimeController = NULL;
}

ProgressTimeController* ProgressTimeController::getInstance() {
	//auto poolManager = PoolManager::getInstance();
	//if (!poolManager->getCurrentPool()->isClearing() || !poolManager->isObjectInPools(progressTimeController)) {
	if (progressTimeController == NULL){
		progressTimeController = new ProgressTimeController();
		progressTimeController->init();
		progressTimeController->autorelease();
		progressTimeController->initial();
	}
	return progressTimeController;
}

void ProgressTimeController::initial() {
	Size visibleSize = ParameterManager::getVisibleSize();

	progressSprite2 = Sprite::create(Constant::getProcessBar2Path());
	progressSprite2->setPosition(visibleSize.width / 2, visibleSize.height - 50);
	progressTimeController->addChild(progressSprite2, 2);

	progressSprite1 = Sprite::create(Constant::getProcessBar1Path());
	progressTimer = ProgressTimer::create(progressSprite1);
	progressTimer->setPosition(visibleSize.width / 2, visibleSize.height - 50);
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setMidpoint(Point(0, 0));
	progressTimer->setBarChangeRate(Point(1, 0));
	progressTimeController->addChild(progressTimer, 1);

	progressTimerLabel = Label::createWithBMFont(Constant::getFuturaPath() , "0%");
	progressTimerLabel->setAnchorPoint(Vec2(0, 0.5));
	progressTimerLabel->setPosition(visibleSize.width / 2 + progressTimer->getContentSize().width / 2, visibleSize.height - 50);
	progressTimeController->addChild(progressTimerLabel, 1);

	progressTimeController->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	progressTimeController->setPosition(0, 0);
}

ProgressTimer* ProgressTimeController::getProgressTimer(){
	return progressTimer;
}

Label* ProgressTimeController::getProgressTimerLabel() {
	return progressTimerLabel;
}