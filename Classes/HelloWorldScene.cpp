#include "HelloWorldScene.h"
#include <ctime>
#include<random>
#include "module\startScene\StartScene.h"
#include "module\descriptionScene\DescriptionScene.h"
#include "module\topRankScene\TopRankScene.h"
#include "module\loadGameScene\LoadGameScene.h"

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
	//创建背景
	auto backgroundSprite = Sprite::create("image/background.png");
	backgroundSprite->setPosition(0, 0);
	backgroundSprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(backgroundSprite, 0);

	//可视范围大小
	Size visibleSize = backgroundSprite->getContentSize();

	//创建menu,4个按钮
	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(menu);
	
	auto startItem = MenuItemImage::create("image/menuGameStart.png", "image/menuGameStart.png", CC_CALLBACK_1(HelloWorld::ClickStart, this));
	startItem->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4 - 50);
	menu->addChild(startItem);

	auto descriptionItem = MenuItemImage::create("image/menuDescription.png", "image/menuDescription.png", CC_CALLBACK_1(HelloWorld::ClickDescription, this));
	descriptionItem->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4 - 150);
	menu->addChild(descriptionItem);

	auto loadGameItem = MenuItemImage::create("image/menuLoadGame.png", "image/menuLoadGame.png", CC_CALLBACK_1(HelloWorld::ClickLoadGame, this));
	loadGameItem->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4 - 250);
	menu->addChild(loadGameItem);

	auto topRankItem = MenuItemImage::create("image/menuTopRank.png", "image/menuTopRank.png", CC_CALLBACK_1(HelloWorld::ClickTopRank, this));
	topRankItem->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4 - 350);
	menu->addChild(topRankItem);
	return true;
}

void HelloWorld::ClickStart(Ref* sender)
{
	auto startScene = StartScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, startScene, false);
	Director::getInstance()->replaceScene(transition);
}

void HelloWorld::ClickDescription(Ref* sender)
{
	auto descriptionScene = DescriptionScene::create();
	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene *transition = CCTransitionPageTurn::create(0.5f, descriptionScene, false);
	Director::getInstance()->pushScene(transition);
}

void HelloWorld::ClickLoadGame(Ref* sender)
{
	auto loadGameScene = LoadGameScene::create();
	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene *transition = CCTransitionPageTurn::create(0.5f, loadGameScene, false);
	Director::getInstance()->pushScene(transition);
}

void HelloWorld::ClickTopRank(Ref* sender)
{
	auto topRankScene = TopRankScene::create();
	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene *transition = CCTransitionPageTurn::create(0.5f, topRankScene, false);
	Director::getInstance()->pushScene(transition);
}