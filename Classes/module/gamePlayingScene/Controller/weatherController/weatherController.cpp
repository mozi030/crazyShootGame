#include"weatherController.h"
#include"math.h"

weatherController* weatherController::weather = NULL;

weatherController::weatherController() {}

weatherController::~weatherController() {
	if (weather != NULL) {
		weather->removeFromParentAndCleanup(true);
		weather = NULL;
	}
}

weatherController* weatherController::getInstance(){
	if (weather == NULL){
		weather = weatherController::create();
		weather->setPosition(0, 0);
		weather->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	}
	return weather;
}

bool weatherController::init() {
	if (!Layer::init()) { return false; }

	cloud = Sprite::create("GamePlayingScene/weather/cloud.png");
	cloud->setPosition(200,540);
	cloud->setScale(0.9);
	this->addChild(cloud, 1);

	auto right = MoveTo::create(5, Vec2(1200, 540));
	auto left = MoveTo::create(5, Vec2(200, 540));

	auto action1 = Sequence::create(right, left,NULL);
	cloud->runAction(RepeatForever::create(action1));

	flash = Sprite::create();
	flash->setPosition(cloud->getPositionX(), cloud->getPositionY() - 700);

	flash->setScale(1.0);
	
	cloud->addChild(flash, 2);

	this->schedule(schedule_selector(weatherController::flashAction), 3.0f);

	return true;
}

void weatherController::flashAction(float dt){


	CCAnimation *flashing = CCAnimation::create();
	for (int i = 1; i < 5; i++){
		char FileName[128] = { 0 };
		sprintf(FileName, "GamePlayingScene/weather/flash_%d.png", i);
		flashing->addSpriteFrameWithFileName(FileName);
	}

	flashing->setDelayPerUnit(0.3f / 3.0f);
	CCAnimate *action = CCAnimate::create(flashing);
	flash->runAction(action);

	auto p1 = archer::getInstance()->getPositionX();
	auto p2 = cloud->getPositionX();

	//判断人和闪电的位置，判断是否受伤
	if (abs(p1 - p2) < 100){
		archer::getInstance()->attacked(20);
	}
}