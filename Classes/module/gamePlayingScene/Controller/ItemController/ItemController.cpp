#include"ItemController.h"

ItemController* ItemController::itemController = NULL;

ItemController::ItemController(){}

ItemController::~ItemController(){
	if (itemController != NULL) {
		itemController->removeFromParentAndCleanup(true);
		itemController = NULL;
	}
}

ItemController* ItemController::getInstance() {
	if (itemController == NULL) {
		itemController = ItemController::create();
		itemController->setPosition(0, 0);
		itemController->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	}
	return itemController;
}

bool ItemController::init(){
	//add your layer
	Node* attributeLayer = CSLoader::createNode("GamePlayingScene/item/attributeLayer.csb");
	Node* itemLayer = CSLoader::createNode("GamePlayingScene/item/itemLayer.csb");
	itemLayer->setPosition(850, 32);
	this->addChild(attributeLayer);
	this->addChild(itemLayer);

	HP_button = static_cast<ui::Button*>(itemLayer->getChildByName("HP_BUTTON"));
	MP_button = static_cast<ui::Button*>(itemLayer->getChildByName("MP_BUTTON"));
	ARROW_button = static_cast<ui::Button*>(itemLayer->getChildByName("ARROW_BUTTON"));
	HP_button->addClickEventListener(CC_CALLBACK_1(ItemController::useHP, this));
	MP_button->addClickEventListener(CC_CALLBACK_1(ItemController::useMp, this));
	ARROW_button->addClickEventListener(CC_CALLBACK_1(ItemController::useArrow, this));

	arrowLabel = Label::create("arrow1", "Arial", 20);
	arrowLabel->setColor(Color3B::BLUE);
	arrowLabel->setPosition(ARROW_button->getPositionX(), ARROW_button->getPositionY() - 20);
	itemLayer->addChild(arrowLabel);

	//人物的血条，蓝条还有经验条，在update里面不断的赋值即可

	HP_percent = static_cast<ui::LoadingBar*>(attributeLayer->getChildByName("HP"));
	MP_percent = static_cast<ui::LoadingBar*>(attributeLayer->getChildByName("MP"));
	EXP_percent = static_cast<ui::LoadingBar*>(attributeLayer->getChildByName("EXP"));

	level_text = static_cast<ui::Text*>(attributeLayer->getChildByName("Text_1"));
	level_text->setPosition(Vec2(level_text->getPositionX(), level_text->getPositionY() + 12));

	scheduleUpdate();

	//this->addChild(AddBall());

	return true;
}

void ItemController::update(float delta) {

	HP_button->setTitleText(item::getHpNum());
	MP_button->setTitleText(item::getBpNum());
	ARROW_button->setTitleText(item::getArrowNum());

	auto archer_ = archer::getInstance();
	HP_percent->setPercent(100.0 * archer_->getBlood() / archer_->getInitialBlood());
	MP_percent->setPercent(100.0 * archer_->getBlue() / archer_->getInitialBLue());
	EXP_percent->setPercent(100.0 * archer_->getExp() / archer_->getTotalExp());

	level_text->setString(to_string(item::getCurrentArcherLevel()));

	if (item::getArrow() <= 0) {
		archer_->setWeapon(1);
	}

	arrowLabel->setString("arrow" + to_string(archer_->getWeapon()));
}

void ItemController::useHP(Ref* sender){
	if (item::getHp() > 0){
		item::useHp();
		auto archer_ = archer::getInstance();
		archer_->setBlood(archer_->getBlood() + 50);
	}
}

void ItemController::useMp(Ref* sender){
	if (item::getBp() > 0){
		item::useMp();
		auto archer_ = archer::getInstance();
		archer_->setBlue(archer_->getBlue() + 50);
	}
}

void ItemController::useArrow(Ref* sender){
	auto archer_ = archer::getInstance();
	if (item::getArrow() > 0) {
		if (archer_->getWeapon() == 1) {
			archer_->setWeapon(2);
		}
		else if (archer_->getWeapon() == 2){
			archer_->setWeapon(3);
		}
		else {
			archer_->setWeapon(1);
		}
	}
}

Sprite* ItemController::AddBall(){
	itemCarrier it;
	it.itermBall(200);
	return it.getItermBall();
}

Sprite* ItemController::Drop(Sprite*Ball){
	Sprite* iterm = Sprite::create(Constant::getItermBallPath());

	auto aBody = PhysicsBody::createCircle(iterm->getContentSize().width / 2);
	aBody->setRotationEnable(true);
	iterm->setPhysicsBody(aBody);

	//并没有设置好，你来设置掩码之类
	aBody->setCategoryBitmask(0x000000FF); //种类
	aBody->setContactTestBitmask(0x000000FF);
	aBody->setCollisionBitmask(0x000000FF);
	aBody->setGroup(0);

	aBody->getFirstShape()->setTag(Constant::getItermTag());

	iterm->setPosition(Ball->getPosition());

	return iterm;
}