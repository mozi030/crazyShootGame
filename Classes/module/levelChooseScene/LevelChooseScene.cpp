#include"LevelChooseScene.h"
USING_NS_CC;
#pragma execution_character_set("utf-8")

bool LevelChooseScene::init() {
	if (!Scene::init()){
		return  false;
	}
	auto bg = Sprite::create(Constant::getLevelChosenSceneBackgroundPath());
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bg->setPosition(0, 0);
	this->addChild(bg);

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(menu, 1);

	level1 = MenuItemImage::create(Constant::getLevelChosenButton1Path(), Constant::getLevelChosenButton1Path(), CC_CALLBACK_1(LevelChooseScene::Level1ChosenMenuItemCallback, this));
	level1->setPosition(131.46, 444.76);
	menu->addChild(level1, 1);

	level2 = MenuItemImage::create(Constant::getLevelChosenButton2Path(), Constant::getLevelChosenButton2Path(), CC_CALLBACK_1(LevelChooseScene::Level2ChosenMenuItemCallback, this));
	level2->setPosition(335.05, 335.27);
	menu->addChild(level2, 1);

	level3 = MenuItemImage::create(Constant::getLevelChosenButton3Path(), Constant::getLevelChosenButton3Path(), CC_CALLBACK_1(LevelChooseScene::Level3ChosenMenuItemCallback, this));
	level3->setPosition(702.00, 299.45);
	menu->addChild(level3, 1);

	level4 = MenuItemImage::create(Constant::getLevelChosenButton4Path(), Constant::getLevelChosenButton4Path(), CC_CALLBACK_1(LevelChooseScene::Level4ChosenMenuItemCallback, this));
	level4->setPosition(964.44, 445.62);
	menu->addChild(level4, 1);

	level5 = MenuItemImage::create(Constant::getLevelChosenButton5Path(), Constant::getLevelChosenButton5Path(), CC_CALLBACK_1(LevelChooseScene::Level5ChosenMenuItemCallback, this));
	level5->setPosition(877.50, 77.25);
	menu->addChild(level5, 1);

	auto shopButton = MenuItemImage::create(Constant::getLevelChosenButtonshopPath(), Constant::getLevelChosenButtonshopPath(), CC_CALLBACK_1(LevelChooseScene::ShopCallback, this));
	shopButton->setPosition(63.67, 40.08);
	menu->addChild(shopButton, 1);

	shop = CSLoader::createNode("Shop/ShopLayer.csb");
	shop->setPosition(300, 120);
	shop->setVisible(false);
	this->addChild(shop, 2);

	ui::Button* exitButton = static_cast<ui::Button*>(shop->getChildByName("exit"));
	ui::Button* hpBuyButton = static_cast<ui::Button*>(shop->getChildByName("buy_1"));
	ui::Button* bpBuyButton = static_cast<ui::Button*>(shop->getChildByName("buy_2"));
	ui::Button* arrowBuyButton = static_cast<ui::Button*>(shop->getChildByName("buy_3"));
	ui::Button* hpSaleButton = static_cast<ui::Button*>(shop->getChildByName("sale_1"));
	ui::Button* bpSaleButton = static_cast<ui::Button*>(shop->getChildByName("sale_2"));
	ui::Button* arrowSaleButton = static_cast<ui::Button*>(shop->getChildByName("sale_3"));

	hpNumText = static_cast<ui::Text*>(shop->getChildByName("hp_num"));
	bpNumText = static_cast<ui::Text*>(shop->getChildByName("bp_num"));
	arrowNumText = static_cast<ui::Text*>(shop->getChildByName("weapon"));
	moneyText = static_cast<ui::Text*>(shop->getChildByName("Text_1"));
	// 
	hpBuyButton->addClickEventListener(CC_CALLBACK_1(LevelChooseScene::buyHp, this));
	bpBuyButton->addClickEventListener(CC_CALLBACK_1(LevelChooseScene::buyBp, this));
	arrowBuyButton->addClickEventListener(CC_CALLBACK_1(LevelChooseScene::buyarrow, this));
	exitButton->addClickEventListener(CC_CALLBACK_1(LevelChooseScene::ExitShop, this));
	hpSaleButton->addClickEventListener(CC_CALLBACK_1(LevelChooseScene::saleHp, this));
	bpSaleButton->addClickEventListener(CC_CALLBACK_1(LevelChooseScene::saleBp, this));
	arrowSaleButton->addClickEventListener(CC_CALLBACK_1(LevelChooseScene::saleArrow, this));

	auto action = CSLoader::createTimeline("Shop/merchant.csb");
	auto speak = CSLoader::createTimeline("Shop/speak.csb");
	shop->runAction(action);
	shop->runAction(speak);
	action->gotoFrameAndPlay(0, 50, true);
	speak->gotoFrameAndPlay(0, 241, true);

	scheduleUpdate();

	return true;
}

void LevelChooseScene::buyHp(Ref* sender) {
	item::buyHp();
}

void LevelChooseScene::buyBp(Ref* sender){
	item::buyBp();
}

void LevelChooseScene::buyarrow(Ref* sender){
	item::buyArrow();
}

void LevelChooseScene::saleHp(Ref* sender){
	if (item::getHp() > 0)
		item::saleHp();
}

void LevelChooseScene::saleBp(Ref* sender){
	if (item::getBp() > 0)
		item::saleBp();
}

void LevelChooseScene::saleArrow(Ref* sender){
	if (item::getArrow() > 0)
		item::saleArrow();
}

void LevelChooseScene::update(float delta){
	hpNumText->setString(item::getHpNum());
	bpNumText->setString(item::getBpNum());
	arrowNumText->setString(item::getArrowNum());
	moneyText->setString(item::getMoneyNum());
}

void LevelChooseScene::ShopCallback(Ref* sender) {
	level1->setEnabled(false);
	level2->setEnabled(false);
	level3->setEnabled(false);
	level4->setEnabled(false);
	level5->setEnabled(false);
	shop->setVisible(true);
}

void LevelChooseScene::OpenShop(Ref* sender){
	shop->setVisible(true);
}

void LevelChooseScene::ExitShop(Ref* sender){
	shop->setVisible(false);
	level1->setEnabled(true);
	level2->setEnabled(true);
	level3->setEnabled(true);
	level4->setEnabled(true);
	level5->setEnabled(true);
}

void LevelChooseScene::Level1ChosenMenuItemCallback(Ref* sender) {
	ParameterManager::setCurrentGameLevel(1);

	auto gamePlayingScene = GamePlayingScene::createScene();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, gamePlayingScene, false);
	Director::getInstance()->replaceScene(transition);
}

void LevelChooseScene::Level2ChosenMenuItemCallback(Ref* sender) {
	ParameterManager::setCurrentGameLevel(2);

	auto gamePlayingScene = GamePlayingScene::createScene();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, gamePlayingScene, false);
	Director::getInstance()->replaceScene(transition);
}

void LevelChooseScene::Level3ChosenMenuItemCallback(Ref* sender) {
	ParameterManager::setCurrentGameLevel(3);

	auto gamePlayingScene = GamePlayingScene::createScene();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, gamePlayingScene, false);
	Director::getInstance()->replaceScene(transition);
}

void LevelChooseScene::Level4ChosenMenuItemCallback(Ref* sender) {
	ParameterManager::setCurrentGameLevel(4);

	auto gamePlayingScene = GamePlayingScene::createScene();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, gamePlayingScene, false);
	Director::getInstance()->replaceScene(transition);
}

void LevelChooseScene::Level5ChosenMenuItemCallback(Ref* sender) {
	ParameterManager::setCurrentGameLevel(5);

	auto gamePlayingScene = GamePlayingScene::createScene();
	Director::sharedDirector()->setDepthTest(true);
	TransitionScene *transition = TransitionPageTurn::create(0.5f, gamePlayingScene, false);
	Director::getInstance()->replaceScene(transition);
}