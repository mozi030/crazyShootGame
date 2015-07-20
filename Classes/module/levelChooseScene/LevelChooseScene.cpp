#include"LevelChooseScene.h"
#include"../gamePlayingScene/GamePlayingScene.h"
USING_NS_CC;
#pragma execution_character_set("utf-8")

bool LevelChooseScene::init() {
	if (!Scene::init()){
		return  false;
	}
	MenuItemFont *levelChosenMenuItem = MenuItemFont::create("LevelChosen", CC_CALLBACK_1(LevelChooseScene::LevelChosenMenuItemCallback,this));
	levelChosenMenuItem->setAnchorPoint(Vec2(0, 0));
	levelChosenMenuItem->setPosition(Vec2(500, 300));
	Menu *levelChosenMenu = Menu::create(levelChosenMenuItem, NULL);
	levelChosenMenu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	levelChosenMenu->setPosition(0, 0);
	this->addChild(levelChosenMenu);

	return true;
}

void LevelChooseScene::LevelChosenMenuItemCallback(Ref* sender) {
	auto gamePlayingScene = GamePlayingScene::createScene();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, gamePlayingScene, false);
	Director::getInstance()->replaceScene(transition);
}