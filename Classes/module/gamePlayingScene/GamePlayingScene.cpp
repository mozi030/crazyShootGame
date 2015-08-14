#include"GamePlayingScene.h"

#define pi 3.141592654

GamePlayingScene* GamePlayingScene::createScene(){
	auto thisScene = new GamePlayingScene();
	thisScene->autorelease();
	thisScene->initWithPhysics();
	thisScene->initial();
	return thisScene;
}

void GamePlayingScene::initial() {
	isGameEnded = false;

	this->getPhysicsWorld()->setGravity(ParameterManager::getGravity());
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	SetGameCacheController::getInstance()->setGameCache();

	//加入地图
	if (ParameterManager::getCurrentGameLevel() == 1) {
		map = Sprite::create("MapScene/level1Map.png");
		map->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	}
	else if (ParameterManager::getCurrentGameLevel() == 2) {
		map = Sprite::create("MapScene/level2Map.png");
		map->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	}
	else if (ParameterManager::getCurrentGameLevel() == 3) {
		map = CSLoader::createNode(Constant::getLevel1MapCsdPath());
	}
	else if (ParameterManager::getCurrentGameLevel() == 4) {
		map = Sprite::create("MapScene/level4Map.png");
		map->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	}
	else if (ParameterManager::getCurrentGameLevel() == 5) {
		map = Sprite::create("MapScene/level5Map.png");
		map->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		this->addChild(weatherController::getInstance(),3);
	}
	this->addChild(map, 0);

	//加入弓箭手
	this->addChild(ArcherController::getInstance(),2);

	//地板
	this->addChild(EdgeController::getInstance(),1); 

	//产生敌人
	this->addChild(EnemyController::getInstance(), 1);

	//加入道具栏与携带道具的角色
	this->addChild(ItemController::getInstance(), 3);

	//物理世界监听
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(GamePlayingScene::onContactBegan, this);
	listener->onContactSeperate = CC_CALLBACK_1(GamePlayingScene::onContactSeperate, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//触屏 listener
	EventListenerTouchOneByOne* screenListener = EventListenerTouchOneByOne::create();
	screenListener->setSwallowTouches(true);// true不向下触摸，简单点来说，比如有两个sprite ,A和 B，A在上B在下（位置重叠）
	screenListener->onTouchBegan = CC_CALLBACK_2(GamePlayingScene::onTouchBegan, this);
	screenListener->onTouchEnded = CC_CALLBACK_2(GamePlayingScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(screenListener, this);

	//结束游戏按钮
	//this->addChild(GameoverController::getInstance(), 3);

	//update为镜头的移动
	this->addChild(CameraController::getInstance());
	scheduleUpdate();
}

void GamePlayingScene::update(float dt) {
	this->setCameraMask(2);
	if (isGameEnded == true) return;

	CameraController::getInstance()->updateCamera(isGameEnded);

	if (ArcherController::getInstance()->getArcher()->getBlood() == 0) {
		CameraController::getInstance()->lookAtInitial();
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		this->addChild(GameoverController::getInstance(), 3);
		this->getPhysicsWorld()->removeAllBodies();
		GameoverController::getInstance()->gameEnded(false);
		ItemController::getInstance()->removeFromParentAndCleanup(true);
		isGameEnded = true;
	}
	else if (EnemyController::getInstance()->totalEnemyNum == 0) {
		CameraController::getInstance()->lookAtInitial();
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		this->addChild(GameoverController::getInstance(), 3);
		this->getPhysicsWorld()->removeAllBodies();
		GameoverController::getInstance()->gameEnded(true);
		ItemController::getInstance()->removeFromParentAndCleanup(true);
		isGameEnded = true;
	}
}

bool GamePlayingScene::onTouchBegan(Touch *touch, Event *unused_event){
	ArcherController::touchBegan(touch->getLocation());
	return true;
}

void GamePlayingScene::onTouchEnded(Touch *touch, Event *unused_event){
	ArcherController::touchEnded(touch->getLocation());
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
	if (tagA == Constant::getEdge1Tag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdge1Tag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//archer碰到到地板
	if (tagA == Constant::getEdge1Tag() && tagB == Constant::getArcherTag()) {
		ArcherController::getInstance()->landGround();
	}
	else if (tagB == Constant::getEdge1Tag() && tagA == Constant::getArcherTag()) {
		ArcherController::getInstance()->landGround();
	}

	//enemy的箭射到地板
	else if (tagA == Constant::getEdge1Tag() && tagB == Constant::getEnemyArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdge1Tag() && tagA == Constant::getEnemyArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//archer的箭射到墙壁
	else if (tagA == Constant::getEdge2Tag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdge2Tag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//enemy的箭射到墙壁
	else if (tagA == Constant::getEdge2Tag() && tagB == Constant::getEnemyArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdge2Tag() && tagA == Constant::getEnemyArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//enemy碰到墙壁
	else if (tagA == Constant::getEdge2Tag() && tagB == Constant::getEnemyTag()) {
		//掉头
		EnemyController * e = EnemyController::getInstance();
		e->Turn(contact.getShapeB()->getBody()->getNode());
	}
	else if (tagB == Constant::getEdge2Tag() && tagA == Constant::getEnemyTag()) {
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
	else if (tagA == Constant::getArcherTag() && tagB == Constant::getEnemyTag()) {
		EnemyController * e = EnemyController::getInstance();
		e->Attack(contact.getShapeB()->getBody()->getNode(), contact.getShapeA()->getBody()->getNode());
		//敌人攻击动画
		//contact.getShapeB()->getBody()->getNode()->schedule(CC_CALLBACK_1(GamePlayingScene::JudgeContact, this, contact.getShapeA()->getBody()->getNode(), contact.getShapeB()->getBody()->getNode()), 0, CC_REPEAT_FOREVER, 0, "attackA");
		//掉血
		ArcherController::getInstance()->attacked(contact.getShapeB()->getBody()->getNode(),1);
	}
	else if (tagB == Constant::getArcherTag() && tagA == Constant::getEnemyTag()) {
		EnemyController * e = EnemyController::getInstance();
		e->Attack(contact.getShapeA()->getBody()->getNode(), contact.getShapeB()->getBody()->getNode());
		//contact.getShapeA()->getBody()->getNode()->schedule(CC_CALLBACK_1(GamePlayingScene::JudgeContact, this, contact.getShapeB()->getBody()->getNode(), contact.getShapeA()->getBody()->getNode()), 0, CC_REPEAT_FOREVER, 0, "attackB");
		//掉血
		ArcherController::getInstance()->attacked(contact.getShapeA()->getBody()->getNode(),1);
	}

	//enemy的箭射到archer
	else if (tagA == Constant::getArcherTag() && tagB == Constant::getEnemyArrowTag()) {
		//掉血
		ArcherController::getInstance()->attacked(contact.getShapeB()->getBody()->getNode(),2);
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getArcherTag() && tagA == Constant::getEnemyArrowTag()) {
		//掉血
		ArcherController::getInstance()->attacked(contact.getShapeA()->getBody()->getNode(), 2);
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//archer的箭射到enemy
	else if (tagA == Constant::getArrowTag() && tagB == Constant::getEnemyTag()) {
		//enemy掉血
		EnemyController * e = EnemyController::getInstance();
		e->EnemyAttacked(contact.getShapeB()->getBody()->getNode(), contact.getShapeA()->getBody()->getNode());

		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getArrowTag() && tagA == Constant::getEnemyTag()) {
		//enemy掉血
		EnemyController * e = EnemyController::getInstance();
		e->EnemyAttacked(contact.getShapeA()->getBody()->getNode(), contact.getShapeB()->getBody()->getNode());

		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//archer的箭雨射到enemy
	else if (tagA == Constant::getArrow4Tag() && tagB == Constant::getEnemyTag()) {
		//enemy掉血
		EnemyController * e = EnemyController::getInstance();
		e->EnemyAttacked(contact.getShapeB()->getBody()->getNode(), contact.getShapeA()->getBody()->getNode());

		//箭消失动画
		ArcherController::getInstance()->createArrowRainTouch(contact.getShapeA()->getBody()->getNode());
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getArrow4Tag() && tagA == Constant::getEnemyTag()) {
		//enemy掉血
		EnemyController * e = EnemyController::getInstance();
		e->EnemyAttacked(contact.getShapeA()->getBody()->getNode(), contact.getShapeB()->getBody()->getNode());

		//箭消失动画
		ArcherController::getInstance()->createArrowRainTouch(contact.getShapeB()->getBody()->getNode());
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
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
	else if (tagA == Constant::getEnemyArrowTag() && tagB == Constant::getEnemyTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEnemyArrowTag() && tagA == Constant::getEnemyTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//archer碰到绳子
	else if (tagA == Constant::getArcherTag() && tagB == Constant::getRopeTag()) {
		ArcherController::getInstance()->touchRope();
	}
	else if (tagB == Constant::getArcherTag() && tagA == Constant::getRopeTag()) {
		ArcherController::getInstance()->touchRope();
	}

	//archer的箭射到itermBall
	else if (tagA == Constant::getArrowTag() && tagB == Constant::getItermBallTag()) {
		ItemController *a = ItemController::getInstance();
		this->addChild(a->Drop((Sprite*)contact.getShapeA()->getBody()->getNode()));
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getArrowTag() && tagA == Constant::getItermBallTag()) {
		ItemController *a = ItemController::getInstance();
		this->addChild(a->Drop((Sprite*)contact.getShapeA()->getBody()->getNode()));

		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//archer碰到itermBall
	else if (tagA == Constant::getArcherTag() && tagB == Constant::getItermTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getArcherTag() && tagA == Constant::getItermTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	return true;
}

void GamePlayingScene::onContactSeperate(PhysicsContact& contact)
{
	if (contact.getShapeB()->getBody() == NULL || contact.getShapeB()->getBody()->getNode() == NULL
		|| contact.getShapeA()->getBody() == NULL || contact.getShapeA()->getBody()->getNode() == NULL) {
		return;
	}
	Size visibleSize = ParameterManager::getVisibleSize();
	int tagA = contact.getShapeA()->getTag();
	int tagB = contact.getShapeB()->getTag();
	//archer离开地板
	if (tagA == Constant::getEdge1Tag() && tagB == Constant::getArcherTag()) {
		ArcherController::getInstance()->leaveGround();
	}
	else if (tagB == Constant::getEdge1Tag() && tagA == Constant::getArcherTag()) {
		ArcherController::getInstance()->leaveGround();
	}
	//archer离开绳子
	else if (tagA == Constant::getArcherTag() && tagB == Constant::getRopeTag()) {
		ArcherController::getInstance()->leaveRope();
	}
	else if (tagB == Constant::getArcherTag() && tagA == Constant::getRopeTag()) {
		ArcherController::getInstance()->leaveRope();
	}
}