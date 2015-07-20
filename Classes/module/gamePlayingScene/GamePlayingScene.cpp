#include"GamePlayingScene.h"
#include"../../public/parameterManager/ParameterManager.h"
#include"Controller/setGameCacheController/SetGameCacheController.h"
#include"Controller/archerController/archerController.h"
#include"Model/Constant/Constant.h"
#include"Controller/progressTimeController/ProgressTimeController.h"
#include"Controller\groundController\GroundController.h"
#include"Controller\enemyController\EnemyController.h"
#include"Controller\arrowController\ArrowController.h"
#include"../levelChooseScene/LevelChooseScene.h"

#define pi 3.141592654

GamePlayingScene* GamePlayingScene::createScene(){
	auto thisScene = new GamePlayingScene();
	thisScene->autorelease();
	thisScene->initWithPhysics();
	thisScene->initial();
	return thisScene;
}

void GamePlayingScene::initial() {
	this->getPhysicsWorld()->setGravity(ParameterManager::getGravity());

	SetGameCacheController::getInstance()->setGameCache();

	backgroundSprite = Sprite::create(Constant::getBackgroundPath());
	backgroundSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backgroundSprite->setPosition(0, 0);
	this->addChild(backgroundSprite, 0);

	//加入弓箭手
	this->addChild(archerController::getInstance(),1);
	
	//进度条
	this->addChild(ProgressTimeController::getInstance(), 1);

	//地板
	this->addChild(GroundController::getInstance(),1);

	//产生敌人
	this->schedule(schedule_selector(GamePlayingScene::updateTimeToCreateEnemy), 3.0f);

	//物理世界监听
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(GamePlayingScene::onContactBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//触屏 listener
	EventListenerTouchOneByOne* screenListener = EventListenerTouchOneByOne::create();
	screenListener->setSwallowTouches(true);// true不向下触摸，简单点来说，比如有两个sprite ,A和 B，A在上B在下（位置重叠）
	screenListener->onTouchBegan = CC_CALLBACK_2(GamePlayingScene::onTouchBegan, this);
	screenListener->onTouchEnded = CC_CALLBACK_2(GamePlayingScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(screenListener, this);

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(menu);

	Size visibleSize = ParameterManager::getVisibleSize();
	auto gameEndedItem = MenuItemImage::create("image/menuGameEnded.png", "image/menuGameEnded.png", CC_CALLBACK_1(GamePlayingScene::ClickGameEnded, this));
	gameEndedItem->setPosition(visibleSize.width, visibleSize.height);
	gameEndedItem->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	menu->addChild(gameEndedItem);
}

void GamePlayingScene::setGameParameter() {
	this->getPhysicsWorld()->setGravity(ParameterManager::getGravity());
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}

float xBegin, yBegin, xEnd, yEnd;
bool GamePlayingScene::onTouchBegan(Touch *touch, Event *unused_event){
	totalTime = 0;
	this->schedule(schedule_selector(GamePlayingScene::updateTimeForProgressBar), 0.1f);
	return true;
}

void GamePlayingScene::onTouchEnded(Touch *touch, Event *unused_event){
	this->unschedule(schedule_selector(GamePlayingScene::updateTimeForProgressBar));

	Vec2 touchEndedPosition = touch->getLocation();
	xEnd = touchEndedPosition.x;
	yEnd = touchEndedPosition.y;
	//创建弓箭
	this->addChild(ArrowController::createAnArrow(xEnd,yEnd), 3);
}

void GamePlayingScene::updateTimeForProgressBar(float dt){
	totalTime += dt;
	if (totalTime >= Constant::getTimeLimit() / 10)
	{
		ProgressTimeController::getInstance()->getProgressTimer()->setPercentage(0);
		ProgressTimeController::getInstance()->getProgressTimerLabel()->setString("0%");
		totalTime = 0;
		return;
	}
	else {
		int a = totalTime * 10.0 / Constant::getTimeLimit() * 100;
		ProgressTimeController::getInstance()->getProgressTimer()->setPercentage(a);
		ProgressTimeController::getInstance()->getProgressTimerLabel()->setString(CCString::createWithFormat("%d", a)->_string + "%");
	}
}

bool GamePlayingScene::onContactBegan(PhysicsContact& contact)
{
	Size visibleSize = ParameterManager::getVisibleSize();
	int tagA = contact.getShapeA()->getTag();
	int tagB = contact.getShapeB()->getTag();
	if (tagA == Constant::getGroundTag() && tagB == Constant::getArrowTag()) {
		if (contact.getShapeB()->getBody() != NULL && contact.getShapeB()->getBody()->getNode() != NULL) {
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
	}
	else if (tagB == Constant::getGroundTag() && tagA == Constant::getArrowTag()) {
		if (contact.getShapeA()->getBody() != NULL && contact.getShapeA()->getBody()->getNode() != NULL) {
			contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
	}
	else if (tagA == Constant::getArrowTag() && tagB == Constant::getEnemyTag()) {
		if (contact.getShapeA()->getBody() != NULL && contact.getShapeA()->getBody()->getNode() != NULL) {
			contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
		if (contact.getShapeB()->getBody() != NULL && contact.getShapeB()->getBody()->getNode() != NULL) {
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
	}
	else if (tagB == Constant::getArrowTag() && tagA == Constant::getEnemyTag()) {
		if (contact.getShapeA()->getBody() != NULL && contact.getShapeA()->getBody()->getNode() != NULL) {
			contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
		if (contact.getShapeB()->getBody() != NULL && contact.getShapeB()->getBody()->getNode() != NULL) {
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
	}
	else if (tagA == Constant::getArcherTag() && tagB == Constant::getEnemyTag()) {
		//gameover
		;
	}
	else if (tagB == Constant::getArcherTag() && tagA == Constant::getEnemyTag()) {
		//gameover
		;
	}

	return true;
}

void GamePlayingScene::updateTimeToCreateEnemy(float dt) {
	this->addChild(EnemyController::createAnEnemy(), 1);
}

void GamePlayingScene::ClickGameEnded(Ref* sender)
{
	//this->unscheduleAllCallbacks();
	//this->unscheduleAllSelectors();
	//this->stopAllActions();
	
	//delete SetGameCacheController::getInstance();
	SetGameCacheController::deleteInstance();
	//archerController::getInstance()->removeFromParentAndCleanup(true);
	//GroundController::getInstance()->removeFromParentAndCleanup(true);
	//ProgressTimeController::getInstance()->removeFromParentAndCleanup(true);

	//this->removeFromPhysicsWorld();
	//this->removeFromParentAndCleanup(true);

	auto aScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, aScene, false);
	Director::getInstance()->replaceScene(transition);
}

