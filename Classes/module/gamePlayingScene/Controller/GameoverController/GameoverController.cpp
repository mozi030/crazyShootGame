#include"GameoverController.h"

GameoverController*GameoverController::gameoverController = NULL;

GameoverController::GameoverController() {}

GameoverController::~GameoverController() {
	if (gameoverController != NULL) {
		gameoverController->removeFromParentAndCleanup(true);
		gameoverController = NULL;
	}
}

GameoverController* GameoverController::getInstance() {
	if (gameoverController == NULL) {
		gameoverController = GameoverController::create();
		gameoverController->setPosition(0, 0);
		//gameoverController->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	}
	return gameoverController;
}

bool GameoverController::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = ParameterManager::getVisibleSize();
	Vec2 cameraPosition = CameraController::getInstance()->getCamera()->getPosition();
	auto gameover = CSLoader::createNode(Constant::getGameOverCsdPath());
	gameover->setPosition(cameraPosition.x - visibleSize.width / 2, cameraPosition.y - visibleSize.height / 2);
	this->addChild(gameover, 2);
	// gameover background
	gameoverMenu = Menu::create();
	gameoverMenu->setPosition(cameraPosition.x - visibleSize.width / 2, cameraPosition.y - visibleSize.height / 2);
	this->addChild(gameoverMenu, 3);

	auto guanka = MenuItemImage::create("GamePlayingScene/GameOverCsd/guanka.png", "GamePlayingScene/GameOverCsd/guanka.png", CC_CALLBACK_1(GameoverController::guanka, this));
	guanka->setPosition(326.84, 161.56);
	gameoverMenu->addChild(guanka);

	auto aLabel = Label::create("SAVE", "Arial", 20);
	aLabel->setColor(Color3B::BLUE);
	aLabel->setPosition(gameoverMenu->getPositionX() + 326.84, gameoverMenu->getPositionY() + 110);
	this->addChild(aLabel,3);

	auto again = MenuItemImage::create("GamePlayingScene/GameOverCsd/again.png", "GamePlayingScene/GameOverCsd/again.png", CC_CALLBACK_1(GameoverController::again, this));
	again->setPosition(518.40, 165.96);
	gameoverMenu->addChild(again);

	aLabel = Label::create("RETURN", "Arial", 20);
	aLabel->setColor(Color3B::BLUE);
	aLabel->setPosition(gameoverMenu->getPositionX() + 518.40, gameoverMenu->getPositionY() + 110);
	this->addChild(aLabel, 3);

	auto next = MenuItemImage::create("GamePlayingScene/GameOverCsd/next.png", "GamePlayingScene/GameOverCsd/next.png", CC_CALLBACK_1(GameoverController::next, this));
	next->setPosition(700, 165.31);
	gameoverMenu->addChild(next);

	aLabel = Label::create("RETURN", "Arial", 20);
	aLabel->setColor(Color3B::BLUE);
	aLabel->setPosition(gameoverMenu->getPositionX() + 700, gameoverMenu->getPositionY() + 110);
	this->addChild(aLabel, 3);

	return true;
}

void GameoverController::guanka(Ref* sender)
{
	//存档
	int i;
	for (i = 1; i <= 6; i++) {
		auto a =  databaseManager::databaseSelete(i);
		if (a.recordNum == 0) break;
	}
	if (i == 7) i = 1;
	aDataTemplete.recordNum = i;
	databaseManager::databaseSave(aDataTemplete);
}

void GameoverController::again(Ref* sender)
{
	auto againScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, againScene, false);
	Director::getInstance()->replaceScene(transition);
	ParameterManager::deleteAll();
}

void GameoverController::next(Ref* sender)
{
	auto next = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, next, false);
	Director::getInstance()->replaceScene(transition);
	ParameterManager::deleteAll();
}

void GameoverController::gameEnded(bool isWin) {
	if (isWin == true) {
		item::addTotalScore(archer::getInstance()->getScore());
		int currentGameLevel = ParameterManager::getCurrentGameLevel();
		if (currentGameLevel == item::getHighestGameLevel()) {
			item::setHighestGameLevel(currentGameLevel + 1);
		}

		auto scoreLabel = Label::createWithBMFont("fonts/futura-48.fnt", "score: " + to_string(archer::getInstance()->getScore()));
		gameoverMenu->addChild(scoreLabel);
		scoreLabel->setPosition(260,350);
		scoreLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

		auto totalScoreLabel = Label::createWithBMFont("fonts/futura-48.fnt", "total score: " + to_string(item::getTotalScore()));
		gameoverMenu->addChild(totalScoreLabel);
		totalScoreLabel->setPosition(260, 300);
		totalScoreLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

		auto currentLevelLabel = Label::createWithBMFont("fonts/futura-48.fnt", "current level: " + to_string(item::getCurrentArcherLevel()));
		gameoverMenu->addChild(currentLevelLabel);
		currentLevelLabel->setPosition(260, 250);
		currentLevelLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

		auto totalMoneylLabel = Label::createWithBMFont("fonts/futura-48.fnt", "total money: " + item::getMoneyNum());
		gameoverMenu->addChild(totalMoneylLabel);
		totalMoneylLabel->setPosition(260, 200);
		totalMoneylLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	}
	else {
		auto totalMoneylLabel = Label::createWithBMFont("fonts/futura-48.fnt", "YOU LOSE!");
		gameoverMenu->addChild(totalMoneylLabel);
		totalMoneylLabel->setPosition(390, 275);
		totalMoneylLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	}
	item::setExp(archer::getInstance()->getExp());

	aDataTemplete.bloodBottleNum = item::getHp();
	aDataTemplete.blueBottleNum = item::getBp();
	aDataTemplete.coinNum = item::getMoney();
	aDataTemplete.currentArcherLevel = item::getCurrentArcherLevel();
	aDataTemplete.highestGameLevel = item::getHighestGameLevel();
	aDataTemplete.totalScore = item::getTotalScore();
	aDataTemplete.weapon1Num = item::getArrow();
	aDataTemplete.weapon2Num = 0;
	aDataTemplete.exp = item::getExp(); 

	char nameOfTemp[30]; 
	memset(nameOfTemp, 0, 30);
	time_t now;
	now = time(NULL); //获取当前时间
	sprintf(nameOfTemp,"%s",ctime(&now));
	string str(nameOfTemp);
	string date = str.substr(20,4) + str.substr(3,7);
	//int firstBlank = find(str.begin(), str.end(), '\ ');
	aDataTemplete.date = date;

	//CameraController::getInstance()->removeFromParentAndCleanup(true);
	ArcherController::getInstance()->gameEndedAndRemove();
	EnemyController::getInstance()->gameEndedAndRemove();
}