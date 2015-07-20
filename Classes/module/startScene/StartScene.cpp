#include"StartScene.h"
#include"../levelChooseScene/LevelChooseScene.h"
USING_NS_CC;

StartScene* StartScene::createScene(){
	auto aScene = StartScene::create();

	//ÓÎÏ·±³¾°½éÉÜ£¬¿Éskip
	CCLOG("in createScene");
	return aScene;
}

StartScene::~StartScene()
{
	CCLOG("StartScene delete");
}

bool StartScene::init() {
	if (!Scene::init()) {
		return  false;
	}
	MenuItemFont *skipMenuItem = MenuItemFont::create("skip", CC_CALLBACK_1(StartScene::SkipMenuItemCallback,this));
	skipMenuItem->setAnchorPoint(Vec2(0, 0));
	skipMenuItem->setPosition(Vec2(900, 25));
	Menu *skipMenu = Menu::create(skipMenuItem, NULL);
	skipMenu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	skipMenu->setPosition(0, 0);
	this->addChild(skipMenu);

	Label* label = Label::create("background introduction", "arial", 30);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(Vec2(450, 300));
	this->addChild(label);
	
	return true;
}

void StartScene::SkipMenuItemCallback(Ref* sender) {
	auto levelChosenScene = LevelChooseScene::create();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, levelChosenScene, false);
	Director::getInstance()->replaceScene(transition);
}