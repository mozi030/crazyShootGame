#include "HelloWorldScene.h"

static const int TAG_CONTROL_INFO = 1000;
static const int TAG_RECORD_INFO = 1001;
static const int TAG_ABOUT_INFO = 1003;
static const int TAG_CLOSE_BTN = 1004;

Scene* HelloWorld::createScene()
{
	auto aScene = Scene::create();
	auto layer = HelloWorld::create();
	aScene->addChild(layer);
	return aScene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("HelloWorldScene/HelloWorldSceneCsd/HelloWorldScene.csb");
	addChild(rootNode,0);

	//可视范围大小
	Size visibleSize = ParameterManager::getVisibleSize();

	//创建menu,4个按钮
	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(menu,1);
	menu->setTag(10000);
	
	startItem = MenuItemImage::create("HelloWorldScene/menuGameStart.png", "HelloWorldScene/menuGameStart.png", CC_CALLBACK_1(HelloWorld::ClickStart, this));
	startItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 75);

	loadGameItem = MenuItemImage::create("HelloWorldScene/menuLoadGame.png", "HelloWorldScene/menuLoadGame.png", CC_CALLBACK_1(HelloWorld::ClickLoadGame, this));
	loadGameItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 150);
	menu->addChild(loadGameItem,1);
	menu->addChild(startItem,1);

	descriptionItem = MenuItemImage::create("HelloWorldScene/menuControl.png", "HelloWorldScene/menuControl.png", CC_CALLBACK_1(HelloWorld::ClickDescription, this));
	descriptionItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 225);
	menu->addChild(descriptionItem,1);

	teamItem = MenuItemImage::create("HelloWorldScene/menuDescription.png", "HelloWorldScene/menuDescription.png", CC_CALLBACK_1(HelloWorld::ClickTeam, this));
	teamItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 300);
	menu->addChild(teamItem,1);

	auto aMenu = Menu::create();
	aMenu->setPosition(Vec2::ZERO);
	aMenu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	closeItem = MenuItemImage::create("HelloWorldScene/skip.png", "HelloWorldScene/skip.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Point(605.37, 383.99));
	aMenu->addChild(closeItem, 2);
	closeItem->setVisible(false);
	closeItem->setTag(TAG_CLOSE_BTN);
	this->addChild(aMenu, 2); 

	auto control = Sprite::create("HelloWorldScene/control-back.png");
	control->setPosition(390.30, 256.90);
	this->addChild(control,1);
	control->setVisible(false);
	control->setTag(TAG_CONTROL_INFO);

	auto record = Sprite::create("HelloWorldScene/record-back.png");
	record->setPosition(390.30, 256.90);
	this->addChild(record,1);
	record->setVisible(false);
	record->setTag(TAG_RECORD_INFO);

	auto about = Sprite::create("HelloWorldScene/about-back.png");
	about->setPosition(390.30, 256.90);
	this->addChild(about,1);
	about->setVisible(false);
	about->setTag(TAG_ABOUT_INFO);

	//record窗口的按钮
	dataTemplete1 = databaseManager::databaseSelete(1);
	dataTemplete2 = databaseManager::databaseSelete(2);
	dataTemplete3 = databaseManager::databaseSelete(3);
	dataTemplete4 = databaseManager::databaseSelete(4);
	dataTemplete5 = databaseManager::databaseSelete(5);
	dataTemplete6 = databaseManager::databaseSelete(6);

	recordMenu = Menu::create();
	recordMenu->setPosition(Vec2::ZERO);
	recordMenu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(recordMenu, 2);
	recordMenu->setVisible(false);

	Label* aLabel;
	MenuItemLabel*aMenuItem;

	if (dataTemplete1.recordNum == 1) {
		aLabel = Label::create("\ \ record 1\n" + dataTemplete1.date, "Arial", 20);
		aLabel->setColor(Color3B::BLUE);
		aMenuItem = MenuItemLabel::create(aLabel, CC_CALLBACK_1(HelloWorld::LoadCallback1, this));
		aMenuItem->setPosition(Point(220, 293));
		recordMenu->addChild(aMenuItem, 2);
	}

	if (dataTemplete2.recordNum == 2) {
		aLabel = Label::create("\ \ record 2\n" + dataTemplete2.date, "Arial", 20);
		aLabel->setColor(Color3B::BLUE);
		aMenuItem = MenuItemLabel::create(aLabel, CC_CALLBACK_1(HelloWorld::LoadCallback2, this));
		aMenuItem->setPosition(Point(345, 293));
		recordMenu->addChild(aMenuItem, 2);
	}

	if (dataTemplete3.recordNum == 3) {
		aLabel = Label::create("\ \ record 3\n" + dataTemplete3.date, "Arial", 20);
		aLabel->setColor(Color3B::BLUE);
		aMenuItem = MenuItemLabel::create(aLabel, CC_CALLBACK_1(HelloWorld::LoadCallback3, this));
		aMenuItem->setPosition(Point(470, 293));
		recordMenu->addChild(aMenuItem, 2);
	}

	if (dataTemplete4.recordNum == 4) {
		aLabel = Label::create("\ \ record 4\n" + dataTemplete4.date, "Arial", 20);
		aLabel->setColor(Color3B::BLUE);
		aMenuItem = MenuItemLabel::create(aLabel, CC_CALLBACK_1(HelloWorld::LoadCallback4, this));
		aMenuItem->setPosition(Point(320, 140));
		recordMenu->addChild(aMenuItem, 2);
	}

	if (dataTemplete5.recordNum == 5) {
		aLabel = Label::create("\ \ record 5\n" + dataTemplete5.date, "Arial", 20);
		aLabel->setColor(Color3B::BLUE);
		aMenuItem = MenuItemLabel::create(aLabel, CC_CALLBACK_1(HelloWorld::LoadCallback5, this));
		aMenuItem->setPosition(Point(445, 140));
		recordMenu->addChild(aMenuItem, 2);
	}

	if (dataTemplete6.recordNum == 6) {
		aLabel = Label::create("\ \ record 6\n" + dataTemplete6.date, "Arial", 20);
		aLabel->setColor(Color3B::BLUE);
		aMenuItem = MenuItemLabel::create(aLabel, CC_CALLBACK_1(HelloWorld::LoadCallback6, this));
		aMenuItem->setPosition(Point(560, 140));
		recordMenu->addChild(aMenuItem, 2);
	}

	return true;
}

void HelloWorld::ClickStart(Ref* sender)
{
	item::setHighestGameLevel(1);
	item::setCurrentArcherLevel(1);
	item::setBpNum(0);
	item::setHpNum(0);
	item::setArrowNum(0);
	item::setMoney(0);
	item::setTotalScore(0);
	item::setExp(0);

	auto startScene = BackgroundStoryScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, startScene, false);
	Director::getInstance()->replaceScene(transition);
}

void HelloWorld::ClickDescription(Ref* sender)
{
	//操作说明
	startItem->setEnabled(false);
	descriptionItem->setEnabled(false);
	loadGameItem->setEnabled(false);
	teamItem->setEnabled(false);
	this->getChildByTag(TAG_CONTROL_INFO)->setVisible(true);
	closeItem->setVisible(true);
}

void HelloWorld::ClickLoadGame(Ref* sender)
{
	//读档
	startItem->setEnabled(false);
	descriptionItem->setEnabled(false);
	loadGameItem->setEnabled(false);
	teamItem->setEnabled(false);
	closeItem->setVisible(true);
	this->getChildByTag(TAG_RECORD_INFO)->setVisible(true);

	recordMenu->setVisible(true);
}

void HelloWorld::ClickTeam(Ref* sender)
{
	//团队介绍
	startItem->setEnabled(false);
	descriptionItem->setEnabled(false);
	loadGameItem->setEnabled(false);
	teamItem->setEnabled(false);
	this->getChildByTag(TAG_ABOUT_INFO)->setVisible(true);
	closeItem->setVisible(true);
}

void HelloWorld::menuCloseCallback(Ref* sender) {
	this->getChildByTag(TAG_CONTROL_INFO)->setVisible(false);
	this->getChildByTag(TAG_RECORD_INFO)->setVisible(false);
	this->getChildByTag(TAG_ABOUT_INFO)->setVisible(false);
	closeItem->setVisible(false);
	startItem->setEnabled(true);
	descriptionItem->setEnabled(true);
	loadGameItem->setEnabled(true);
	teamItem->setEnabled(true);

	recordMenu->setVisible(false);
}

void HelloWorld::LoadCallback1(Ref* sender) 
{
	item::setHighestGameLevel(dataTemplete1.highestGameLevel);
	item::setCurrentArcherLevel(dataTemplete1.currentArcherLevel);
	item::setBpNum(dataTemplete1.blueBottleNum);
	item::setHpNum(dataTemplete1.bloodBottleNum);
	item::setArrowNum(dataTemplete1.weapon1Num);
	item::setMoney(dataTemplete1.coinNum);
	item::setTotalScore(dataTemplete1.totalScore);
	item::setExp(dataTemplete1.exp);

	auto levelChosenScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, levelChosenScene, false);
	Director::getInstance()->replaceScene(transition);
}

void HelloWorld::LoadCallback2(Ref* sender)
{
	item::setHighestGameLevel(dataTemplete2.highestGameLevel);
	item::setCurrentArcherLevel(dataTemplete2.currentArcherLevel);
	item::setBpNum(dataTemplete2.blueBottleNum);
	item::setHpNum(dataTemplete2.bloodBottleNum);
	item::setArrowNum(dataTemplete2.weapon1Num);
	item::setMoney(dataTemplete2.coinNum);
	item::setTotalScore(dataTemplete2.totalScore);
	item::setExp(dataTemplete2.exp);

	auto levelChosenScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, levelChosenScene, false);
	Director::getInstance()->replaceScene(transition);
}

void HelloWorld::LoadCallback3(Ref* sender)
{
	item::setHighestGameLevel(dataTemplete3.highestGameLevel);
	item::setCurrentArcherLevel(dataTemplete3.currentArcherLevel);
	item::setBpNum(dataTemplete3.blueBottleNum);
	item::setHpNum(dataTemplete3.bloodBottleNum);
	item::setArrowNum(dataTemplete3.weapon1Num);
	item::setMoney(dataTemplete3.coinNum);
	item::setTotalScore(dataTemplete3.totalScore);
	item::setExp(dataTemplete3.exp);

	auto levelChosenScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, levelChosenScene, false);
	Director::getInstance()->replaceScene(transition);
}

void HelloWorld::LoadCallback4(Ref* sender)
{
	item::setHighestGameLevel(dataTemplete4.highestGameLevel);
	item::setCurrentArcherLevel(dataTemplete4.currentArcherLevel);
	item::setBpNum(dataTemplete4.blueBottleNum);
	item::setHpNum(dataTemplete4.bloodBottleNum);
	item::setArrowNum(dataTemplete4.weapon1Num);
	item::setMoney(dataTemplete4.coinNum);
	item::setTotalScore(dataTemplete4.totalScore);
	item::setExp(dataTemplete4.exp);

	auto levelChosenScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, levelChosenScene, false);
	Director::getInstance()->replaceScene(transition);
}

void HelloWorld::LoadCallback5(Ref* sender)
{
	item::setHighestGameLevel(dataTemplete5.highestGameLevel);
	item::setCurrentArcherLevel(dataTemplete5.currentArcherLevel);
	item::setBpNum(dataTemplete5.blueBottleNum);
	item::setHpNum(dataTemplete5.bloodBottleNum);
	item::setArrowNum(dataTemplete5.weapon1Num);
	item::setMoney(dataTemplete5.coinNum);
	item::setTotalScore(dataTemplete5.totalScore);
	item::setExp(dataTemplete5.exp);

	auto levelChosenScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, levelChosenScene, false);
	Director::getInstance()->replaceScene(transition);
}

void HelloWorld::LoadCallback6(Ref* sender)
{
	item::setHighestGameLevel(dataTemplete6.highestGameLevel);
	item::setCurrentArcherLevel(dataTemplete6.currentArcherLevel);
	item::setBpNum(dataTemplete6.blueBottleNum);
	item::setHpNum(dataTemplete6.bloodBottleNum);
	item::setArrowNum(dataTemplete6.weapon1Num);
	item::setMoney(dataTemplete6.coinNum);
	item::setTotalScore(dataTemplete6.totalScore);
	item::setExp(dataTemplete6.exp);

	auto levelChosenScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, levelChosenScene, false);
	Director::getInstance()->replaceScene(transition);
}