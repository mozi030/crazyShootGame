#include"ArcherController.h"

ArcherController* ArcherController::archerController = NULL;

ArcherController::ArcherController() {}

ArcherController::~ArcherController() {
	if (archerController != NULL) {
		archerController->removeFromParentAndCleanup(true);
		archerController = NULL;
	}
}

ArcherController* ArcherController::getInstance(){
	if (archerController == NULL){
		archerController = ArcherController::create();
		archerController->setPosition(0,0);
		archerController->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	}
	return archerController;
}

bool ArcherController::init() {
	if (!Layer::init()) { return false; }

	archer_ = archer::getInstance();
	archer_->setPosition(ParameterManager::getGameParameterInstance(ParameterManager::getCurrentGameLevel())->archerParameter->initialPosition);
	this->addChild(archer_);

	//设置参数
	int levelNum = item::getCurrentArcherLevel();
	LevelParameter* aLevelParameter = ParameterManager::getLevelParameterInstance(levelNum);
	archer_->setInitialBlood(aLevelParameter->blood);
	archer_->setBlood(aLevelParameter->blood);
	archer_->setInitialBlue(aLevelParameter->blue);
	archer_->setBlue(aLevelParameter->blue);
	archer_->setTotalExp(aLevelParameter->levelUpExp);
	archer_->setExp(item::getExp());
	archer_->setWeapon(1);
	archer_->setScore(0);

	//加入蓄力用的进度条
	progressTime_ = progressTime::getInstance();
	this->addChild(progressTime_);

	//keyboard listener
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(ArcherController::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(ArcherController::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->schedule(schedule_selector(ArcherController::updateTimeForAddExp), 1.0f);

	return true;
}

archer* ArcherController::archer_;
archer* ArcherController::getArcher() {
	return archer_;
}

progressTime* ArcherController::progressTime_;
progressTime* ArcherController::getProgressTime() {
	return progressTime_;
}

float ArcherController::totalTimeForProgressBar;
void ArcherController::touchBegan(Vec2 touchPoint) {
	Vec2 cameraLocation = CameraController::getInstance()->getCamera()->getPosition();
	Size visibleSize = ParameterManager::getVisibleSize();

	Vec2 touchEndedPosition = Vec2(touchPoint.x + (cameraLocation.x - visibleSize.width / 2), touchPoint.y + (cameraLocation.y - visibleSize.height / 2));
	archer_->aimAt(touchEndedPosition);

	totalTimeForProgressBar = 0;
	progressTime::getInstance()->setProgressPercent(0);
	archer_->schedule(schedule_selector(ArcherController::updateTimeForProgressBar), 0.1f);
}

void ArcherController::touchEnded(Vec2 touchPoint) {
	Size visibleSize = ParameterManager::getVisibleSize();
	Vec2 cameraLocation = CameraController::getInstance()->getCamera()->getPosition();

	Vec2 touchEndedPosition = Vec2(touchPoint.x + (cameraLocation.x - visibleSize.width / 2), touchPoint.y + (cameraLocation.y - visibleSize.height / 2));
	archer_->aimAt(touchEndedPosition);

	archer_->unschedule(schedule_selector(ArcherController::updateTimeForProgressBar));
	Vec2 beginPosition = archer_->getPosition();

	if (archer_->getWeapon() == 1) {
		archer_->addChild(arrow::createAnArrow(beginPosition, touchEndedPosition, progressTime::getInstance()->getProgressPercent(), 1), 3);
	}
	else {
		if (item::getArrow() > 0) {
			if (archer_->getWeapon() == 2) {
				auto currentBlue = archer_->getBlue();
				if (currentBlue < archer_->getInitialBLue() / 4) {
					return;
				}
				else {
					archer_->setBlue(currentBlue - archer_->getInitialBLue() / 4);
				}
				archer_->addChild(arrow::createAnArrow(beginPosition, touchEndedPosition, progressTime::getInstance()->getProgressPercent(), 2), 3);
				item::useArrow();
			}
			else {
				auto currentBlue = archer_->getBlue();
				if (currentBlue < archer_->getInitialBLue() / 2) {
					return;
				}
				else {
					archer_->setBlue(currentBlue - archer_->getInitialBLue() / 2);
				}
				archer_->addChild(arrow::createAnArrow(beginPosition, touchEndedPosition, progressTime::getInstance()->getProgressPercent(), 3), 3);
				item::useArrow();
				item::useArrow();
			}
		}
		else {
			archer_->setWeapon(1);
			archer_->addChild(arrow::createAnArrow(beginPosition, touchEndedPosition, progressTime::getInstance()->getProgressPercent(), 1), 3);
		}
	}
}

void ArcherController::updateTimeForProgressBar(float dt){
	totalTimeForProgressBar += dt;
	if (totalTimeForProgressBar >= Constant::getTimeLimit() / 10)
	{
		progressTime::getInstance()->setProgressPercent(0);
		totalTimeForProgressBar = 0;
		return;
	}
	else {
		progressTime::getInstance()->setProgressPercent(totalTimeForProgressBar * 10.0 / Constant::getTimeLimit() * 100);
	}
}

bool ArcherController::moveLeftAngRightLock = false;
bool ArcherController::moveUpAndDownLock = false;
bool ArcherController::onAir = true;
bool ArcherController::climbing = false;
void ArcherController::onKeyPressed(EventKeyboard::KeyCode keycode, Event*event) {
	float x = archer_->getPositionX();
	float y = archer_->getPositionY();

	if (EventKeyboard::KeyCode::KEY_UP_ARROW == keycode || EventKeyboard::KeyCode::KEY_W == keycode) {
		if (climbing == false) {
			if (onAir == false) {
				archer_->jump();
			}
		}
		else {
			if (moveUpAndDownLock == false) {
				moveUpAndDownLock = true;
				archer_->climbUp();
			}
		}
	}
	else if (EventKeyboard::KeyCode::KEY_DOWN_ARROW == keycode || EventKeyboard::KeyCode::KEY_S == keycode) {
		if (climbing == true) {
			if (moveUpAndDownLock == false) {
				moveUpAndDownLock = true;
				archer_->climbDown();
			}
		}
	}
	else if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keycode || EventKeyboard::KeyCode::KEY_A == keycode) {
		if (moveLeftAngRightLock == false) {
			moveLeftAngRightLock = true;
			archer_->running(false,climbing);
		}
	}
	else if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keycode || EventKeyboard::KeyCode::KEY_D == keycode) {
		if (moveLeftAngRightLock == false) {
			moveLeftAngRightLock = true;
			archer_->running(true, climbing);
		}
	}
	else if (EventKeyboard::KeyCode::KEY_F == keycode){
		if (archer_->getBlue() >= archer_->getInitialBLue() / 2) {
			archer_->setBlue(archer_->getBlue() - archer_->getInitialBLue() / 2);
			Size mapSize = ParameterManager::getGameParameterInstance(ParameterManager::getCurrentGameLevel())->mapSize;
			int createArrowNum = 11;
			float x = archer_->getPositionX();
			float y = archer_->getPositionY();
			for (int i = -createArrowNum / 2; i <= createArrowNum / 2; i++){
				if (archer_->getDirection() == true) {
					this->addChild(arrow::createArrowRain(Vec2(x + 100 * i, y + 500), Vec2(x + 100 * i + 1, y + 500 - 2), 0), 3);
				}
				else {
					this->addChild(arrow::createArrowRain(Vec2(x + 100 * i, y + 500), Vec2(x + 100 * i - 1, y + 500 - 2), 0), 3);
				}
			}
		}
	}

	else if (EventKeyboard::KeyCode::KEY_U == keycode) {
		archer_->addChild(arrow::createAnArrow(Vec2(x, y), Vec2(x - 1, y + 0.5), 0, archer_->getWeapon()), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_I == keycode) {
		archer_->addChild(arrow::createAnArrow(Vec2(x, y), Vec2(x - 1, y + 1), 0, archer_->getWeapon()), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_O == keycode) {
		archer_->addChild(arrow::createAnArrow(Vec2(x, y), Vec2(x + 1, y + 1), 0, archer_->getWeapon()), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_P == keycode) {
		archer_->addChild(arrow::createAnArrow(Vec2(x, y), Vec2(x + 1, y + 0.5), 0, archer_->getWeapon()), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_J == keycode) {
		archer_->addChild(arrow::createAnArrow(Vec2(x, y), Vec2(x - 1, y), 0, archer_->getWeapon()), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_SEMICOLON == keycode) {
		archer_->addChild(arrow::createAnArrow(Vec2(x, y), Vec2(x + 1, y), 0, archer_->getWeapon()), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_M == keycode) {
		archer_->addChild(arrow::createAnArrow(Vec2(x, y), Vec2(x - 1, y - 0.5), 0, archer_->getWeapon()), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_COMMA == keycode) {
		archer_->addChild(arrow::createAnArrow(Vec2(x, y), Vec2(x - 1, y - 1), 0, archer_->getWeapon()), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_PERIOD == keycode) {
		archer_->addChild(arrow::createAnArrow(Vec2(x, y), Vec2(x + 1, y - 1), 0, archer_->getWeapon()), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_SLASH == keycode) {
		archer_->addChild(arrow::createAnArrow(Vec2(x, y), Vec2(x + 1, y - 0.5), 0, archer_->getWeapon()), 3);
	}
}

void ArcherController::onKeyReleased(EventKeyboard::KeyCode keycode, Event*event) {
	if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keycode || EventKeyboard::KeyCode::KEY_A == keycode) {
		moveLeftAngRightLock = false;
		archer_->stopActionByTag(Constant::getArcherMoveLeftActionTag());
		//auto velocity = archer_->getPhysicsBody()->getVelocity();
		//archer_->getPhysicsBody()->setVelocity(Vec2(0, velocity.y));
		if (climbing == false){
			archer_->stopping();
		}
	}
	else if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keycode || EventKeyboard::KeyCode::KEY_D == keycode) {
		moveLeftAngRightLock = false;
		archer_->stopActionByTag(Constant::getArcherMoveRightActionTag());
		//auto velocity = archer_->getPhysicsBody()->getVelocity();
		//archer_->getPhysicsBody()->setVelocity(Vec2(0, velocity.y));
		if (climbing == false){
			archer_->stopping();
		}
	}
	else if (EventKeyboard::KeyCode::KEY_UP_ARROW == keycode || EventKeyboard::KeyCode::KEY_W == keycode) {
		if (climbing == true){
			moveUpAndDownLock = false;
			archer_->stopActionByTag(Constant::getArcherClimbUpActionTag());
			archer_->stoppingClimbing();
		}
	}
	else if (EventKeyboard::KeyCode::KEY_DOWN_ARROW == keycode || EventKeyboard::KeyCode::KEY_S == keycode) {
		if (climbing == true) {
			moveUpAndDownLock = false;
			archer_->stopActionByTag(Constant::getArcherClimbDownActionTag());
			archer_->stoppingClimbing();
		}
	}
}

void ArcherController::landGround() {
	onAir = false;
	auto velocity = archer_->getPhysicsBody()->getVelocity();
	archer_->getPhysicsBody()->setVelocity(Vec2(velocity.x, 0));
}

void ArcherController::leaveGround() {
	onAir = true;
}

void ArcherController::attacked(Node* aNode, int attackType) {
	switch (attackType) {
	case 1://被敌人撞到
		archer_->attacked(((Enemy*)aNode)->getPower());
		break;
	case 2://被箭射到
		archer_->attacked(((Enemy*)(aNode->getParent()))->getPower());
		break;
	default:
		break;
	}
}

void ArcherController::setWeapon(int type){
	archer_->setWeapon(type);
}

void ArcherController::gameEndedAndRemove() {
	archer_->removeFromParentAndCleanup(true);
	this->pause();
}

void ArcherController::touchRope() {
	if (onAir == true) {
		moveUpAndDownLock = false;
		climbing = true;
		archer_->climb();
	}
}

void ArcherController::leaveRope() {
	//if (onAir == true) {
		climbing = false;
		archer_->notClimb(moveLeftAngRightLock);
		archer_->stopActionByTag(Constant::getArcherClimbUpActionTag());
		archer_->stopActionByTag(Constant::getArcherClimbDownActionTag());
	//}
}

void ArcherController::createArrowRainTouch(Node* arrowRainNode) {
	auto arrowRainSprite = (arrow*)arrowRainNode;
	archer_->addChild(arrow::createArrowRainTouch(arrowRainSprite->getRotation(), arrowRainSprite->getPosition()));
}

void ArcherController::updateTimeForAddExp(float dt) {
	if (moveLeftAngRightLock == false && moveUpAndDownLock == false) {
		if (climbing == false && onAir == true) {
			return;
		}
		auto currentBlue = archer_->getBlue();
		auto totalBlue = archer_->getInitialBLue();
		if (currentBlue < totalBlue) {
			currentBlue += totalBlue / 30;
			if (currentBlue > totalBlue) {
				currentBlue = totalBlue;
			}
			archer_->setBlue(currentBlue);
		}
	}
}