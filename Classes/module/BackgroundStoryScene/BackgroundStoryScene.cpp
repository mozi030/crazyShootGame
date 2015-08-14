#include"BackgroundStoryScene.h"

USING_NS_CC;

BackgroundStoryScene* BackgroundStoryScene::createScene(){
	auto aScene = BackgroundStoryScene::create();
	return aScene;
}

bool BackgroundStoryScene::init() {
	if (!Scene::init()) {
		return  false;
	}

	auto storyNode = CSLoader::createNode("BackgroundStoryScene/BackgroundStorySceneCsd/BackgroundStorySceneCsd.csb");
	this->addChild(storyNode);
	auto skipMenuItem = MenuItemImage::create("BackgroundStoryScene/skip.png", "BackgroundStoryScene/skip2.png", CC_CALLBACK_1(BackgroundStoryScene::SkipMenuItemCallback, this));
	skipMenuItem->setAnchorPoint(Vec2(0, 0));
	skipMenuItem->setPosition(Vec2(900, 500));
	Menu *skipMenu = Menu::create(skipMenuItem, NULL);
	skipMenu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	skipMenu->setPosition(0, 0);
	this->addChild(skipMenu);
	
	return true;
}

void BackgroundStoryScene::SkipMenuItemCallback(Ref* sender) {
	auto levelChosenScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, levelChosenScene, false);
	Director::getInstance()->replaceScene(transition);
}