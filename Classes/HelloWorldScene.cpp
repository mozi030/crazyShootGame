#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "module\BackgroundStoryScene\BackgroundStoryScene.h"
#include "public/parameterManager/ParameterManager.h"

USING_NS_CC;

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
	addChild(rootNode);

	//可视范围大小
	Size visibleSize = ParameterManager::getVisibleSize();

	//创建menu,4个按钮
	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(menu);
	
	auto startItem = MenuItemImage::create("HelloWorldScene/menuGameStart.png", "HelloWorldScene/menuGameStart.png", CC_CALLBACK_1(HelloWorld::ClickStart, this));
	startItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 75);
	menu->addChild(startItem);

	auto descriptionItem = MenuItemImage::create("HelloWorldScene/menuDescription.png", "HelloWorldScene/menuDescription.png", CC_CALLBACK_1(HelloWorld::ClickDescription, this));
	descriptionItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 225);
	menu->addChild(descriptionItem);

	auto loadGameItem = MenuItemImage::create("HelloWorldScene/menuLoadGame.png", "HelloWorldScene/menuLoadGame.png", CC_CALLBACK_1(HelloWorld::ClickLoadGame, this));
	loadGameItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 150);
	menu->addChild(loadGameItem);

	auto topRankItem = MenuItemImage::create("HelloWorldScene/menuTopRank.png", "HelloWorldScene/menuTopRank.png", CC_CALLBACK_1(HelloWorld::ClickTopRank, this));
	topRankItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 300);
	menu->addChild(topRankItem);

	auto controlItem = MenuItemImage::create("HelloWorldScene/menuControl.png", "HelloWorldScene/menuControl.png", CC_CALLBACK_1(HelloWorld::ClickControl, this));
	controlItem->setPosition(visibleSize.width / 3 + 60, visibleSize.height * 3 / 4 - 375);
	menu->addChild(controlItem);
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
}

void HelloWorld::ClickLoadGame(Ref* sender)
{
	//读档
}

void HelloWorld::ClickTopRank(Ref* sender)
{
	//高分排名
}

void HelloWorld::ClickControl(Ref* sender)
{
	//更改设置
}