#include"progressTime.h"

progressTime* progressTime::progressTimeInstance = NULL;

progressTime::progressTime(){}

progressTime::~progressTime(){
	if (progressTimeInstance != NULL) {
		progressTimeInstance->removeFromParentAndCleanup(true);
		progressTimeInstance = NULL;
	}
}

progressTime* progressTime::getInstance() {
	if (progressTimeInstance == NULL){
		progressTimeInstance = new progressTime();
		progressTimeInstance->init();
		progressTimeInstance->autorelease();
		progressTimeInstance->initial();
	}
	return progressTimeInstance;
}

void progressTime::initial() {
	Size visibleSize = ParameterManager::getVisibleSize();

	progressSprite2 = Sprite::create(Constant::getProcessBar2Path());
	progressSprite2->setPosition(visibleSize.width / 2, visibleSize.height - 50);
	progressTimeInstance->addChild(progressSprite2, 2);

	progressSprite1 = Sprite::create(Constant::getProcessBar1Path());
	progressTimer = ProgressTimer::create(progressSprite1);
	progressTimer->setPosition(visibleSize.width / 2, visibleSize.height - 50);
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setMidpoint(Point(0, 0));
	progressTimer->setBarChangeRate(Point(1, 0));
	progressTimeInstance->addChild(progressTimer, 1);

	progressTimerLabel = Label::createWithBMFont(Constant::getFuturaPath() , "0%");
	progressTimerLabel->setAnchorPoint(Vec2(0, 0.5));
	progressTimerLabel->setPosition(visibleSize.width / 2 + progressTimer->getContentSize().width / 2, visibleSize.height - 50);
	progressTimeInstance->addChild(progressTimerLabel, 1);

	progressTimeInstance->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	progressTimeInstance->setPosition(0, 0);
}

void progressTime::setProgressPercent(float percent) {
	progressTimer->setPercentage(percent);
	progressTimerLabel->setString(CCString::createWithFormat("%d", int(percent))->_string + "%");
}

float progressTime::getProgressPercent() {
	return progressTimer->getPercentage();
}