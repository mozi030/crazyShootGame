#include"GamePlayingScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"../levelChooseScene/LevelChooseScene.h"
#include"../../public/parameterManager/ParameterManager.h"
#include"../../public/Constant/Constant.h"
#include"Controller/setGameCacheController/SetGameCacheController.h"
#include"Controller/archerController/archerController.h"
#include"Controller/progressTimeController/ProgressTimeController.h"
#include"Controller\groundController\GroundController.h"
#include"Controller\enemyController\EnemyController.h"
#include"Controller\arrowController\ArrowController.h"

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
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	SetGameCacheController::getInstance()->setGameCache();

	auto map = CSLoader::createNode(Constant::getLevel1MapCsdPath());
	this->addChild(map,0);

	//加入弓箭手
	this->addChild(ArcherController::getInstance(),1);
	
	//进度条
	this->addChild(ProgressTimeController::getInstance(), 1);

	//地板
	this->addChild(GroundController::getInstance(),1);

	//产生敌人
	this->addChild(EnemyController::getInstance(),1);

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
	this->addChild(menu,1);

	Size visibleSize = ParameterManager::getVisibleSize();
	auto gameEndedItem = MenuItemImage::create(Constant::getGameEndedPath(), Constant::getGameEndedPath(), CC_CALLBACK_1(GamePlayingScene::ClickGameEnded, this));
	gameEndedItem->setPosition(visibleSize.width, visibleSize.height);
	gameEndedItem->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	menu->addChild(gameEndedItem);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GamePlayingScene::onKeyPressed,this); 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);
}

void GamePlayingScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event*event) {
	if (EventKeyboard::KeyCode::KEY_UP_ARROW == keycode) {

	}
	else if (EventKeyboard::KeyCode::KEY_DOWN_ARROW == keycode) {

	}
	else if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keycode) {
		ArcherController::getInstance()->getArcher()->runAction(MoveBy::create(1,Vec2(-20,0)));
	}
	else if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keycode) {
		ArcherController::getInstance()->getArcher()->runAction(MoveBy::create(1, Vec2(20, 0)));
	}
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
	Vec2 beginPosition = ArcherController::getInstance()->getArcher()->getPosition();
	xBegin = beginPosition.x + 20.0;
	yBegin = beginPosition.y + 20.0;
	xEnd = touchEndedPosition.x;
	yEnd = touchEndedPosition.y;

	this->addChild(ArrowController::createAnArrow(xBegin, yBegin, xEnd, yEnd), 3);
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
	//箭射到地
	if (tagA == Constant::getBottomGroundTag() && tagB == Constant::getArrowTag()) {
		if (contact.getShapeB()->getBody() != NULL && contact.getShapeB()->getBody()->getNode() != NULL) {
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
	}
	else if (tagB == Constant::getBottomGroundTag() && tagA == Constant::getArrowTag()) {
		if (contact.getShapeA()->getBody() != NULL && contact.getShapeA()->getBody()->getNode() != NULL) {
			contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
	}
	//箭射到敌人
	else if (tagA == Constant::getArrowTag() && tagB >= Constant::getEnemyTag1() && tagB <= Constant::getEnemyTag3()) {
		auto ABody = contact.getShapeA()->getBody();
		auto BBody = contact.getShapeB()->getBody();
		if (ABody != NULL && ABody->getNode() != NULL) {
			ABody->getNode()->removeFromParentAndCleanup(true);
		}
		if (BBody != NULL && BBody->getNode() != NULL) {
			EnemyController::getInstance()->EnemyAttacked(BBody->getNode()->getParent(), BBody->getNode()->getPosition());
			/*auto enemySprite = (Sprite*)BBody->getNode();
			auto enemyNode = (Enemy*)enemySprite->getParent();
			enemyNode->setBlood(enemyNode->getBlood() - 1);
			if (enemyNode->getBlood() == 0) {
			this->addChild(enemyNode->createDispearSprite(enemyNode->getMode()));

			enemySprite->removeFromParentAndCleanup(true);
			enemyNode->removeFromParentAndCleanup(true);
			}*/
		}
	}
	else if (tagB == Constant::getArrowTag() && tagA >= Constant::getEnemyTag1() && tagA <= Constant::getEnemyTag3()) {
		auto ABody = contact.getShapeA()->getBody();
		auto BBody = contact.getShapeB()->getBody();
		if (BBody != NULL && BBody->getNode() != NULL) {
			BBody->getNode()->removeFromParentAndCleanup(true);
		}
		if (ABody != NULL && ABody->getNode() != NULL) {
			EnemyController::getInstance()->EnemyAttacked(ABody->getNode()->getParent(), ABody->getNode()->getPosition());
			/*auto enemySprite = (Sprite*)ABody->getNode();
			auto enemyNode = (Enemy*)enemySprite->getParent();
			enemyNode->setBlood(enemyNode->getBlood() - 1);
			if (enemyNode->getBlood() == 0) {
			this->addChild(enemyNode->createDispearSprite(enemyNode->getMode()));

			enemySprite->removeFromParentAndCleanup(true);
			enemyNode->removeFromParentAndCleanup(true);
			}*/
		}
	}
	//敌人碰到射手
	else if (tagA == Constant::getArcherTag() && tagB >= Constant::getEnemyTag1() && tagB <= Constant::getEnemyTag3()) {
		//gameover
		;
	}
	else if (tagB == Constant::getArcherTag() && tagA >= Constant::getEnemyTag1() && tagA <= Constant::getEnemyTag3()) {
		//gameover
		;
	}

	return true;
}

void GamePlayingScene::ClickGameEnded(Ref* sender)
{
	auto aScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, aScene, false);
	Director::getInstance()->replaceScene(transition);

	ParameterManager::deleteAll();
}

