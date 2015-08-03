#include"GamePlayingScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"../levelChooseScene/LevelChooseScene.h"
#include"../../public/parameterManager/ParameterManager.h"
#include"../../public/Constant/Constant.h"
#include"Controller/setGameCacheController/SetGameCacheController.h"
//#include"Controller/archerController/archerController.h"
//#include"Controller/progressTimeController/ProgressTimeController.h"
//#include"Controller\groundController\GroundController.h"
//#include"Controller\enemyController\EnemyController.h"
//#include"Controller\arrowController\ArrowController.h"

#define pi 3.141592654
Camera* GamePlayingScene::camera;

GamePlayingScene* GamePlayingScene::createScene(){
	camera = NULL;

	auto thisScene = new GamePlayingScene();
	thisScene->autorelease();
	thisScene->initWithPhysics();
	thisScene->initial();
	return thisScene;
}

void GamePlayingScene::initial() {
	this->getPhysicsWorld()->setGravity(ParameterManager::getGravity());
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	SetGameCacheController::getInstance()->setGameCache();

	map = CSLoader::createNode(Constant::getLevel1MapCsdPath());
	//map->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	//map->setPosition(Vec2::ZERO);
	this->addChild(map,0);

	//加入弓箭手
	player = ArcherController::getInstance();
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
	gameEndedItem = MenuItemImage::create(Constant::getGameEndedPath(), Constant::getGameEndedPath(), CC_CALLBACK_1(GamePlayingScene::ClickGameEnded, this));
	gameEndedItem->setPosition(visibleSize.width, visibleSize.height);
	gameEndedItem->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	//gameEndedItem->setVisible(false);
	menu->addChild(gameEndedItem);
	//gameEndedItem->setVisible(false);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GamePlayingScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GamePlayingScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);

	scheduleUpdate();
}

void GamePlayingScene::update(float dt) {
	Vec2 playerPosition = player->getArcher()->getPosition();
	Vec2 mapPosition = map->getPosition();
	if (camera == NULL) {
		camera = Camera::create();
		camera->setPosition(0,0);
		this->addChild(camera);
	}
	float x, y;
	if (playerPosition.x <= 512) {
		x = 512;
	}
	else if (playerPosition.x >= 1280 - 512){
		x = 1280 - 512;
	}
	else {
		x = playerPosition.x;
	}
	if (playerPosition.y <= 320) {
		y = 320;
	}
	else if (playerPosition.y >= 928 - 320) {
		y = 928 - 320;
	}
	else {
		y = playerPosition.y;
	}

	//ProgressTimeController::getInstance()->setPosition(x,y + 280);

	//Vec3 eyePosOld = camera->getPosition3D();

	Vec3 eyePos = Vec3(x, y, camera->getPositionZ());
	camera->setPosition3D(eyePos);
	camera->lookAt(Vec3(eyePos.x, eyePos.y, 0));
}

float moveLeftAngRightLock = false;
float onAir = true;
void GamePlayingScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event*event) {
	float x = player->getArcher()->getPositionX();
	float y = player->getArcher()->getPositionY();


	if (EventKeyboard::KeyCode::KEY_UP_ARROW == keycode || EventKeyboard::KeyCode::KEY_W == keycode) {
		if (onAir == false) {
			onAir = true;
			ArcherController::getInstance()->getArcher()->jump();
		}
	}
	else if (EventKeyboard::KeyCode::KEY_DOWN_ARROW == keycode || EventKeyboard::KeyCode::KEY_S == keycode) {

	}
	else if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keycode || EventKeyboard::KeyCode::KEY_A == keycode) {
		if (moveLeftAngRightLock == false) {
			moveLeftAngRightLock = true;
			//this->schedule(CC_CALLBACK_1(updateTimeToMoveLeft, this), 0);
			ArcherController::getInstance()->getArcher()->ArcherDirection = false;
			ArcherController::getInstance()->getArcher()->running();
			auto action = RepeatForever::create(MoveBy::create(1, Vec2(-100, 0)));
			action->setTag(12345);
			ArcherController::getInstance()->getArcher()->runAction(action);
		}
	}
	else if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keycode || EventKeyboard::KeyCode::KEY_D == keycode) {
		if (moveLeftAngRightLock == false) {
			moveLeftAngRightLock = true;
			//this->schedule(CC_CALLBACK_1(updateTimeToMoveRight, this), 0);
			ArcherController::getInstance()->getArcher()->ArcherDirection = true;
			ArcherController::getInstance()->getArcher()->running();
			auto action = RepeatForever::create(MoveBy::create(1, Vec2(100, 0)));
			action->setTag(1234);
			ArcherController::getInstance()->getArcher()->runAction(action);
		}
	}

	else if (EventKeyboard::KeyCode::KEY_U == keycode) {
		this->addChild(ArrowController::createAnArrow(x, y, x - 1, y + 0.5), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_I == keycode) {
		this->addChild(ArrowController::createAnArrow(x, y, x - 1, y + 1), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_O == keycode) {
		this->addChild(ArrowController::createAnArrow(x, y, x + 1, y + 1), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_P == keycode) {
		this->addChild(ArrowController::createAnArrow(x, y, x + 1, y + 0.5), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_J == keycode) {
		this->addChild(ArrowController::createAnArrow(x, y, x - 1, y), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_SEMICOLON == keycode) {
		this->addChild(ArrowController::createAnArrow(x, y, x, y + 1), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_M == keycode) {
		this->addChild(ArrowController::createAnArrow(x, y, x - 1, y - 0.5), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_COMMA == keycode) {
		this->addChild(ArrowController::createAnArrow(x, y, x - 1, y - 1), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_PERIOD == keycode) {
		this->addChild(ArrowController::createAnArrow(x, y, x + 1, y - 1), 3);
	}
	else if (EventKeyboard::KeyCode::KEY_LEFT_BRACE == keycode) {
		this->addChild(ArrowController::createAnArrow(x, y, x + 1, y - 0.5), 3);
	}
}

//键盘释放，静止状态
void GamePlayingScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event*event) {

	if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keycode || EventKeyboard::KeyCode::KEY_A == keycode) {
		moveLeftAngRightLock = false;
		ArcherController::getInstance()->getArcher()->stopActionByTag(12345);
		ArcherController::getInstance()->getArcher()->stopping();
	}
	else if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keycode || EventKeyboard::KeyCode::KEY_D == keycode) {
		moveLeftAngRightLock = false;
		ArcherController::getInstance()->getArcher()->stopActionByTag(1234);
		ArcherController::getInstance()->getArcher()->stopping();
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
	if (contact.getShapeB()->getBody() == NULL || contact.getShapeB()->getBody()->getNode() == NULL
	 || contact.getShapeA()->getBody() == NULL || contact.getShapeA()->getBody()->getNode() == NULL) {
		return true;
	}
	Size visibleSize = ParameterManager::getVisibleSize();
	int tagA = contact.getShapeA()->getTag();
	int tagB = contact.getShapeB()->getTag();

	//archer的箭射到地板
	if (tagA == Constant::getBottomGroundTag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getBottomGroundTag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//archer碰到到地板
	if (tagA == Constant::getBottomGroundTag() && tagB == Constant::getArcherTag()) {
		onAir = false;
		player->getArcher()->getPhysicsBody()->setVelocity(Vec2::ZERO);
	}
	else if (tagB == Constant::getBottomGroundTag() && tagA == Constant::getArcherTag()) {
		onAir = false;
		player->getArcher()->getPhysicsBody()->setVelocity(Vec2::ZERO);
	}

	//enemy的箭射到地板
	else if (tagA == Constant::getBottomGroundTag() && tagB == Constant::getEnemyArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getBottomGroundTag() && tagA == Constant::getEnemyArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//archer的箭射到墙壁
	else if (tagA == Constant::getLeftGroundTag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getLeftGroundTag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//enemy的箭射到墙壁
	else if (tagA == Constant::getLeftGroundTag() && tagB == Constant::getEnemyArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getLeftGroundTag() && tagA == Constant::getEnemyArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//enemy碰到墙壁
	else if (tagA == Constant::getLeftGroundTag() && tagB >= Constant::getEnemyTag1() && tagB <= Constant::getEnemyTag3()) {
		//掉头
		EnemyController * e = EnemyController::getInstance();
		e->Turn(contact.getShapeB()->getBody()->getNode());
	}
	else if (tagB == Constant::getLeftGroundTag() && tagA >= Constant::getEnemyTag1() && tagA <= Constant::getEnemyTag3()) {
		//掉头
		EnemyController * e = EnemyController::getInstance();
		e->Turn(contact.getShapeA()->getBody()->getNode());
	}

	//archer的箭碰到archer
	else if (tagA == Constant::getArcherTag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getArcherTag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//enemy碰到archer
	else if (tagA == Constant::getArcherTag() && tagB >= Constant::getEnemyTag1() && tagB <= Constant::getEnemyTag2()) {
		EnemyController * e = EnemyController::getInstance();
		e->Attack(contact.getShapeB()->getBody()->getNode(), contact.getShapeA()->getBody()->getNode());
		//敌人攻击动画
		//contact.getShapeB()->getBody()->getNode()->schedule(CC_CALLBACK_1(GamePlayingScene::JudgeContact, this, contact.getShapeA()->getBody()->getNode(), contact.getShapeB()->getBody()->getNode()), 0, CC_REPEAT_FOREVER, 0, "attackA");
		//掉血
		ArcherController::getInstance()->getArcher()->attacked(10);
	}
	else if (tagB == Constant::getArcherTag() && tagA >= Constant::getEnemyTag1() && tagA <= Constant::getEnemyTag2()) {
		EnemyController * e = EnemyController::getInstance();
		e->Attack(contact.getShapeA()->getBody()->getNode(), contact.getShapeB()->getBody()->getNode());
		//contact.getShapeA()->getBody()->getNode()->schedule(CC_CALLBACK_1(GamePlayingScene::JudgeContact, this, contact.getShapeB()->getBody()->getNode(), contact.getShapeA()->getBody()->getNode()), 0, CC_REPEAT_FOREVER, 0, "attackB");
		//掉血
		ArcherController::getInstance()->getArcher()->attacked(10);
	}

	//enemy的箭射到archer
	else if (tagA == Constant::getArcherTag() && tagB == Constant::getEnemyArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		//掉血
		ArcherController::getInstance()->getArcher()->attacked(15);
	}
	else if (tagB == Constant::getArcherTag() && tagA == Constant::getEnemyArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		//掉血
		ArcherController::getInstance()->getArcher()->attacked(15);
	}

	//archer的箭射到enemy
	else if (tagA == Constant::getArrowTag() && tagB >= Constant::getEnemyTag1() && tagB <= Constant::getEnemyTag3()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		//enemy掉血
		EnemyController * e = EnemyController::getInstance();
		e->EnemyAttacked(contact.getShapeB()->getBody()->getNode());
	}
	else if (tagB == Constant::getArrowTag() && tagA >= Constant::getEnemyTag1() && tagA <= Constant::getEnemyTag3()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		EnemyController * e = EnemyController::getInstance();
		e->EnemyAttacked(contact.getShapeA()->getBody()->getNode());
		//enemy掉血
	}

	//archer的箭射到enemy的箭
	else if (tagA == Constant::getArrowTag() && tagB == Constant::getEnemyArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getArrowTag() && tagA == Constant::getEnemyArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//enemy的箭射到enemy
	else if (tagA == Constant::getEnemyArrowTag() && tagB >= Constant::getEnemyTag1() && tagB <= Constant::getEnemyTag3()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEnemyArrowTag() && tagA >= Constant::getEnemyTag1() && tagA <= Constant::getEnemyTag3()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	return true;
}

void GamePlayingScene::ClickGameEnded(Ref* sender)
{
	auto gameover = CSLoader::createNode(Constant::getGameOverCsdPath());
	this->addChild(gameover, 2);
	// gameover background
	Size visibleSize = ParameterManager::getVisibleSize();
	Menu* aMenu = Menu::create();
	aMenu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	aMenu->setPosition(0, 0);
	this->addChild(aMenu, 2); 

	auto guanka = MenuItemImage::create("GamePlayingScene/GameOverCsd/guanka.png", "GamePlayingScene/GameOverCsd/guanka.png", CC_CALLBACK_1(GamePlayingScene::guanka, this));
	guanka->setPosition(326.84, 161.56);
	aMenu->addChild(guanka, 2);

	auto again = MenuItemImage::create("GamePlayingScene/GameOverCsd/again.png", "GamePlayingScene/GameOverCsd/again.png", CC_CALLBACK_1(GamePlayingScene::again, this));
	again->setPosition(518.40, 165.96);
	aMenu->addChild(again, 2);

	auto next = MenuItemImage::create("GamePlayingScene/GameOverCsd/next.png", "GamePlayingScene/GameOverCsd/next.png", CC_CALLBACK_1(GamePlayingScene::next, this));
	next->setPosition(700, 165.31);
	aMenu->addChild(next, 2);

}


void GamePlayingScene::guanka(Ref* sender)
{
	auto levelScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, levelScene, false);
	Director::getInstance()->replaceScene(transition);
	ParameterManager::deleteAll();
}

void GamePlayingScene::again(Ref* sender)
{
	auto againScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, againScene, false);
	Director::getInstance()->replaceScene(transition);
	ParameterManager::deleteAll();
}

void GamePlayingScene::next(Ref* sender)
{
	auto next = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, next, false);
	Director::getInstance()->replaceScene(transition);
	ParameterManager::deleteAll();
}

