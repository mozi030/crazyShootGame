#include"../../Model/archer/archer.h"
#include"../../Model/Constant/Constant.h"

/**
archerController* archerController::archer = NULL;

archerController::archerController() {}

archerController::~archerController() {
archer = NULL;
}
**/

//archerController* archerController::archer = NULL;

archer* archer::getInstance(){
	//auto poolManager = PoolManager::getInstance();
	//if (!poolManager->getCurrentPool()->isClearing() || !poolManager->isObjectInPools(archer)) {
	if (archer_ == NULL){
		archer_ = new archer();

		archer_->autorelease();
		//archer = (archerController*)Sprite::createWithSpriteFrameName(Constant::getArcherFrameName());
		archer_->init();

		//¸ù¾Ý¹­¼ýÊÖËùÔÚµÄ¹Ø¿¨£¬³õÊ¼»¯ËûµÄÒ»Ð©ÊôÐÔ

		if (true){
			archer_->hpValue = 100;
		}
		else
		{
			archer_->hpValue = 200;
		}

	}
	return archer_;
}



/**
bool archerController::init(){
bool a = Layer::init();

Size visibleSize = Director::getInstance()->getVisibleSize();
Vec2 origin = Director::getInstance()->getVisibleOrigin();
float times = 1.5;//Í¼ÐÎ·Å´ó±¶Êý

body = Sprite::create(Constant::getArcherbodyPath());
body->setPosition(visibleSize.width/10, visibleSize.height/10);
body->setScale(times);
this->addChild(body, 1);

hand = Sprite::create(Constant::getArcherhandPath());
hand->setPosition(body->getPositionX() - (4 * times), body->getPositionY() - (3 * times));
hand->setScale(times);
this->addChild(hand, 3);

archerCenter = hand->getPosition();

head = Sprite::create(Constant::getArcherheadPath());
head->setPosition(body->getPositionX() - (1 * times), body->getPositionY() + (2 * times));
head->setScale(times);
this->addChild(head, 2);

//add touch listener
EventListenerTouchOneByOne* screenListener = EventListenerTouchOneByOne::create();
screenListener->setSwallowTouches(false);// true²»ÏòÏÂ´¥Ãþ£¬¼òµ¥µãÀ´Ëµ£¬±ÈÈçÓÐÁ½¸ösprite ,AºÍ B£¬AÔÚÉÏBÔÚÏÂ£¨Î»ÖÃÖØµþ£©
screenListener->onTouchBegan = CC_CALLBACK_2(archerController::onTouchBegan, this);
Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(screenListener, this);

return a;
}

bool archerController::onTouchBegan(Touch *touch, Event *unused_event) {
auto touchPoint = touch->getLocation();
if (touchPoint.x >= archerCenter.x) {
body->setFlippedX(false);//²»·­×ª
head->setFlippedX(false);
hand->setFlippedX(false);
double angle;
if (fabs(touchPoint.x - archerCenter.x) < 1e-6) {
angle = 135;
}
else {
//¼ÆËãµã»÷´¦ÓëarcherµÄÁ¬ÏßÓë¾ÅµãÖÓ·½ÏòµÄË³Ê±Õë¼Ð½Ç¡£
angle = -atan((touchPoint.y - archerCenter.y) / (touchPoint.x - archerCenter.x)) / 3.141592654 * 180;
angle += 180;
if (angle < 135) angle = 135;//ÏÞÖÆ½ÇµÄ·¶Î§£¬²»È»Èç¹ûÒªÍ·ÍùÕýÉÏ·½¿´µÄ»°£¬Í¼»áºÜÄÑ¿´
else if (angle > 225) angle = 225;
}
head->setRotation(angle - 180);
hand->setRotation(angle + 90);
}
else {
double angle = -atan((touchPoint.y - archerCenter.y) / (touchPoint.x - archerCenter.x)) / 3.141592654 * 180;
body->setFlippedX(true);
head->setFlippedX(true);
hand->setFlippedX(true);
if (angle > 45) angle = 45;
else if (angle < -45) angle = -45;
head->setRotation(angle);
hand->setRotation(angle + 90);
}
return true;
}

/*
archerController* archerController::getInstance(){
//auto poolManager = PoolManager::getInstance();
//if (!poolManager->getCurrentPool()->isClearing() || !poolManager->isObjectInPools(archer)) {
if (archer == NULL){
archer = new archerController();
archer->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Constant::getArcherFrameName()));
archer->autorelease();
//archer = (archerController*)Sprite::createWithSpriteFrameName(Constant::getArcherFrameName());
archer->initial();
}
return archer;
}

void archerController::initial() {
auto aBody = PhysicsBody::createCircle(archer->getContentSize().height / 2);
aBody->setRotationEnable(false);
archer->setPhysicsBody(aBody);
archer->setPosition(20, 100);
archer->setAnchorPoint(Vec2(0.5, 0.5));
archer->getPhysicsBody()->setContactTestBitmask(0x0000000F);
//archerSprite->getPhysicsBody()->setCollisionBitmask(0x0000000F);
archer->getPhysicsBody()->setCategoryBitmask(0x0000000F);
archer->getPhysicsBody()->getFirstShape()->setTag(Constant::getArcherTag());
}
*/




