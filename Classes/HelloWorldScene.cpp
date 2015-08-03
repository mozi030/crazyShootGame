#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "module\BackgroundStoryScene\BackgroundStoryScene.h"
#include "public/parameterManager/ParameterManager.h"

USING_NS_CC;

static const int TAG_CONTROL_INFO = 1000;
static const int TAG_RECORD_INFO = 1001;
static const int TAG_RANK_INFO = 1002;
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
	menu->addChild(startItem,1);

	descriptionItem = MenuItemImage::create("HelloWorldScene/menuControl.png", "HelloWorldScene/menuControl.png", CC_CALLBACK_1(HelloWorld::ClickDescription, this));
	descriptionItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 225);
	menu->addChild(descriptionItem,1);

	loadGameItem = MenuItemImage::create("HelloWorldScene/menuLoadGame.png", "HelloWorldScene/menuLoadGame.png", CC_CALLBACK_1(HelloWorld::ClickLoadGame, this));
	loadGameItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 150);
	menu->addChild(loadGameItem,1);

	topRankItem = MenuItemImage::create("HelloWorldScene/menuTopRank.png", "HelloWorldScene/menuTopRank.png", CC_CALLBACK_1(HelloWorld::ClickTopRank, this));
	topRankItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 300);
	menu->addChild(topRankItem,1);

	teamItem = MenuItemImage::create("HelloWorldScene/menuDescription.png", "HelloWorldScene/menuDescription.png", CC_CALLBACK_1(HelloWorld::ClickTeam, this));
	teamItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 375);
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

	//auto onExitItem = MenuItemImage::create("HelloWorldScene/close.png", "HelloWorldScene/close.png", CC_CALLBACK_1(HelloWorld::onExit, this));
	//onExitItem->setPosition(0,100);
	//menu->addChild(onExitItem);


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

	auto rank = Sprite::create("HelloWorldScene/rank-back.png");
	rank->setPosition(390.30, 256.90);
	this->addChild(rank,1);
	rank->setVisible(false);
	rank->setTag(TAG_RANK_INFO);

	auto about = Sprite::create("HelloWorldScene/about-back.png");
	about->setPosition(390.30, 256.90);
	this->addChild(about,1);
	about->setVisible(false);
	about->setTag(TAG_ABOUT_INFO);
	return true;
}

void HelloWorld::ClickStart(Ref* sender)
{
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
	topRankItem->setEnabled(false);
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
	topRankItem->setEnabled(false);
	teamItem->setEnabled(false);
	this->getChildByTag(TAG_RECORD_INFO)->setVisible(true);
	closeItem->setVisible(true);
}

void HelloWorld::ClickTopRank(Ref* sender)
{
	//高分排名
	startItem->setEnabled(false);
	descriptionItem->setEnabled(false);
	loadGameItem->setEnabled(false);
	topRankItem->setEnabled(false);
	teamItem->setEnabled(false);
	this->getChildByTag(TAG_RANK_INFO)->setVisible(true);
	closeItem->setVisible(true);
}

void HelloWorld::ClickTeam(Ref* sender)
{
	//团队介绍
	startItem->setEnabled(false);
	descriptionItem->setEnabled(false);
	loadGameItem->setEnabled(false);
	topRankItem->setEnabled(false);
	teamItem->setEnabled(false);
	this->getChildByTag(TAG_ABOUT_INFO)->setVisible(true);
	closeItem->setVisible(true);
}

void HelloWorld::menuCloseCallback(Ref* sender) {
	this->getChildByTag(TAG_CONTROL_INFO)->setVisible(false);
	this->getChildByTag(TAG_RECORD_INFO)->setVisible(false);
	this->getChildByTag(TAG_RANK_INFO)->setVisible(false);
	this->getChildByTag(TAG_ABOUT_INFO)->setVisible(false);
	closeItem->setVisible(false);
	startItem->setEnabled(true);
	descriptionItem->setEnabled(true);
	loadGameItem->setEnabled(true);
	topRankItem->setEnabled(true);
	teamItem->setEnabled(true);
}